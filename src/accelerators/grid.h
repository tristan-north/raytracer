#ifndef GRID_H
#define GRID_H

#include "abstractaccel.h"

class Grid : public AbstractAccel
{
public:
	Grid(World* w);

	virtual ShadeRec closest_intersection(const Ray& ray);
	virtual bool shadow_intersection(const Ray& ray, double distToLight);
};

#endif // GRID_H
