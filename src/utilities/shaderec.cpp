// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "utilities/shaderec.h"


ShadeRec::ShadeRec(World& wr)
	: 	hit_an_object(false),
		material_ptr(0),
		hit_point(),
		normal(),
		ray(),
		t(0.0),
		world(wr)
{}

ShadeRec &ShadeRec::operator=(const ShadeRec &rhs)
{
	hit_an_object = rhs.hit_an_object;
	material_ptr = rhs.material_ptr;
	hit_point = rhs.hit_point;
	normal = rhs.normal;
	ray = rhs.ray;
	t = rhs.t;

	return (*this);
}
