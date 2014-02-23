#ifndef ABSTRACTACCEL_H
#define ABSTRACTACCEL_H

#include "utilities/shaderec.h"

class World;

class AbstractAccel
{
public:
	AbstractAccel(World& w);
	virtual ~AbstractAccel() {}

	virtual ShadeRec closest_intersection(const Ray& ray) = 0;
	virtual bool shadow_intersection(const Ray& ray, double distToLight) = 0;

	World& world;

private:
};

#endif // ABSTRACTACCEL_H
