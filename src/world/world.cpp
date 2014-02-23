#include <QtGlobal>
#include "world/world.h"
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
#include "accelerators/grid.h"
#include "buildscene.h"


extern ulong g_numPrimaryRays;


World::World() : accelStruct_ptr(NULL),
				background_color(0),
				tracer_ptr(NULL)
{
	settings.pixelSamples = 1;
	settings.maxRayDepth = 2;
}

void World::cleanup() {
	if (accelStruct_ptr) {
		delete accelStruct_ptr;
		accelStruct_ptr = NULL;
	}

	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	free_vector(primitives);
	free_vector(lights);
	free_vector(materials);
	free_vector(meshDatas);
}


void World::render_scanline(int scanlineNum) {
	RGBColor pixel_color;
	Ray ray;
	Point2 pp;		// sample point
	const float aspectRatio = float(g_hres)/g_vres;
	const float viewAngle = tan(camera.fov * 0.5 * M_PI / 180);

	ray.o = camera.get_eye_pos();

	for (uint x = 0; x < g_hres; x++) {
		pixel_color = 0;

		for (uint p = 0; p < settings.pixelSamples; p++)			// up sub pixel
			for (uint q = 0; q < settings.pixelSamples; q++) {	// across sub pixel
				// move to center of pixel
				pp.x = x + 0.5;
				pp.y = scanlineNum + 0.5;

				// randomize position within pixel
				pp.x += ::rand_float() - 0.5;
				pp.y += ::rand_float() - 0.5;

				// remap from pixel coords (raster) to screen space (-1 to 1).
				pp.x = 2*pp.x / g_hres - 1;
				pp.y = 1 - 2*pp.y / g_vres;

				// remap from screen space to cam space (pp.z is always -1).
				pp.x *= viewAngle * aspectRatio;
				pp.y *= viewAngle;

				ray.d = camera.cam_to_world(Point3(pp.x, pp.y, -1)) - ray.o;
				ray.d.normalize();

				pixel_color += tracer_ptr->trace_ray(ray, 0);
                __sync_add_and_fetch(&g_numPrimaryRays, 1);
			}

		pixel_color /= settings.pixelSamples*settings.pixelSamples;
		display_pixel(scanlineNum, x, pixel_color);
	}

}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	// do gamma
	mapped_color = raw_color.powc(0.45);  // 2.2 gamma

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

	screen_buffer[x + (y * g_hres)] = (displayR << 16) + (displayG << 8) + displayB;
}
