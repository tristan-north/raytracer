#ifndef BBOX_H
#define BBOX_H

#include "ray.h"
#include "point3.h"

class BBox
{
public:
	double xMin, xMax, yMin, yMax, zMin, zMax;
	BBox();
	BBox(const double xMin, const double xMax,
		const double yMin, const double yMax,
		const double zMin, const double zMax);
	BBox(const Point3 pMin, const Point3 pMax);

	bool hit(const Ray& ray, double& tmin) const;
	bool inside(const Point3& p) const;
	void expandToFit(const BBox& inBBox);
};

#endif // BBOX_H
