#include "grid.h"
#include "utilities/common.h"
#include "utilities/timer.h"
#include "utilities/shaderec.h"
#include "world/world.h"

extern Timer isectTimer;

Grid::Grid(World *w) : AbstractAccel(w)
{

}


ShadeRec Grid::closest_intersection(const Ray& ray) {
	timespec tp;
	isectTimer.getTime(tp);

	ShadeRec returnSr(*world_ptr);
	returnSr.t = kHugeValue;

	// Test intersection of each geometric object and keep the ShadeRec
	// of the closest intersection.
	int numObjects = world_ptr->objects.size();
	ShadeRec testSr(*world_ptr);
	double testT;
	for (int j = 0; j < numObjects; j++) {
		if ( world_ptr->objects[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
			returnSr.t = testT;
			returnSr.hit_an_object = true;
			returnSr.material_ptr =  world_ptr->objects[j]->get_material();
			returnSr.hit_point = ray.o + testT * ray.d;
			returnSr.normal = testSr.normal;
			returnSr.local_hit_point = testSr.local_hit_point;
		}
	}

	// Test intersection of each light
	numObjects =  world_ptr->lights.size();
	for (int j = 0; j < numObjects; j++) {
		if ( world_ptr->lights[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
			returnSr.t = testT;
			returnSr.hit_an_object = true;
			returnSr.material_ptr = testSr.material_ptr;
			returnSr.hit_point = ray.o + testT * ray.d;
			returnSr.normal = testSr.normal;
			returnSr.local_hit_point = testSr.local_hit_point;
		}
	}

	isectTimer.add(tp);
	return(returnSr);
}

bool Grid::shadow_intersection(const Ray& ray, double distToLight) {
	timespec tp;
	isectTimer.getTime(tp);

	double t;
	int numObjects =  world_ptr->objects.size();

	for( int j = 0; j < numObjects; j++ ) {
		if ( world_ptr->objects[j]->shadow_hit(ray, t) && t < distToLight) {
			isectTimer.add(tp);
			return true;
		}
	}

	isectTimer.add(tp);
	return false;
}
