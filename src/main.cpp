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
 - Check book on how to add indirect.
 - Make lights hitable in grid only for primary rays.


 - Implement multi-jittered sampling as recommended by Max.
 - Use Intel IPP for vectors, image manipulation etc.
 - Implement hilbert bucket ordering http://en.wikipedia.org/wiki/Space-filling_curve
 - Implement BVH
 - Add multiple bounces



 Basic program flow:
 - World::render_scanline() gets called which calls tracer_ptr->trace_ray() for each subpixel which returns the final subpixel color.
 - trace_ray() calls accelStruct_ptr->closest_intersection() which returns a shadeRec with data at hitpoint needed for shading.
 - If an object is hit material_ptr->shade() is called.
 - material_ptr->shade() then goes through each light adding up the light contributions, calling accelStruct_ptr->shadow_intersection().



PAPERS REFERENCED

Grid acceleration structure:

"A Parallel Ray Tracing Computer", Cleary 1983
Computing the optimal grid resolution.

"Ray Tracing Animated Scenes using Coherent Grid Traversal", Wald 2006
Also computing the optimal grid resolution.

"ARTS: Accelerated Ray Tracing Systems", Akira Fujimoto 1986
Initial paper on grid acceleration. Explains the 3D-Digital Differential Analyser (or DDA)
grid traversal method.

*/
