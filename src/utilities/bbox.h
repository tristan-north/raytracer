#ifndef BBOX_H
#define BBOX_H

#include "ray.h"
#include "point3.h"

class BBox
{
public:
	double x0, x1, y0, y1, z0, z1;
	BBox(void);
	BBox(	const double x0, const double x1,
			const double y0, const double y1,
			const double z0, const double z1);
	BBox(const Point3 p0, const Point3 p1);
	BBox(const BBox& bbox);
	BBox& operator= (const BBox& rhs);
	~BBox(void);

	bool hit(const Ray& ray) const;
	bool inside(const Point3& p) const;
};

#endif // BBOX_H
