#ifndef RECTLIGHT_H
#define RECTLIGHT_H

#include "lights/abstractlight.h"
#include "utilities/vector3.h"
#include "utilities/normal.h"
#include "utilities/rgbcolor.h"
#include "utilities/shaderec.h"
#include "world/world.h"
#include "materials/constant.h"


class RectLight: public AbstractLight
{
public:
    RectLight();
    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
    virtual Vector3 get_direction(const ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);
	void set_size(int w, int h);
    virtual float pdf(const ShadeRec &sr);
	virtual float G(const ShadeRec& sr);
    virtual void set_transform(const float tx, const float ty, const float tz,
                               const float rx, const float ry, const float rz,
                               const float sx, const float sy, const float sz);

    void set_intensity(const float b);
    void set_color(const float c);
    void set_color(const RGBColor& c);
    void set_color(const float r, const float g, const float b);


private:
    Vector3 wi;     // unit direction from hit point being shaded to sample point on light surface

    Point3  p0;     // A corner of the light
    Vector3 a;      // A vector of an edge
    Vector3 b;      // A vector of an edge
    Normal normal;

    mutable Constant material;

    void updateMaterial();

};

#endif // RECTLIGHT_H
