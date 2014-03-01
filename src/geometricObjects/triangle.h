#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "geometricObjects/abstractgeo.h"
#include "utilities/meshdata.h"
#include "utilities/bbox.h"
#include "utilities/shaderec.h"

class Triangle : public AbstractGeo
{
public:
    Triangle();
	Triangle(MeshData* _meshPtr, const uint v0, const uint v1, const uint v2,
								 const uint n0, const uint n1, const uint n2);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;
	virtual BBox get_bbox() const;

private:
	MeshData* 	mesh_ptr;					// stores all the data
	uint		vIndex0, vIndex1, vIndex2;  // indices into the vertices array in the meshData
	uint		nIndex0, nIndex1, nIndex2;  // indices into the normals array in the meshData
};

#endif // TRIANGLE_H
