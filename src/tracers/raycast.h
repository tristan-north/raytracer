#ifndef RAYCAST_H
#define RAYCAST_H

#include "tracers/abstracttracer.h"

class RayCast: public AbstractTracer {
public:
	RayCast(World& _world);

	virtual RGBColor trace_ray(const Ray ray, uint rayDepth) const;
};

#endif // RAYCAST_H
