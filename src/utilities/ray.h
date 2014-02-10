#ifndef RAY_H
#define RAY_H

#include "utilities/point3.h"
#include "utilities/vector3.h"

class Ray
{
public:

	Point3 o;			// origin
	Vector3 d; 		// direction

	Ray(void);
	Ray(const Point3& origin, const Vector3& dir);
	Ray(const Ray& ray);
	~Ray(void);

	Ray& operator= (const Ray& rhs);
};

#endif // RAY_H
