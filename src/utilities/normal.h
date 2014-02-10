#ifndef NORMAL_H
#define NORMAL_H

#include "utilities/matrix.h"
#include "utilities/vector3.h"
#include "utilities/point3.h"

class Normal
{

public:
	double	x, y, z;

	Normal(void);										// default constructor
	Normal(double a);									// constructor
	Normal(double _x, double _y, double _z);			// constructor
	Normal(const Normal& n); 							// copy constructor
	Normal(const Vector3& v);							// constructs a normal from vector
	~Normal(void);										// destructor

	Normal& operator= (const Normal& rhs);				// assignment operator
	Normal& operator= (const Vector3& rhs);				// assignment of a vector to a normal
	Normal& operator= (const Point3& rhs);				// assignment of a point to a normal
	Normal operator- (void) const;						// unary minus
	Normal operator+ (const Normal& n) const;			// addition
	Normal& operator+= (const Normal& n);				// compound addition
	double operator* (const Vector3& v) const;			// dot product with a vector on the right
	Normal operator* (const double a) const;			// multiplication by a double on the right

	void normalize(void);								// convert normal to a unit normal
};





// inlined member functions

// unary minus
inline Normal Normal::operator- (void) const {
	return (Normal(-x, -y, -z));
}

// addition of two normals
inline Normal Normal::operator+ (const Normal& n) const {
	return (Normal(x + n.x, y + n.y, z + n.z));
}

// compound addition of two normals
inline Normal& Normal::operator+= (const Normal& n) {
	x += n.x; y += n.y; z += n.z;
	return (*this);
}

// dot product of a normal on the left and a vector on the right
inline double Normal::operator* (const Vector3& v) const {
	return (x * v.x + y * v.y + z * v.z);
}

// multiplication by a double on the right
inline Normal Normal::operator* (const double a) const {
	return (Normal(x * a, y * a, z * a));
}


// inlined non-member functions

// multiplication by a double on the left
Normal operator* (const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.x, f * n.y,f * n.z));
}


// addition of a vector on the left to return a vector
Vector3 operator+ (const Vector3& v, const Normal& n);

inline Vector3 operator+ (const Vector3& v, const Normal& n) {
	return (Vector3(v.x + n.x, v.y + n.y, v.z + n.z));
}


// subtraction of a normal from a vector to return a vector
Vector3 operator- (const Vector3&, const Normal& n);

inline Vector3 operator- (const Vector3& v, const Normal& n) {
	return (Vector3(v.x - n.x, v.y - n.y, v.z - n.z));
}


// dot product of a vector on the left and a normal on the right
double operator* (const Vector3& v, const Normal& n);

inline double operator* (const Vector3& v, const Normal& n) {
	return (v.x * n.x + v.y * n.y + v.z * n.z);
}



// non-inlined non-member function

// multiplication by a matrix on the left
Normal operator* (const Matrix& mat, const Normal& n);


#endif // NORMAL_H
