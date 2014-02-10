#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "materials/abstractmaterial.h"

class Occlusion : public AbstractMaterial
{
public:
    Occlusion();

    void set_numSamples(int n);
    virtual RGBColor shade(ShadeRec& sr);

private:
    int numSamples;
};

#endif // OCCLUSION_H
