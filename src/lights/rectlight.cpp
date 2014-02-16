#include <QDebug>
#include "rectlight.h"
#include "utilities/common.h"

RectLight::RectLight() : AbstractLight(),
                        p0(-0.5, 0, -0.5), a(1, 0, 0),  b(0, 0, 1),
                        normal(0, 1, 0)
{}


bool RectLight::hit(const Ray& ray, double& tmin, ShadeRec &sr) const {
    float t = (p0 - ray.o) * normal / (ray.d * normal);

    if( t <= kEpsilon )
        return false;

    Point3 p = ray.o + (t * ray.d);
    Vector3 d = p - p0;

    float ddota = d * a;
    if( ddota < 0.0 || ddota > a.len_squared())
        return false;

    float ddotb = d * b;
    if( ddotb < 0.0 || ddotb > b.len_squared())
        return false;

    tmin = t;
    sr.normal = normal;
	sr.hit_an_object = true;
    sr.material_ptr = &material;

    return true;
}


// as this function is virtual, it shouldn't be inlined
Vector3 RectLight::get_direction(const ShadeRec &sr) {
    sample_point.x = rand_float() - 0.5;
    sample_point.y = 0;
    sample_point.z = rand_float() - 0.5;

    sample_point = transform * sample_point;

	wi = (sample_point - sr.hit_point);		// Used in G()

    Vector3 ret = wi;
    wi.normalize();

    return ret;
}


float RectLight::pdf(const ShadeRec &sr) {
    Vector3 n = a^b;
    float len = n.length();
    float mInvArea = 1.f / len;

    return mInvArea;
}


float RectLight::G(const ShadeRec& sr) {
    float ndotd = -normal * wi;
    float d2 = sample_point.d_squared(sr.hit_point);

    return ndotd / d2;
}


RGBColor RectLight::L(ShadeRec& s) {
    float ndotd = -normal * wi;

	if( ndotd > 0.0 )
        return (intensity * color);
	else
        return 0;
}


void RectLight::set_transform(const float tx, const float ty, const float tz,
                             const float rx, const float ry, const float rz,
                             const float sx, const float sy, const float sz) {
    AbstractLight::set_transform(tx, ty, tz, rx, ry, rz, sx, sy, sz);

    normal = transform * normal;
    normal.normalize();

    p0 = transform * p0;
    a = transform * a;
    b = transform * b;
}


void RectLight::updateMaterial()
{
     material.set_cd(intensity * color);
}


void RectLight::set_intensity(const float b)
{
    AbstractLight::set_intensity(b);
    updateMaterial();
}


void RectLight::set_color(const float c)
{
    AbstractLight::set_color(c);
    updateMaterial();
}


void RectLight::set_color(const RGBColor &c)
{
    AbstractLight::set_color(c);
    updateMaterial();
}


void RectLight::set_color(const float r, const float g, const float b)
{
    AbstractLight::set_color(r, g, b);
    updateMaterial();
}

