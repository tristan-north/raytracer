#ifndef CAMERA_H
#define CAMERA_H

#include "utilities/point3.h"
#include "utilities/vector3.h"
#include "utilities/point2.h"

class World;  // can't #include "World" here because World contains a camera pointer

class Camera
{
public:

	Camera();
	Camera(const Camera& camera);			// copy constructor
	~Camera();

	void set_eye(const Point3& p);
	void set_eye(const float x, const float y, const float z);
	void set_lookat(const Point3& p);
	void set_lookat(const float x, const float y, const float z);
	void set_up_vector(const Vector3& u);
	void set_up_vector(const float x, const float y, const float z);
	void set_roll(const float ra);
	void compute_uvw(void);
	void set_view_distance(const float vpd);
	void set_zoom(const float zoom_factor);
	Vector3 get_direction(const Point2& p) const;
	Point3 get_eye(void) const;

protected:

	Point3		eye;				// eye point
	Point3		lookat; 			// lookat point
	float		ra;					// roll angle
	Vector3		up;					// up vector
	Vector3		u, v, w;			// orthonormal basis vectors
	float		d;					// view plane distance

	Camera& operator= (const Camera& camera);
};


// inlined access functions
inline void Camera::set_eye(const Point3& p) {
	eye = p;
}

inline void Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x; eye.y = y; eye.z = z;
}

inline void Camera::set_lookat(const Point3& p) {
	lookat = p;
}

inline void Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x; lookat.y = y; lookat.z = z;
}

inline void Camera::set_up_vector(const Vector3& u) {
	up = u;
}

inline void Camera::set_up_vector(const float x, const float y, const float z) {
	up.x = x; up.y = y; up.z = z;
}

inline void Camera::set_roll(const float r) {
	ra = r;
}

inline void Camera::set_view_distance(float _d) {
	d = _d;
}

inline Point3 Camera::get_eye(void) const {
	return eye;
}

#endif // CAMERA_H
