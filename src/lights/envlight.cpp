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
    float rnd1 = rand_float();
    float rnd2 = rand_float();

////  Uniform hemisphere distribution
//    float sin_theta = sqrt(1 - rnd1*rnd1);
//    float phi = 2 * PI * rnd2;

//    Vector3 dir;
//    dir.x = sin_theta * sin(phi);
//    dir.y = rnd1;
//    dir.z = sin_theta * cos(phi);

    // Cosine hemisphere distribution.
    // This accounts for lamberts law which would otherwise need to be applied.
    float r = sqrt(rnd1);
    float theta = 2 * PI * rnd2;

    Vector3 dir;
    dir.x = r * cos(theta);
    dir.y = sqrt(max(0.0f, 1-rnd1));
    dir.z = r * sin(theta);


    // u, v, w is used to transform the ray to world space
    // This doesn't need to be recomputed for every light sample, just once for each shading point.
    Vector3 v = sr.normal;
    Vector3 w = v ^ Vector3(0.0072, 1.0, 0.0034);     // Jitter up vector in case normal is vertical
    w.normalize();
    Vector3 u = w ^ v;

    dir = dir.x*u + dir.y*v + dir.z*w;

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
