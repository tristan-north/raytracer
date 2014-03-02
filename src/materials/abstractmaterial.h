#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

#include "world/world.h"			// required for the shade function in all derived classes
#include "utilities/rgbcolor.h"
#include "utilities/shaderec.h"
#include <string>

class AbstractMaterial
{
public:

	AbstractMaterial();
	virtual RGBColor evaluate(ShadeRec& sr, uint rayDepth);
	std::string assignment;
};

#endif // ABSTRACTMATERIAL_H
