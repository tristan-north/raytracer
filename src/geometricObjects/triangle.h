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
	Triangle(MeshData* _meshPtr, const int i0, const int i1, const int i2);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;
	void compute_normal(const bool reverse_normal = false);
    Normal get_normal() const;
	virtual BBox get_bbox() const;

	MeshData* 	mesh_ptr;					// stores all the data
	int			index0, index1, index2;  	// indices into the vertices array in the mesh
	Normal		normal;
};

#endif // TRIANGLE_H
