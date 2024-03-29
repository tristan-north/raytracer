#include "utilities/ray.h"

Ray::Ray (void) : o(0.0), d(0.0, 0.0, 1.0) {}

Ray::Ray (const Point3& origin, const Vector3& dir) : o(origin), d(dir) {}

Ray::Ray (const Ray& ray) : o(ray.o), d(ray.d) {}

Ray& Ray::operator= (const Ray& rhs)
{
	if (this == &rhs)
		return (*this);

	o = rhs.o;
	d = rhs.d;

	return (*this);
}

Ray::~Ray (void) {}



