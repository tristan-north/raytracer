#include "raycast.h"
#include "tracers/raycast.h"
#include "world/world.h"
#include "utilities/shaderec.h"
#include "materials/abstractmaterial.h"

RayCast::RayCast(void) : AbstractTracer() {}
RayCast::RayCast(World* _worldPtr) : AbstractTracer(_worldPtr) {}
RayCast::~RayCast(void) {}


// this ignores the depth argument for now
RGBColor RayCast::trace_ray(const Ray ray, const int depth) const {
    // Get the ShadeRec of the closest intersection of given ray with the world.
    ShadeRec sr(world_ptr->closest_intersection(ray));

	if (sr.hit_an_object) {
		if( sr.material_ptr )
			return (sr.material_ptr->shade(sr));
		else
			return RGBColor(1, 0, 0);
	}
	else
		return (world_ptr->background_color);
}
