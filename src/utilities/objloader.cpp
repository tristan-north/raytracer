#include <QtGlobal>
#include <fstream>
#include <assert.h>
#include <QDebug>
#include "objloader.h"
#include "geometricObjects/triangle.h"
#include "utilities/meshdata.h"
#include "materials/abstractmaterial.h"

using namespace std;

int ObjLoader::load(World& world, const string filepath, const MaterialsList& materialsList) {
	assert(materialsList.materials.size() > 0);
	AbstractMaterial* materialToAssign = materialsList.materials[0];

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
		if( line.length() < 1 )
			continue;

		// Process line defining vertices.
		if( line.at(0) == 'v') {
            if( line.at(1) == 't') {  // This is UV coord, ignore for now.
                continue;
            }
            if( line.at(1) == 'n') {  // This is normal, ignore for now.
                continue;
            }

			numbersAsStrings = getNumbersAsStrings(line);
			assert(numbersAsStrings.size() == 3);

			float v0 = atof(numbersAsStrings[0].c_str());
			float v1 = atof(numbersAsStrings[1].c_str());
			float v2 = atof(numbersAsStrings[2].c_str());

//			qDebug("(%.3f, %.3f, %.3f)", v0, v1, v2);
			meshData->vertices.push_back(Point3(v0, v1, v2));
		}
		// Process line defining faces.
		else if( line.at(0) == 'f' ) {
			numbersAsStrings = getNumbersAsStrings(line);

			assert(numbersAsStrings.size() > 2);

			int vIndex0 = atoi(numbersAsStrings[0].c_str());

			// Need to account for faces defined by more than 3 verts and convert
			// them to triangles. Number of triangles created is number of verts - 2.
			for( size_t i = 2; i < numbersAsStrings.size(); i++ ) {
				int vIndex1 = atoi(numbersAsStrings[i - 1].c_str());
				int vIndex2 = atoi(numbersAsStrings[i].c_str());

				// Need to -1 from the vertex index as in the .obj file they start at 1 not 0.
				Triangle* t = new Triangle(meshData, vIndex0-1, vIndex1-1, vIndex2-1);
				world.add_primitive(t);
				t->compute_normal();
				t->set_material(materialToAssign);

				numTriangles++;

//				qDebug("Added face with vertex indices: [%d][%d][%d]", vIndex0, vIndex1, vIndex2);
//				qDebug("(%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f)",
//					   meshData->vertices[vIndex0-1].x, meshData->vertices[vIndex0-1].y, meshData->vertices[vIndex0-1].z,
//					   meshData->vertices[vIndex1-1].x, meshData->vertices[vIndex1-1].y, meshData->vertices[vIndex1-1].z,
//					   meshData->vertices[vIndex2-1].x, meshData->vertices[vIndex2-1].y, meshData->vertices[vIndex2-1].z);
			}
		}
		// Process line defining group name.
		else if( line.at(0) == 'g' ) {
			string groupName = line.substr(2);
			materialToAssign = materialsList.materials[0];
			for( uint i = 0; i < materialsList.assignments.size(); i++ ) {
				if( materialsList.assignments[i] == groupName ) {
					materialToAssign = materialsList.materials[i];
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
//	qDebug("%s", line.c_str());

	int indexStart = 1;
	int indexEnd;
	vector<string> stringsList;
	while(true) {
		indexStart = line.find_first_not_of(" \r", indexStart);
		if( indexStart == -1 )
			break;

		indexEnd = line.find(' ', indexStart);
		stringsList.push_back(line.substr(indexStart, indexEnd - indexStart));
//		qDebug("%s", stringsList.back().c_str());

		indexStart = indexEnd;
	}

	return stringsList;
}

