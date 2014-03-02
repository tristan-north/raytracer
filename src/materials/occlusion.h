#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "materials/abstractmaterial.h"

class Occlusion : public AbstractMaterial
{
public:
    Occlusion();

    void set_numSamples(int n);
	virtual RGBColor evaluate(ShadeRec& sr, uint rayDepth);

private:
    int numSamples;
};

#endif // OCCLUSION_H
