#include "abstractbrdf.h"


AbstractBRDF::AbstractBRDF() {}

RGBColor AbstractBRDF::f(const ShadeRec& sr, const Vector3& wo, const Vector3& wi) const {
	return (0);
}


RGBColor AbstractBRDF::sample_f(const ShadeRec& sr, const Vector3& wo, Vector3& wi) const {
	return (0);
}


RGBColor AbstractBRDF::sample_f(const ShadeRec& sr, const Vector3& wo, Vector3& wi, float& pdf) const {
	return (0);
}


RGBColor AbstractBRDF::rho(const ShadeRec& sr, const Vector3& wo) const {
	return (0);
}
