#ifndef VECTOR3_H
#define VECTOR3_H

#include "utilities/matrix.h"

class Normal;
class Point3;

class Vector3
{

public:
	double	x, y, z;

	Vector3(void);											// default constructor
	Vector3(double a);										// constructor
	Vector3(double _x, double _y, double _z);				// constructor
	Vector3(const Vector3& v);								// copy constructor
	Vector3(const Normal& n);								// constructs a vector from a Normal
	Vector3(const Point3& p);								// constructs a vector from a point
	~Vector3 (void);										// destructor

	Vector3& operator= (const Vector3& rhs); 				// assignment operator
	Vector3& operator= (const Normal& rhs);					// assign a Normal to a vector
	Vector3& operator= (const Point3& rhs); 				// assign a Point3 to a vector
	Vector3	operator- (void) const;							// unary minus
	Vector3 operator* (const double a) const;				// multiplication by a double on the right
	Vector3	operator/ (const double a) const;				// division by a double
	Vector3	operator+ (const Vector3& v) const;				// addition
	Vector3& operator+= (const Vector3& v);					// compound addition
	Vector3	operator- (const Vector3& v) const;				// subtraction
	double operator* (const Vector3& b) const;				// dot product
	Vector3 operator^ (const Vector3& v) const;				// cross product

	Vector3 rotateX(const float deg) const;					// return a vector rotated by deg degrees around X axis
	Vector3 rotateY(const float deg) const;					// return a vector rotated by deg degrees around Y axis
	Vector3 rotateZ(const float deg) const;					// return a vector rotated by deg degrees around Z axis

	double length(void);									// length
    double len_squared(void) const;								// square of the length
	void normalize(void);									// convert vector to a unit vector
	Vector3& hat(void);										// return a unit vector, and normalize the vector
};


// inlined member functions

// unary minus
// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object
inline Vector3 Vector3::operator- (void) const {
	return (Vector3(-x, -y, -z));
}

// the square of the length
inline double Vector3::len_squared(void) const {
	return (x * x + y * y + z * z);
}

// multiplication by a double on the right
inline Vector3 Vector3::operator* (const double a) const {
	return (Vector3(x * a, y * a, z * a));
}

// division by a double
inline Vector3 Vector3::operator/ (const double a) const {
	return (Vector3(x / a, y / a, z / a));
}

// addition
inline Vector3 Vector3::operator+ (const Vector3& v) const {
	return (Vector3(x + v.x, y + v.y, z + v.z));
}

// subtraction
inline Vector3 Vector3::operator- (const Vector3& v) const {
	return (Vector3(x - v.x, y - v.y, z - v.z));
}

// dot product
inline double Vector3::operator* (const Vector3& v) const {
	return (x * v.x + y * v.y + z * v.z);
}

// cross product
inline Vector3 Vector3::operator^ (const Vector3& v) const {
    return (Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x));
}

// compound addition
inline Vector3& Vector3::operator+= (const Vector3& v) {
	x += v.x; y += v.y; z += v.z;
	return (*this);
}



// inlined non-member function

// multiplication by a double on the left
Vector3 operator* (const double a, const Vector3& v);

inline Vector3 operator* (const double a, const Vector3& v) {
	return (Vector3(a * v.x, a * v.y, a * v.z));
}



// non-inlined non-member function

// multiplication by a matrix on the left
Vector3 operator* (const Matrix& mat, const Vector3& v);


#endif // VECTOR3_H
