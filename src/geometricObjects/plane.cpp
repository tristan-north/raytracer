#include "geometricObjects/plane.h"

const double Plane::kEpsilon = 0.001;

//  default constructor
Plane::Plane() : AbstractGeo(), a(0.0), n(0, 1, 0) {}

//  constructor
Plane::Plane(const Point3& point, const Normal& normal)
	:	AbstractGeo(),
		a(point),
		n(normal)
{
		n.normalize();
}

// copy constructor
Plane::Plane(const Plane& plane)
	:	AbstractGeo(plane),
		a(plane.a),
		n(plane.n)
{}

// destructor
Plane::~Plane() {}

// clone
Plane* Plane::clone() const {
	return (new Plane(*this));
}

Plane& Plane::operator= (const Plane& rhs)	{

	if (this == &rhs)
		return (*this);

	AbstractGeo::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	float t = (a - ray.o) * n / (ray.d * n);

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;

		return (true);
	}

	return(false);
}

bool Plane::shadow_hit(const Ray& ray, double& tmin) const {
	float t = (a - ray.o) * n / (ray.d * n);

	if (t > kEpsilon) {
		tmin = t;
		return (true);
	}
	return(false);
}
