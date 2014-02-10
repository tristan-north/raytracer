#ifndef MATTE_H
#define MATTE_H

#include "materials/abstractmaterial.h"
#include "BRDFs/lambertian.h"

class Matte : public AbstractMaterial
{
public:
    Matte();

	void set_kd(const float k);
	void set_cd(const RGBColor c);
	void set_cd(const float r, const float g, const float b);

	virtual RGBColor shade(ShadeRec& sr);

private:
    Lambertian diffuse_brdf;
};


inline void	Matte::set_kd (const float kd) {
    diffuse_brdf.set_kd(kd);
}

inline void	Matte::set_cd(const RGBColor c) {
    diffuse_brdf.set_cd(c);
}

inline void	Matte::set_cd(const float r, const float g, const float b) {
    diffuse_brdf.set_cd(r, g, b);
}


#endif // MATTE_H
