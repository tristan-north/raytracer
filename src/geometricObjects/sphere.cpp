#include <math.h>
#include "geometricObjects/sphere.h"
#include "utilities/common.h"


Sphere::Sphere()
	: 	AbstractGeo(),
		center(0.0),
		radius(1.0)
{}

Sphere::Sphere(Point3 c, double r)
	: 	AbstractGeo(),
		center(c),
		radius(r)
{}


// hit
bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3		temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			return (true);
		}
	}

	return (false);
}

bool Sphere::shadow_hit(const Ray& ray, double& tmin) const {
	double 		t;
	Vector3		temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}
	}

	return (false);
}

BBox Sphere::get_bbox() const
{
	return BBox(center.x - radius - kEpsilon,
				center.x + radius + kEpsilon,
				center.y - radius - kEpsilon,
				center.y + radius + kEpsilon,
				center.z - radius - kEpsilon,
				center.z + radius + kEpsilon);
}






