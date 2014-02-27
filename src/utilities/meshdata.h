#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>
#include "utilities/point3.h"
#include "utilities/normal.h"

class MeshData
{
public:
    MeshData();
    ~MeshData();

	std::vector<Point3>		vertices;				// mesh vertices
//	vector<Normal> 			normals;				// average normal at each vertex;
//	vector<vector<int> > 	vertex_faces;			// the triangles shared by each vertex
//	int 					num_vertices; 			// number of vertices
//	int 					num_triangles; 			// number of triangles
};

#endif // MESHDATA_H
