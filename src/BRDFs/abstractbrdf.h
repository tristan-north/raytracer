#ifndef ABSTRACTBRDF_H
#define ABSTRACTBRDF_H

#include <math.h>
#include "utilities/rgbcolor.h"
#include "utilities/vector3.h"
#include "utilities/shaderec.h"

class AbstractBRDF {
public:

    AbstractBRDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3& wo, const Vector3& wi) const;
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3& wo, Vector3& wi) const;
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3& wo, Vector3& wi, float& pdf) const;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3& wo) const;
};


#endif // ABSTRACTBRDF_H
