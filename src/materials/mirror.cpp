#include "mirror.h"

Mirror::Mirror() : AbstractMaterial()
{
}

RGBColor Mirror::evaluate(ShadeRec &sr, uint rayDepth)
{
	RGBColor finalColor	= 0;
	World& world = sr.world;
	Vector3 wo = -sr.ray.d;

	Ray indirectRay;
	indirectRay.o = sr.hit_point;
	indirectRay.d = 2*sr.normal * (sr.normal*wo) - wo;  // Reflection ray direction.

	finalColor = world.tracer_ptr->trace_ray(indirectRay, rayDepth + 1);

	return finalColor;
}
