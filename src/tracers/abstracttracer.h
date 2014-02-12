#ifndef ABSTRACTTRACER_H
#define ABSTRACTTRACER_H

// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#include "utilities/ray.h"
#include "utilities/rgbcolor.h"
#include "utilities/common.h"

class World;

class AbstractTracer
{
public:

    AbstractTracer(void);
    AbstractTracer(World* _world_ptr);
    virtual ~AbstractTracer(void);

	virtual RGBColor trace_ray(const Ray ray, const int depth) const;

protected:
	World* world_ptr;
};

#endif // ABSTRACTTRACER_H
