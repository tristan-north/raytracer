#include "constant.h"

Constant::Constant() : AbstractMaterial(), cd(1)
{}


RGBColor Constant::shade(ShadeRec &sr, uint rayDepth)
{
    return cd;
}
