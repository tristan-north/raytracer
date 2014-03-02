#include "constant.h"

Constant::Constant() : AbstractMaterial(), cd(1)
{}


RGBColor Constant::evaluate(ShadeRec &sr, uint rayDepth)
{
    return cd;
}
