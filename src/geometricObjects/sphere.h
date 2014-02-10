#ifndef SPHERE_H
#define SPHERE_H

#include "geometricObjects/abstractgeo.h"

class Sphere: public AbstractGeo
{
public:
    Sphere();   									// Default constructor
	Sphere(Point3 center, double r);					// Constructor
	Sphere(const Sphere& sphere); 						// Copy constructor
    virtual Sphere* clone() const; 					// Virtual copy constructor
    virtual	~Sphere();								// Destructor

	Sphere& operator= (const Sphere& sphere);			// assignment operator

	void set_center(const Point3& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, double& t) const;

private:
	Point3 center;					// center coordinates as a point
	double radius;					// the radius
	static const double kEpsilon;   // for shadows and secondary rays
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
