#include <QtGlobal>
#include <fstream>
#include <assert.h>
#include <QDebug>
#include <algorithm>
#include "objloader.h"
#include "geometricObjects/triangle.h"
#include "utilities/meshdata.h"
#include "materials/abstractmaterial.h"

using namespace std;

int ObjLoader::load(World& world, const string filepath) {
	assert(world.materials.size() > 0);
	AbstractMaterial* materialToAssign = world.materials[0];

	ifstream file;
	file.open(filepath.c_str());

	if( !file.is_open() ) {
		qCritical("File %s can't be opened.", filepath.c_str());
		return 0;
	}

	qDebug("Loading: %s", filepath.c_str());

	MeshData* meshData = new MeshData;
    world.add_meshData(meshData);

    ulong numTriangles = 0;
	string line;
	vector<string> numbersAsStrings;
	while( file.good() ) {
		getline(file, line);
		if( line.length() < 4 )
			continue;

		// Process line defining vertex.
		if( line.at(0) == 'v' && line.at(1) == ' ') {
			numbersAsStrings = getNumbersAsStrings(line);
			assert(numbersAsStrings.size() == 3);

			float x = atof(numbersAsStrings[0].c_str());
			float y = atof(numbersAsStrings[1].c_str());
			float z = atof(numbersAsStrings[2].c_str());

			meshData->vertices.push_back(Point3(x, y, z));
		}

		// Process line defining normal.
		else if( line.at(0) == 'v' && line.at(1) == 'n') {
			numbersAsStrings = getNumbersAsStrings(line);
			assert(numbersAsStrings.size() == 3);

			float x = atof(numbersAsStrings[0].c_str());
			float y = atof(numbersAsStrings[1].c_str());
			float z = atof(numbersAsStrings[2].c_str());

			meshData->normals.push_back(Normal(x, y, z));
		}
		// Process line defining face.
		else if( line.at(0) == 'f' ) {
			// Need to -1 from indicies in obj file as they start at 1 not 0.
			uint vIndex0=0, vIndex1=0, vIndex2=0, nIndex0=0, nIndex1=0, nIndex2=0;
			numbersAsStrings = getNumbersAsStrings(line);
			assert(numbersAsStrings.size() > 2);

			// If face defined contains normal index.
			bool normalIsDefined = false;
			if( count(numbersAsStrings[0].begin(), numbersAsStrings[0].end(), '/') == 2) {
				normalIsDefined = true;
			}

			vIndex0 = atoi(numbersAsStrings[0].c_str())-1;
			if(normalIsDefined) nIndex0 = getNormalIndexFromString(numbersAsStrings[0])-1;

			// Need to account for faces defined by more than 3 verts and convert
			// them to triangles. Number of triangles created is number of verts -2.
			for( size_t i = 2; i < numbersAsStrings.size(); i++ ) {
				vIndex1 = atoi(numbersAsStrings[i - 1].c_str())-1;
				vIndex2 = atoi(numbersAsStrings[i].c_str())-1;

				if(normalIsDefined) {
					nIndex1 = getNormalIndexFromString(numbersAsStrings[i - 1])-1;
					nIndex2 = getNormalIndexFromString(numbersAsStrings[i])-1;
				}
				else {
					Normal normal;
					computeNormal(meshData->vertices[vIndex0], meshData->vertices[vIndex1], meshData->vertices[vIndex2], normal);
					meshData->normals.push_back(normal);

					nIndex0 = nIndex1 = nIndex2 = meshData->normals.size()-1;
				}

				Triangle* t = new Triangle(meshData, vIndex0, vIndex1, vIndex2,
													 nIndex0, nIndex1, nIndex2);
				world.add_primitive(t);
				t->set_material(materialToAssign);

				numTriangles++;
			}
		}
		// Process line defining group name.
		else if( line.at(0) == 'g' ) {
			string groupName = line.substr(2);
			materialToAssign = world.materials[0];
			for( uint i = 0; i < world.materials.size(); i++ ) {
				if( world.materials[i]->assignment == groupName ) {
					materialToAssign = world.materials[i];
					break;
				}
			}
		}
	}
	file.close();

    qDebug("Triangles: %ld", numTriangles);

	return 1;
}

vector<string> ObjLoader::getNumbersAsStrings(const string& line) {
	int indexStart = line.find(' ');
	int indexEnd;
	vector<string> stringsList;
	while(true) {
		indexStart = line.find_first_not_of(" \r", indexStart);
		if( indexStart == -1 )
			break;

		indexEnd = line.find(' ', indexStart);
		stringsList.push_back(line.substr(indexStart, indexEnd - indexStart));

		indexStart = indexEnd;
	}

	return stringsList;
}

void ObjLoader::computeNormal(const Point3 &v0, const Point3 &v1, const Point3 &v2, Normal &normal) {
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

uint ObjLoader::getNormalIndexFromString(const string &str)
{
	return atoi(str.substr(str.find_last_of('/') + 1).c_str());
}


