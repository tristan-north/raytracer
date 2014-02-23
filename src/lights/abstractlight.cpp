#include "QDebug"
#include "lights/abstractlight.h"


AbstractLight::AbstractLight() :
    intensity(1.0),
	color(1.0),
	num_samples(1)
{}

RGBColor AbstractLight::L(ShadeRec& sr) {
	return (0);
}

void AbstractLight::set_intensity(const float b) {
    intensity = b;
}

void AbstractLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}

void AbstractLight::set_color(const RGBColor& c) {
	color = c;
}

void AbstractLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

void AbstractLight::set_transform(const float tx, const float ty, const float tz,
                          const float rx, const float ry, const float rz,
                          const float sx, const float sy, const float sz) {

    transform.translate(tx, ty, tz);
    transform.rotateByDeg(rx, ry, rz);
    transform.scale(sx, sy, sz);
}


void AbstractLight::set_num_samples(int n) {
	num_samples = n;
}

int AbstractLight::get_num_samples() {
	return num_samples;
}

float AbstractLight::pdf(const ShadeRec &sr) {
	return 1.0;
}

float AbstractLight::G(const ShadeRec &sr) {
	return 1.0;
}
