#include "lambertian.h"
#include "utilities/common.h"

Lambertian::Lambertian()
    :   AbstractBRDF(),
		kd(1.0),
		cd(0.5)
{}


RGBColor Lambertian::f(const ShadeRec& sr, const Vector3& wo, const Vector3& wi) const {
	return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3& wo) const {
	return (kd * cd);
}
