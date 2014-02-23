#ifndef RAYCAST_H
#define RAYCAST_H

#include "tracers/abstracttracer.h"

class RayCast: public AbstractTracer {
public:

	RayCast(void);
	RayCast(World* _worldPtr);
	virtual	~RayCast(void);

	virtual RGBColor trace_ray(const Ray ray, uint rayDepth) const;
};

#endif // RAYCAST_H
