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

	std::vector<Point3>		vertices;
	std::vector<Normal> 	normals;

};

#endif // MESHDATA_H
