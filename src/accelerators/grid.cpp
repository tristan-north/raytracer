#include <math.h>
#include <algorithm>
#include <QtDebug>
#include "utilities/vector3.h"
#include "grid.h"
#include "utilities/common.h"
#include "utilities/timer.h"
#include "utilities/shaderec.h"
#include "world/world.h"

using namespace std;

extern Timer closestIsectTimer;
extern Timer shadowIsectTimer;

void clamp(uint& x, const uint min, const uint max) {
	if(x > max) x = max;
	else if (x < min) x = min;
}
void clamp(int& x, const int min, const int max) {
	if(x > max) x = max;
	else if (x < min) x = min;
}

Grid::Grid(World& w) : AbstractAccel(w)
{
	qDebug() << "Building acceleration structure (grid).";
	timespec tp;
	Timer::getTime(tp);

	// Create bbox of scene.
	BBox primBBox;
	for( size_t i = 0; i < w.primitives.size(); i++) {
		primBBox = w.primitives[i]->get_bbox();
		bbox.expandToFit(primBBox);
	}

	qDebug("Scene bounds: (%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f)",
		   bbox.xMin, bbox.yMin, bbox.zMin,
		   bbox.xMax, bbox.yMax, bbox.zMax);

	// Compute grid res based on the 1983 paper "A Parallel Ray Tracing Computer"
	// by Cleary and "Ray Tracing Animated Scenes using Coherent Grid Traversal", Wald 2006
	const int lambda = 5;  // Tweaking this per scene can be beneficial.
	const Vector3 gridSize(bbox.xMax - bbox.xMin, bbox.yMax - bbox.yMin, bbox.zMax - bbox.zMin);
	const double gridVolume = gridSize.x * gridSize.y * gridSize.z;

	const double resScaleFactor = cbrt(lambda * w.primitives.size() / gridVolume);

	gridRes.x = gridSize.x * resScaleFactor;
	gridRes.y = gridSize.y * resScaleFactor;
	gridRes.z = gridSize.z * resScaleFactor;

	qDebug("Grid resolution: %dx%dx%d", gridRes.x, gridRes.y, gridRes.z);

	cellSize.x = gridSize.x / gridRes.x;
	cellSize.y = gridSize.y / gridRes.y;
	cellSize.z = gridSize.z / gridRes.z;

	// Allocate grid cells.
	uint numCells = gridRes.x * gridRes.y * gridRes.z;
	cells = new Cell[numCells];
	memset(cells, 0x0, sizeof(Cell) * numCells);

	// Insert primitives into grid.
	for( size_t i = 0; i < w.primitives.size(); i++) {
		// Find the cell which contains the primitive bbox min point
		// and the cell containing the max point.
		primBBox = w.primitives[i]->get_bbox();

		uint primMinCellX = (primBBox.xMin - bbox.xMin) / cellSize.x;
		clamp(primMinCellX, 0, gridRes.x-1);
		uint primMinCellY = (primBBox.yMin - bbox.yMin) / cellSize.y;
		clamp(primMinCellY, 0, gridRes.y-1);
		uint primMinCellZ = (primBBox.zMin - bbox.zMin) / cellSize.z;
		clamp(primMinCellZ, 0, gridRes.z-1);

		uint primMaxCellX = (primBBox.xMax - bbox.xMin) / cellSize.x;
		clamp(primMaxCellX, 0, gridRes.x-1);
		uint primMaxCellY = (primBBox.yMax - bbox.yMin) / cellSize.y;
		clamp(primMaxCellY, 0, gridRes.y-1);
		uint primMaxCellZ = (primBBox.zMax - bbox.zMin) / cellSize.z;
		clamp(primMaxCellZ, 0, gridRes.z-1);

		// Loop through cells overlapped by the primitive bbox.
		for( uint xCellIndex = primMinCellX; xCellIndex <= primMaxCellX; xCellIndex++ ) {
			for( uint yCellIndex = primMinCellY; yCellIndex <= primMaxCellY; yCellIndex++ ) {
				for( uint zCellIndex = primMinCellZ; zCellIndex <= primMaxCellZ; zCellIndex++ ) {
					get_cell(xCellIndex, yCellIndex, zCellIndex)->addPrimitive(w.primitives[i]);
				}
			}
		}

	}

	qDebug("Finished building acceleration structure. Build time %.4fs", Timer::getElapsedMsec(tp) / 1000.0);
}


ShadeRec Grid::closest_intersection(const Ray &ray)
{
	timespec tp;
	Timer::getTime(tp);

	ShadeRec sr(world);
	intersect(sr, ray, false, NULL);

	closestIsectTimer.add(tp);
	return sr;
}


bool Grid::shadow_intersection(const Ray& ray, double distToLight) {
	timespec tp;
	Timer::getTime(tp);

	ShadeRec sr(world);
	intersect(sr, ray, true, distToLight);

	shadowIsectTimer.add(tp);

	if( sr.hit_an_object && sr.t < distToLight )
		return true;
	else
		return false;
}


bool Grid::intersect(ShadeRec &returnSr, const Ray& ray, const bool isShadowRay, const double maxT) {
	ShadeRec lightSr(world);
	ShadeRec testSr(world);

	// Get intersection with any lights first, if not a shadow ray.
	double t;
	if( !isShadowRay ) {
		lightSr.t = kHugeValue;
		uint numObjects = world.lights.size();
		for (uint i = 0; i < numObjects; i++) {
			if ( world.lights[i]->hit(ray, t, testSr) && (t < lightSr.t)) {
				lightSr.t = t;
				lightSr.hit_an_object = true;
				lightSr.material_ptr = testSr.material_ptr;
				lightSr.hit_point = ray.o + t * ray.d;
				lightSr.normal = testSr.normal;
			}
		}
	}

	double bboxIsecDist = 0;
	// Check if ray is inside bbox.
	if( !bbox.inside(ray.o) ) {
		// If not inside find if and where ray hits grid bbox. If it misses just return
		// whatever light was hit (if no lights were hit lightSr will be empty).
		if( !bbox.hit(ray, bboxIsecDist) ) {
			returnSr = lightSr;
			return returnSr.hit_an_object;
		}
	}

	// rayOGridspace is the ray origin position relative to the grid origin position. Ie rayOGrid is in "grid space".
	Vector3 gridIsecPoint = ray.o + ray.d*bboxIsecDist;
	Vector3 rayOGridspace(gridIsecPoint.x-bbox.xMin, gridIsecPoint.y-bbox.yMin, gridIsecPoint.z-bbox.zMin);
	// This is the ray origin position in "cell space". Ie if rayOCell.x is 2.5,
	// the ray starts in the middle of the 3rd cell in x.
	Vector3 rayOCellspace(rayOGridspace.x/cellSize.x, rayOGridspace.y/cellSize.y, rayOGridspace.z/cellSize.z);

	struct {int x; int y; int z;} cellIndex;
	cellIndex.x = floor(rayOCellspace.x); clamp(cellIndex.x, 0, gridRes.x-1);
	cellIndex.y = floor(rayOCellspace.y); clamp(cellIndex.y, 0, gridRes.y-1);
	cellIndex.z = floor(rayOCellspace.z); clamp(cellIndex.z, 0, gridRes.z-1);

	// deltaT is the distance between cell border intersections for each axis
	float deltaTx = fabs(cellSize.x/ray.d.x);
	float deltaTy = fabs(cellSize.y/ray.d.y);
	float deltaTz = fabs(cellSize.z/ray.d.z);

	// tx, ty and tz are how far along the ray needs to be travelled to get to the
	// next (based on current t) cell in x, next cell in y and next cell in z.
	// Whichever is smallest will be the next intersection.
	double tx = ((cellIndex.x + 1) * cellSize.x - rayOGridspace.x) / ray.d.x;
	if( ray.d.x < 0 )
		tx = (cellIndex.x * cellSize.x - rayOGridspace.x) / ray.d.x;
	double ty = ((cellIndex.y + 1) * cellSize.y - rayOGridspace.y) / ray.d.y;
	if( ray.d.y < 0 )
		ty = (cellIndex.y * cellSize.y - rayOGridspace.y) / ray.d.y;
	double tz = ((cellIndex.z + 1) * cellSize.z - rayOGridspace.z) / ray.d.z;
	if( ray.d.z < 0 )
		tz = (cellIndex.z * cellSize.z - rayOGridspace.z) / ray.d.z;

	// Used to either increment or decrement cell index based on if ray direction is + or -.
	int stepX = 1; if(ray.d.x < 0) stepX = -1;
	int stepY = 1; if(ray.d.y < 0) stepY = -1;
	int stepZ = 1; if(ray.d.z < 0) stepZ = -1;

	// Traverse the grid.
	t = 0;
	Cell* cell;
	while(true) {
		// Intersect the primitives in the current cell.
		cell = get_cell(cellIndex.x, cellIndex.y, cellIndex.z);
		cell->intersectPrimitives(ray, returnSr, testSr);

		// Move variables to next cell.
		if( tx <= ty && tx <= tz ) {
			// tx is smallest, so we're crossing into another cell in x.
			t = tx;   // As this is the next cell boarder intersected, update t to this
			tx += deltaTx;   // update to next intersection along x
			cellIndex.x = cellIndex.x + stepX;
		} else if( ty <= tx && ty <= tz ) {
			// ty is smallest, so we're crossing into another cell in y.
			t = ty;
			ty += deltaTy;
			cellIndex.y = cellIndex.y + stepY;
		} else if( tz <= tx && tz <= ty ) {
			// tz is smallest, so we're crossing into another cell in z.
			t = tz;
			tz += deltaTz;
			cellIndex.z = cellIndex.z + stepZ;
		}

		// If have intersected a primitive and the intersection distance is
		// less than the distance to the next cell, we've found the closest so break.
		if( returnSr.hit_an_object ) {
			if( (returnSr.t-bboxIsecDist) < t )
				break;
		}

		// Break if the next cell is outside the grid.
		if( cellIndex.x > (int)(gridRes.x-1) || cellIndex.y > (int)(gridRes.y-1) || cellIndex.z > (int)(gridRes.z-1) )
			break;
		if( cellIndex.x < 0 || cellIndex.y < 0 || cellIndex.z < 0)
			break;
	}

	// If a light hit was closer, return that instead.
	if( lightSr.hit_an_object ) {
		if( lightSr.t < returnSr.t )
			returnSr = lightSr;
	}

	return returnSr.hit_an_object;
}

/*
// This just tests against every primitive with no accel struct.
ShadeRec Grid::closest_intersection(const Ray& ray) {
	timespec tp;
	Timer::getTime(tp);

	ShadeRec returnSr(world);
	returnSr.t = kHugeValue;

	// Test intersection of each geometric object and keep the ShadeRec
	// of the closest intersection.
	int numObjects = world.primitives.size();
	ShadeRec testSr(world);
	double testT;
	for (int j = 0; j < numObjects; j++) {
		if ( world.primitives[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
			returnSr.t = testT;
			returnSr.hit_an_object = true;
			returnSr.material_ptr =  world.primitives[j]->get_material();
			returnSr.hit_point = ray.o + testT * ray.d;
			returnSr.normal = testSr.normal;
		}
	}

	// Test intersection of each light
	numObjects =  world.lights.size();
	for (int j = 0; j < numObjects; j++) {
		if ( world.lights[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
			returnSr.t = testT;
			returnSr.hit_an_object = true;
			returnSr.material_ptr = testSr.material_ptr;
			returnSr.hit_point = ray.o + testT * ray.d;
			returnSr.normal = testSr.normal;
		}
	}

	closestIsectTimer.add(tp);
	return(returnSr);
}


bool Grid::shadow_intersection(const Ray& ray, double distToLight) {
	timespec tp;
	Timer::getTime(tp);

	double t;
	int numObjects =  world.primitives.size();

	for( int j = 0; j < numObjects; j++ ) {
		if ( world.primitives[j]->shadow_hit(ray, t) && t < distToLight) {
			shadowIsectTimer.add(tp);
			return true;
		}
	}

	shadowIsectTimer.add(tp);
	return false;
}
*/

Cell *Grid::get_cell(int x, int y, int z)
{
	return &cells[x + (y * gridRes.x) + (z * gridRes.x * gridRes.y)];
}


void Cell::addPrimitive(AbstractGeo *primitive)
{
	primitives.push_back(primitive);
}

bool Cell::intersectPrimitives(const Ray &ray, ShadeRec &returnSr, ShadeRec &testSr)
{
	returnSr.t = kHugeValue;

	// Test intersection of each primitive and keep the ShadeRec
	// of the closest intersection.
	uint numPrim = primitives.size();
	double testT;
	for (uint i = 0; i < numPrim; i++) {
		if ( primitives[i]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
			returnSr.t = testT;
			returnSr.hit_an_object = true;
			returnSr.material_ptr = primitives[i]->get_material();
			returnSr.hit_point = ray.o + testT * ray.d;
			returnSr.normal = testSr.normal;
		}
	}

	return returnSr.hit_an_object;
}
