#include "abstracttracer.h"


AbstractTracer::AbstractTracer(void) : world_ptr(0) {}
AbstractTracer::AbstractTracer(World* _worldPtr) : world_ptr(_worldPtr) {}

AbstractTracer::~AbstractTracer(void) {
	if (world_ptr)
		world_ptr = 0;
}


RGBColor AbstractTracer::trace_ray(const Ray ray, const int depth) const {
	return (0);
}

