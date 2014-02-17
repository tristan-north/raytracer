#include <QApplication>
#include "window.h"
#include "utilities/timer.h"

ulong g_numPrimaryRays = 0;
ulong g_numLightRays = 0;
Timer closestIsectTimer;
Timer shadowIsectTimer;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Window window;
	window.show();
    window.startRender();

	return app.exec();
}

/*
TODO:

 - Optimise grid intersection for shadow rays. eg make use of maxT.
 - Check grid intersection code against scratchapixel.


 - Implement multi-jittered sampling as recommended by Max.
 - Use Intel IPP for vectors, image manipulation etc.
 - Implement hilbert bucket ordering http://en.wikipedia.org/wiki/Space-filling_curve
 - Implement intersection acceleration structure
 - Add multiple bounces



 Basic program flow:
 - World::render_scanline() gets called which calls tracer_ptr->trace_ray() for each subpixel which returns the final subpixel color.
 - trace_ray() calls world_ptr->hit_objects() with the ray direction which goes through each object in the scene calling its hit() function.
 - If an object is hit material_ptr->shade() is called on the closest hit object.
 - material_ptr->shade() then goes through each light adding up the light contributions. To get shadows each light has its in_shadow() function called.
 - Light::in_shadow() goes through each object calling shadow_hit() which returns a bool.


*/
