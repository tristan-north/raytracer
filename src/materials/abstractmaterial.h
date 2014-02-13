#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

#include "world/world.h"			// required for the shade function in all derived classes
#include "utilities/rgbcolor.h"
#include "utilities/shaderec.h"

class AbstractMaterial
{
public:

    AbstractMaterial(void);
	virtual RGBColor shade(ShadeRec& sr);
};

#endif // ABSTRACTMATERIAL_H