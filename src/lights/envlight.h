#ifndef ENVLIGHT_H
#define ENVLIGHT_H

#include "abstractlight.h"

class EnvLight : public AbstractLight
{
public:
    EnvLight();
    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
    virtual Vector3 get_direction(const ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);
    virtual float pdf(const ShadeRec &sr);

};

#endif // ENVLIGHT_H
