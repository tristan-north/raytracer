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

	float fov;

	void set_transform(const float tx, const float ty, const float tz,
					   const float rx, const float ry, const float rz);
	Point3 get_eye_pos();
	Point3 cam_to_world(Point3 p);

private:
	Matrix camMatrix;

};

#endif // CAMERA_H
