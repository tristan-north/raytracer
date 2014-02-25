#include "raycast.h"
#include "tracers/raycast.h"
#include "world/world.h"
#include "utilities/shaderec.h"
#include "materials/abstractmaterial.h"

RayCast::RayCast(void) : AbstractTracer() {}
RayCast::RayCast(World* _worldPtr) : AbstractTracer(_worldPtr) {}

RGBColor RayCast::trace_ray(const Ray ray, uint rayDepth) const {
	if( rayDepth > world_ptr->settings.maxRayDepth )
		return 0;

	// Get the ShadeRec of the closest intersection of given ray with the world.
	ShadeRec sr = world_ptr->accelStruct_ptr->closest_intersection(ray);

	// If a primary ray, test ray against lights.
	if( rayDepth == 0 ) {
		double t;
		ShadeRec lightSr(*world_ptr);
		ShadeRec testSr(*world_ptr);
		lightSr.t = kHugeValue;
		uint numObjects = world_ptr->lights.size();
		for (uint i = 0; i < numObjects; i++) {
			if ( world_ptr->lights[i]->hit(ray, t, testSr) && (t < lightSr.t)) {
				lightSr.t = t;
				lightSr.hit_an_object = true;
				lightSr.material_ptr = testSr.material_ptr;
				lightSr.hit_point = ray.o + t * ray.d;
				lightSr.normal = testSr.normal;
			}
		}

		// If a light was hit and was closer than the geo hit.
		if( lightSr.hit_an_object && lightSr.t < sr.t )
			sr = lightSr;
	}

	if (sr.hit_an_object) {
		// u, v, w is used later to transform from shader to world space.
		sr.v = sr.normal;
		sr.w = sr.v ^ Vector3(0.0072, 1.0, 0.0034);     // Jitter up vector in case normal is vertical
		sr.w.normalize();
		sr.u = sr.w ^ sr.v;

		if( sr.material_ptr )
			return (sr.material_ptr->shade(sr, rayDepth));
		else
			return RGBColor(1, 0, 0);
	}
	else
		return (world_ptr->background_color);
}
