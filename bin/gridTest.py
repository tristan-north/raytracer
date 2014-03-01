#TODO:
# Account for ray starting outside the grid
# Account for division by 0s

import maya.cmds as cmds
from math import *

class Vec3:
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
		
	def __repr__(self):
		return '(' + `self.x` + ', ' + `self.y` + ', ' + `self.z` + ')'
		
	def normalize(self):
		length = sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
		self.x = self.x/length
		self.y = self.y/length
		self.z = self.z/length
		
	def drawAsLine(self, length):
		line = cmds.curve(d=1, p=[(0, 0, 0), (self.x*length, self.y*length, self.z*length)])
		colorRed(line)
		
		cmds.select(cl=True)
		
	def drawAsPoint(self):
		loc = cmds.spaceLocator()
		cmds.scale(0.1, 0.1, 0.1)
		cmds.move(self.x, self.y, self.z)
		colorRed(loc)
		
		cmds.select(cl=True)
		
class Ray:
	def __init__(self, origin, direction):
		self.o = origin
		self.d = direction
		
	def draw(self, length):
		line = cmds.curve(d=1, p=[(0, 0, 0), (self.d.x*length, self.d.y*length, self.d.z*length)])
		cmds.move(self.o.x, self.o.y, self.o.z)
		colorRed(line)
		
		cmds.select(cl=True)

def createGrid(cellSizeX, cellSizeY, cellSizeZ, n, offset):
	if cmds.ls('cell*'): cmds.delete(cmds.ls('cell*'))
	
	for x in xrange(n):
		for y in xrange(n):
			for z in xrange(n):
				name = 'cell' + `x` + `y` + `z`
				cmds.polyCube(name=name)
				cmds.scale(0.99, 0.99, 0.99)
				cmds.move(0.5, 0.5, 0.5)
				cmds.makeIdentity(apply=True, t=1, s=1, n=0, pn=1)
				cmds.move(0, 0, 0, name + '.scalePivot')
				cmds.scale(cellSizeX, cellSizeY, cellSizeZ)
				cmds.move(x*cellSizeX + offset.x, y*cellSizeY + offset.y, z*cellSizeZ + offset.z)
	cmds.select(cl=True)

def colorRed(transformName):
	shape = cmds.listRelatives(transformName, shapes=True)[0]
	cmds.setAttr(shape + '.overrideEnabled', 1)
	cmds.setAttr(shape + '.overrideColor', 13)

def hideNonRed():
	for cell in cmds.ls('cell*', type='mesh'):
		if not cmds.getAttr(cell + '.overrideEnabled'):
			cmds.setAttr(cell+ '.visibility', 0)

#############################################
# SETUP

if cmds.ls('curve*'): cmds.delete(cmds.ls('curve*'))
if cmds.ls('locator*'): cmds.delete(cmds.ls('locator*'))

ray = Ray(Vec3(3.1, 2.2, 3.1), Vec3(-1.4, 2, 3))
ray.d.normalize()
ray.draw(15)

gridMax = Vec3(10, 12, 5)
gridMin = Vec3(0.5, 0.5, 0.5)
gridResolution = 9

cellSizeX = (gridMax.x - gridMin.x) / gridResolution
cellSizeY = (gridMax.y - gridMin.y) / gridResolution
cellSizeZ = (gridMax.z - gridMin.z) / gridResolution

createGrid(cellSizeX, cellSizeY, cellSizeZ, gridResolution, gridMin)

#############################################
# TRAVERSAL

# This is the ray origin position relative to the grid origin position. Ie rayOGrid is in "grid space".
rayOGrid = Vec3(ray.o.x - gridMin.x, ray.o.y - gridMin.y, ray.o.z - gridMin.z)
# This is the ray origin position in "cell space". Ie if rayOCell.x is 2.5, the ray starts in the middle of the 3rd cell in x.
rayOCell = Vec3(rayOGrid.x / cellSizeX, rayOGrid.y / cellSizeY, rayOGrid.z / cellSizeZ)

print 'rayOGrid: ' + `rayOGrid`
print 'rayOCell: ' + `rayOCell`

cellIndex = Vec3(int(rayOCell.x), int(rayOCell.y), int(rayOCell.z))

print 'cellIndex: ' + `cellIndex`
colorRed('cell' + `cellIndex.x` + `cellIndex.y` + `cellIndex.z`)

# deltaT is the distance between intersections on each axis
deltaTx = abs(cellSizeX/ray.d.x)
deltaTy = abs(cellSizeY/ray.d.y)
deltaTz = abs(cellSizeZ/ray.d.z)
print 'deltaTx: ' + `deltaTx`
print 'deltaTy: ' + `deltaTy`
print 'deltaTz: ' + `deltaTz`

# tx, ty and tz are how far along the ray needs to be travelled to get to the
# next (based on current t) cell in x, next cell in y and next cell in z.
# Whichever is smallest will be the next intersection.
tx = ((cellIndex.x + 1) * cellSizeX - rayOGrid.x) / ray.d.x
if ray.d.x < 0:
	tx = (cellIndex.x * cellSizeX - rayOGrid.x) / ray.d.x
ty = ((cellIndex.y + 1) * cellSizeY - rayOGrid.y) / ray.d.y
if ray.d.y < 0:
	ty = (cellIndex.y * cellSizeY - rayOGrid.y) / ray.d.y
tz = ((cellIndex.z + 1) * cellSizeZ - rayOGrid.z) / ray.d.z
if ray.d.z < 0:
	tz = (cellIndex.z * cellSizeZ - rayOGrid.z) / ray.d.z

# Used to either increment or decrement cell index based on if ray direction is + or -.
stepX = 1
if ray.d.x < 0:
	stepX = -1
stepY = 1
if ray.d.y < 0:
	stepY = -1
stepZ = 1
if ray.d.z < 0:
	stepZ = -1


t = 0  # disatnce along ray
while(True):
	if tx <= ty and tx <= tz:
		# tx is smallest, so we're crossing into another cell in x.
		t = tx   # As this is the next cell boarder intersected, update t to this
		tx = tx + deltaTx   # update to next intersection along x
		cellIndex.x = cellIndex.x + stepX
	elif ty <= tx and ty <= tz:
		# ty is smallest, so we're crossing into another cell in y.
		t = ty
		ty = ty + deltaTy
		cellIndex.y = cellIndex.y + stepY
	elif tz <= tx and tz <= ty:
		# tz is smallest, so we're crossing into another cell in z.
		t = tz
		tz = tz + deltaTz
		cellIndex.z = cellIndex.z + stepZ
		
	# Break if trying to acess a cell outside the grid
	if (cellIndex.x > gridResolution-1) or (cellIndex.y > gridResolution-1) or (cellIndex.z > gridResolution-1):
			break
	if (cellIndex.x < 0) or (cellIndex.y < 0) or (cellIndex.z < 0):
			break
		
	testPoint = Vec3(ray.d.x * t + ray.o.x, ray.d.y * t + ray.o.y, ray.d.z * t + ray.o.z)
	testPoint.drawAsPoint()

	colorRed('cell' + `cellIndex.x` + `cellIndex.y` + `cellIndex.z`)

	
#hideNonRed()
	

