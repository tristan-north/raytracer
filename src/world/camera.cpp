#include <math.h>
#include "world/camera.h"
#include "world/viewplane.h"
#include "world/world.h"
#include "utilities/common.h"
#include "utilities/point3.h"
#include "utilities/vector3.h"
#include "utilities/rgbcolor.h"
#include "utilities/ray.h"


Camera::Camera(void)
	:	eye(0, 0, 500),
		lookat(0),
		ra(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1),
		d(500)
{}

Camera::Camera(const Camera& c)
	: 	eye(c.eye),
		lookat(c.lookat),
		ra(c.ra),
		up(c.up),
		u(c.u),
		v(c.v),
		w(c.w),
		d(c.d)

{}

Camera& Camera::operator= (const Camera& rhs) {
	if (this == &rhs)
		return (*this);

	eye				= rhs.eye;
	lookat			= rhs.lookat;
	ra				= rhs.ra;
	up				= rhs.up;
	u				= rhs.u;
	v				= rhs.v;
	w				= rhs.w;
	d				= rhs.d;


	return (*this);
}

Camera::~Camera(void) {}


// This computes an orthornormal basis given the view point, lookat point, and up vector
void Camera::compute_uvw(void) {
	w = eye - lookat;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;

	// take care of the singularity by hardwiring in specific camera orientations
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector3(0, 0, 1);
		v = Vector3(1, 0, 0);
		w = Vector3(0, 1, 0);
	}

	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector3(1, 0, 0);
		v = Vector3(0, 0, 1);
		w = Vector3(0, -1, 0);
	}
}


Vector3 Camera::get_direction(const Point2& p) const {
	Vector3 dir = p.x * u + p.y * v - d * w;
	dir.normalize();

	return(dir);
}
