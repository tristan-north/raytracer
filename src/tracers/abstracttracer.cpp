#include "abstracttracer.h"


AbstractTracer::AbstractTracer(void) : world_ptr(0) {}
AbstractTracer::AbstractTracer(World* _worldPtr) : world_ptr(_worldPtr) {}


RGBColor AbstractTracer::trace_ray(const Ray ray, uint rayDepth) const {
	return (0);
}

