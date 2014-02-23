#ifndef SPHERE_H
#define SPHERE_H

#include "geometricObjects/abstractgeo.h"

class Sphere: public AbstractGeo
{
public:
	Sphere();
	Sphere(Point3 center, double r);

	void set_center(const Point3& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, double& t) const;
	virtual BBox get_bbox() const;

private:
	Point3 center;
	double radius;
};


inline void Sphere::set_center(const Point3& c) {
	center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Sphere::set_radius(const double r) {
	radius = r;
}


#endif // SPHERE_H
