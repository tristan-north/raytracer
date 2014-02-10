#include <math.h>
#include "geometricObjects/sphere.h"

const double Sphere::kEpsilon = 0.001;

// default constructor
Sphere::Sphere()
	: 	AbstractGeo(),
		center(0.0),
		radius(1.0)
{}

// constructor
Sphere::Sphere(Point3 c, double r)
	: 	AbstractGeo(),
		center(c),
		radius(r)
{}

// clone
Sphere* Sphere::clone() const {
	return (new Sphere(*this));
}

// copy constructor
Sphere::Sphere (const Sphere& sphere)
	: 	AbstractGeo(sphere),
		center(sphere.center),
		radius(sphere.radius)
{}

// assignment operator
Sphere& Sphere::operator= (const Sphere& rhs)
{
	if (this == &rhs)
		return (*this);

	AbstractGeo::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}

// destructor
Sphere::~Sphere() {}

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
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
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






