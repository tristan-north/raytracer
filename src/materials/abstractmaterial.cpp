#include "materials/abstractmaterial.h"


AbstractMaterial::AbstractMaterial(): assignment("") {}

RGBColor AbstractMaterial::evaluate(ShadeRec& sr, uint rayDepth) {
	return (0);
}
