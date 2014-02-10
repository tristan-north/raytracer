#ifndef POINT3_H
#define POINT3_H

#include "utilities/matrix.h"
#include "utilities/vector3.h"

class Point3
{

public:
	double x, y, z;

	Point3();													// default constructor
	Point3(const double a);										// constructor
	Point3(const double a, const double b, const double c);		// constructor

    Point3 operator- (void) const;								// unary minus
	Vector3 operator- (const Point3& p) const;					// vector joining two points
	Point3 operator+ (const Vector3& v) const;					// addition of a vector
	Point3 operator- (const Vector3& v) const;					// subtraction of a vector
	Point3 operator* (const double a) const; 					// multiplication by a double on the right

	double d_squared(const Point3& p) const;					// square of distance bertween two points
	double distance(const Point3& p) const;						// distance bewteen two points
};


// inlined member functions
inline Point3 Point3::operator- (void) const {
	return (Point3(-x, -y, -z));
}

inline Vector3 Point3::operator- (const Point3& p) const {
	return (Vector3(x - p.x,y - p.y,z - p.z));
}

inline Point3 Point3::operator+ (const Vector3& v) const {
	return (Point3(x + v.x, y + v.y, z + v.z));
}


inline Point3 Point3::operator- (const Vector3& v) const {
	return (Point3(x - v.x, y - v.y, z - v.z));
}

inline Point3 Point3::operator* (const double a) const {
	return (Point3(x * a,y * a,z * a));
}

inline double Point3::d_squared(const Point3& p) const {
	return (	(x - p.x) * (x - p.x)
			+ 	(y - p.y) * (y - p.y)
			+	(z - p.z) * (z - p.z) );
}

// inlined non-member function
Point3 operator* (double a, const Point3& p);

inline Point3 operator* (double a, const Point3& p) {
	return (Point3(a * p.x, a * p.y, a * p.z));
}


// non-inlined non-member function
Point3 operator* (const Matrix& mat, const Point3& p);


#endif // POINT3_H
