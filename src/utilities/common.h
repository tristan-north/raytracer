#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <float.h>
#include <vector>
#include "utilities/vector3.h"
#include <cmath>

#pragma GCC diagnostic ignored "-Wunused-parameter"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.0001;
const double 	kHugeValue  = FLT_MAX;

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

inline float rand_float() {
	return (float)rand() / (float)RAND_MAX;
}

// This is the recommended way to get a vector to actually
// release its memory.
template <typename T>
inline void free_vector(std::vector<T>& toFree) {
	uint numItems = toFree.size();
	for (uint i = 0; i < numItems; i++) {
		delete toFree[i];
		toFree[i] = NULL;
	}

	toFree.erase(toFree.begin(), toFree.end());

	std::vector<T> v;
	v.swap(toFree);
}

inline Vector3 get_uniform_hemisphere_sample() {
	float rnd1 = rand_float();
	float rnd2 = rand_float();

	float sin_theta = sqrt(1 - rnd1*rnd1);
	float phi = 2 * PI * rnd2;

	Vector3 dir;
	dir.x = sin_theta * sin(phi);
	dir.y = rnd1;
	dir.z = sin_theta * cos(phi);

	return dir;
}

inline Vector3 get_cosine_hemisphere_sample() {
	float rnd1 = rand_float();
	float rnd2 = rand_float();

	float r = sqrt(rnd1);
	float theta = 2 * PI * rnd2;

	Vector3 dir;
	dir.x = r * cos(theta);
	dir.y = sqrt(std::max(0.0f, 1-rnd1));
	dir.z = r * sin(theta);

	return dir;
}

#endif // COMMON_H
