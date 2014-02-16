#ifndef SHADEREC_H
#define SHADEREC_H

// We need the following as #includes instead of forward class declarations,
// because we have the objects themselves, not pointers or references

#include "utilities/point3.h"
#include "utilities/normal.h"
#include "utilities/rgbcolor.h"
#include "utilities/ray.h"

class World;	// only need a forward class declaration as the World data member is a reference
class AbstractMaterial;

class ShadeRec
{
public:
	ShadeRec(World& wr);				// constructor

	bool				hit_an_object;		// did the ray hit an object?
	AbstractMaterial* 	material_ptr;		// Pointer to the nearest object's material
	Point3				hit_point;			// World coordinates of intersection
	Normal				normal;				// normal at hit point
	Ray					ray;				// Required for specular highlights and area lights
	int					rayDepth;			// recursion depth
	float				t;					// ray parameter
	World&				w;					// world reference for shading

	ShadeRec& operator= (const ShadeRec& rhs);			// assignment operator

};

#endif // SHADEREC_H
