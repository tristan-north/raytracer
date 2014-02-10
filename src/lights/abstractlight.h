#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H

#include "utilities/vector3.h"
#include "utilities/normal.h"
#include "utilities/rgbcolor.h"
#include "utilities/ray.h"
#include "utilities/matrix.h"
#include "geometricObjects/abstractgeo.h"

class ShadeRec;

class AbstractLight
{
public:

    AbstractLight(void);

    void set_intensity(const float b);
	void set_color(const float c);
	void set_color(const RGBColor& c);
	void set_color(const float r, const float g, const float b);
    virtual void set_transform(const float tx, const float ty, const float tz,
                               const float rx, const float ry, const float rz,
                               const float sx, const float sy, const float sz);
	void set_num_samples(int n);
	int get_num_samples();

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
    virtual float pdf(const ShadeRec &sr);
    virtual float G(const ShadeRec& sr);
    // The return vector of get_direction has the length of the distance from shading point to light sample.
    virtual Vector3 get_direction(const ShadeRec& sr) = 0;
	virtual RGBColor L(ShadeRec& sr);

protected:
    float		intensity;
	RGBColor	color;
	Point3		sample_point;	// This stored the point currently being sampled, it gets set by get_direction().
    int         num_samples;
    Matrix      transform;

};

#endif // ABSTRACTLIGHT_H
