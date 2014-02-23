#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "BRDFs/abstractbrdf.h"

class Lambertian: public AbstractBRDF {
public:

	Lambertian();

	virtual RGBColor f(const ShadeRec& sr, const Vector3& wo, const Vector3& wi) const;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3& wo) const;
	void set_ka(const float ka);
	void set_kd(const float kd);
	void set_cd(const RGBColor& c);
	void set_cd(const float r, const float g, const float b);
	void set_cd(const float c);

private:

	float		kd;
	RGBColor 	cd;
};


inline void Lambertian::set_ka(const float k) {
	kd = k;
}


inline void Lambertian::set_kd(const float k) {
	kd = k;
}


inline void Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}


inline void Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}

inline void	Lambertian::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}

#endif // LAMBERTIAN_H
