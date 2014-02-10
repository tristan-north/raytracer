#ifndef PLANE_H
#define PLANE_H

#include "geometricObjects/abstractgeo.h"

class Plane: public AbstractGeo
{
public:
    Plane();   												// default constructor
	Plane(const Point3& point, const Normal& normal);			// constructor
	Plane(const Plane& plane); 									// copy constructor
    virtual Plane* clone() const; 							// virtual copy constructor
    virtual ~Plane();										// destructor

	Plane& operator= (const Plane& rhs);						// assignment operator

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

private:
	Point3 	a;   				// point through which plane passes
	Normal 	n;					// normal to the plane

	static const double kEpsilon;   // for shadows and secondary rays
};
#endif // PLANE_H
