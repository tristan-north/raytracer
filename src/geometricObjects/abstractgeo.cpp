#include "geometricObjects/abstractgeo.h"
#include "materials/abstractmaterial.h"

// default constructor
AbstractGeo::AbstractGeo() : material_ptr(0) {}

// set_material
void AbstractGeo::set_material(AbstractMaterial* mPtr) {
	material_ptr = mPtr;
}
