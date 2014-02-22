#include <math.h>
#include "world/camera.h"
#include "utilities/common.h"



Camera::Camera() : fov(60)
{}

void Camera::set_transform(const float tx, const float ty, const float tz,
						   const float rx, const float ry, const float rz)
{
	camMatrix.translate(tx, ty, tz);
	camMatrix.rotateByDeg(rx, ry, rz);
}

Point3 Camera::get_eye_pos()
{
	return camMatrix * Point3(0, 0, 0);
}

Point3 Camera::cam_to_world(Point3 p)
{
	return camMatrix * p;
}



