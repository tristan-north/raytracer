#include "envlight.h"
#include "utilities/common.h"
#include "world/world.h"
#include <cmath>

using namespace std;

EnvLight::EnvLight() : AbstractLight()
{
}


bool EnvLight::hit(const Ray& ray, double& tmin, ShadeRec &sr) const {
    return false;
}


Vector3 EnvLight::get_direction(const ShadeRec &sr) {
	Vector3 dir = get_cosine_hemisphere_sample();

	dir = dir.x*sr.u + dir.y*sr.v + dir.z*sr.w;  // Transform to world space.

    sample_point.x = dir.x;
    sample_point.y = dir.y;
    sample_point.z = dir.z;

    // The length of this return vector needs to be the distance to the light, hence * kHugeValue.
    return dir * kHugeValue;
}


RGBColor EnvLight::L(ShadeRec& s) {
    return intensity*color;
}


float EnvLight::pdf(const ShadeRec& sr) {
    return invPI * (sr.normal*sample_point);
}
