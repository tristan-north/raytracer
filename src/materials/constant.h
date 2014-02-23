#ifndef CONSTANT_H
#define CONSTANT_H

#include "materials/abstractmaterial.h"

class Constant : public AbstractMaterial
{
public:
    Constant();

    void set_cd(const RGBColor c);
    void set_cd(const float r, const float g, const float b);

	virtual RGBColor shade(ShadeRec& sr, uint rayDepth);

private:
    RGBColor cd;
};

inline void	Constant::set_cd(const RGBColor c) {
    cd = c;
}

inline void	Constant::set_cd(const float r, const float g, const float b) {
    cd.r = r;
    cd.g = g;
    cd.b = b;
}


#endif // CONSTANT_H
