#include <QtGlobal>
#include "world/world.h"
#include "geometricObjects/plane.h"
#include "geometricObjects/sphere.h"
#include "geometricObjects/triangle.h"
#include "tracers/raycast.h"
#include "world/camera.h"
#include "lights/rectlight.h"
#include "lights/envlight.h"
#include "materials/matte.h"
#include "materials/occlusion.h"
#include "utilities/bbox.h"
#include "utilities/meshdata.h"
#include "utilities/vector3.h"
#include "utilities/point3.h"
#include "utilities/normal.h"
#include "utilities/shaderec.h"
#include "utilities/common.h"
#include "utilities/objloader.h"
#include "utilities/timer.h"
#include "build/BuildShadedObjects.h"


extern ulong g_numPrimaryRays;
extern Timer isectTimer;

// default constructor
World::World() : background_color(0), tracer_ptr(NULL), camera_ptr(NULL) {}

// destructor
World::~World() {
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}

	delete_objects();
	delete_lights();
    delete_materials();
    delete_meshDatas();
}


void World::render_scanline(int scanlineNum) {
	RGBColor	pixel_color;
	Ray			ray;
	int 		depth = 0;
	Point2		pp;		// sample point on a pixel
	int n = (int)sqrt((float)vp.num_samples);

	ray.o = camera_ptr->get_eye();

	for (int x = 0; x < vp.hres; x++) {		// across
		pixel_color = 0;

		for (int p = 0; p < n; p++)			// up sub pixel
			for (int q = 0; q < n; q++) {	// across sub pixel
				pp.x = x - 0.5 * vp.hres + (q + 0.5) / n;
				pp.y = 0.5 * vp.vres - scanlineNum + (p + 0.5) / n;
				// Use basic jittered sampling
//				pp.x = x - 0.5 * vp.hres + (q + rand_float()) / n;
//				pp.y = 0.5 * vp.vres - scanlineNum + (p + rand_float()) / n;

				ray.d = camera_ptr->get_direction(pp);
                pixel_color += tracer_ptr->trace_ray(ray, depth);
                __sync_add_and_fetch(&g_numPrimaryRays, 1);
			}

		pixel_color /= vp.num_samples;
		display_pixel(scanlineNum, x, pixel_color);
	}

}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	// do gamma
	if (vp.gamma != 1.0)
		mapped_color = raw_color.powc(vp.inv_gamma);
	else
		mapped_color = raw_color;

	// clamp to 1
	mapped_color.r = min(mapped_color.r, 1.0f);
	mapped_color.g = min(mapped_color.g, 1.0f);
	mapped_color.b = min(mapped_color.b, 1.0f);

	// map to 0-255
	int displayR = int((mapped_color.r * 255) + 0.5);
	int displayG = int((mapped_color.g * 255) + 0.5);
	int displayB = int((mapped_color.b * 255) + 0.5);

	int x = column;
	int y = row;

	screen_buffer[x + (y * vp.hres)] = (displayR << 16) + (displayG << 8) + displayB;
}


ShadeRec World::closest_intersection(const Ray& ray) {
    timespec tp;
    isectTimer.getTime(tp);

    ShadeRec returnSr(*this);
    returnSr.t = kHugeValue;

    // Test intersection of each geometric object and keep the ShadeRec
    // of the closest intersection.
    int numObjects = objects.size();
    ShadeRec testSr(*this);
    double testT;
    for (int j = 0; j < numObjects; j++) {
        if (objects[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
            returnSr.t = testT;
            returnSr.hit_an_object = true;
            returnSr.material_ptr = objects[j]->get_material();
            returnSr.hit_point = ray.o + testT * ray.d;
            returnSr.normal = testSr.normal;
            returnSr.local_hit_point = testSr.local_hit_point;
        }
    }

    // Test intersection of each light
    numObjects = lights.size();
    for (int j = 0; j < numObjects; j++) {
        if (lights[j]->hit(ray, testT, testSr) && (testT < returnSr.t)) {
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


bool World::shadow_intersection(const Ray& ray, double distToLight) {
    timespec tp;
    isectTimer.getTime(tp);

    double t;
    int numObjects = objects.size();

    for( int j = 0; j < numObjects; j++ ) {
        if (objects[j]->shadow_hit(ray, t) && t < distToLight) {
            isectTimer.add(tp);
            return true;
        }
    }

    isectTimer.add(tp);
    return false;
}


void World::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

    objects.erase(objects.begin(), objects.end());
}


void World::delete_lights(void) {
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}

    lights.erase(lights.begin(), lights.end());
}


void World::delete_materials(void) {
    int num_materials = materials.size();

    for (int j = 0; j < num_materials; j++) {
        delete materials[j];
        materials[j] = NULL;
    }

    materials.erase(materials.begin(), materials.end());

}


void World::delete_meshDatas(void) {
    int num_meshDatas = meshDatas.size();

    for (int j = 0; j < num_meshDatas; j++) {
        delete meshDatas[j];
        meshDatas[j] = NULL;
    }

    meshDatas.erase(meshDatas.begin(), meshDatas.end());

}