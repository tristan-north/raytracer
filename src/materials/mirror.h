#ifndef MIRROR_H
#define MIRROR_H

#include "materials/abstractmaterial.h"

class Mirror : public AbstractMaterial
{
public:
	Mirror();

	virtual RGBColor evaluate(ShadeRec& sr, uint rayDepth);

private:
};


#endif // MIRROR_H
