#include "world/viewplane.h"

// default constructor
ViewPlane::ViewPlane(void)
	: 	hres(400),
		vres(400),
		num_samples(1),
		gamma(1.0),
		inv_gamma(1.0)
{}


// copy constructor
ViewPlane::ViewPlane(const ViewPlane& vp)
	:  	hres(vp.hres),
		vres(vp.vres),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma)
{}

ViewPlane::~ViewPlane(void) {}

// assignment operator
ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);

	hres 				= rhs.hres;
	vres 				= rhs.vres;
	num_samples			= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;

	return (*this);
}
