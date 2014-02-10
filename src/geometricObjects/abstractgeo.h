#ifndef ABSTRACTGEO_H
#define ABSTRACTGEO_H

#include "utilities/point3.h"
#include "utilities/ray.h"
#include "utilities/shaderec.h"

class AbstractMaterial;

class AbstractGeo
{
public:

    AbstractGeo();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
	virtual bool shadow_hit(const Ray& ray, double& t) const = 0;
    AbstractMaterial* get_material() const;

    virtual void set_material(AbstractMaterial* mPtr); // needs to virtual so that it can be overriden in Compound


protected:
    mutable AbstractMaterial* material_ptr; // mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
};


inline AbstractMaterial* AbstractGeo::get_material() const {
	return (material_ptr);
}

#endif // ABSTRACTGEO_H
