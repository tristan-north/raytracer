#include <math.h>
#include "utilities/vector3.h"
#include "utilities/normal.h"
#include "utilities/point3.h"
#include "utilities/common.h"

// default constructor
Vector3::Vector3(void) : x(0.0), y(0.0), z(0.0) {}

// constructor
Vector3::Vector3(double a) : x(a), y(a), z(a) {}

// constructor
Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

// copy constructor
Vector3::Vector3(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

// constructs a vector from a normal
Vector3::Vector3(const Normal& n) : x(n.x), y(n.y), z(n.z) {}

// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions
Vector3::Vector3(const Point3& p) : x(p.x), y(p.y), z(p.z) {}

Vector3::~Vector3 (void) {}


Vector3& Vector3::operator= (const Vector3& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}

// assign a Normal to a vector
Vector3& Vector3::operator= (const Normal& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// assign a point to a vector
Vector3& Vector3::operator= (const Point3& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

Vector3 Vector3::rotateX(const float deg) const {
	float rad = PI * deg / 180;  // convert to radians

	Vector3 newVec;
	newVec.y = y * cos(rad) - z * sin(rad);
	newVec.z = y * sin(rad) + z * cos(rad);
	newVec.x = x;

	return newVec;
}

Vector3 Vector3::rotateY(const float deg) const {
	float rad = PI * deg / 180;  // convert to radians

	Vector3 newVec;
	newVec.z = z * cos(rad) - x * sin(rad);
	newVec.x = z * sin(rad) + x * cos(rad);
	newVec.y = y;

	return newVec;
}

Vector3 Vector3::rotateZ(const float deg) const {
	float rad = PI * deg / 180;  // convert to radians

	Vector3 newVec;
	newVec.x = x * cos(rad) - y * sin(rad);
	newVec.y = x * sin(rad) + y * cos(rad);
	newVec.z = z;

	return newVec;
}


// length of the vector
double Vector3::length(void) {
	return (sqrt(x * x + y * y + z * z));
}

// converts the vector to a unit vector
void Vector3::normalize(void) {
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}

// converts the vector to a unit vector and returns the vector
Vector3& Vector3::hat(void) {
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
	return (*this);
}


// non-member function
// multiplication by a matrix on the left
Vector3 operator* (const Matrix& mat, const Vector3& v) {
	return (Point3(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}
