#include <math.h>
#include "utilities/rgbcolor.h"

// default constructor
RGBColor::RGBColor(void) : r(0.0), g(0.0), b(0.0) {}

// constructor
RGBColor::RGBColor(float c) : r(c), g(c), b(c) {}

// constructor
RGBColor::RGBColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

// copy constructor
RGBColor::RGBColor(const RGBColor& c) : r(c.r), g(c.g), b(c.b) {}

// destructor
RGBColor::~RGBColor(void) {}


// assignment operator
RGBColor& RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}

// raise each component to the specified power
// used for color filtering.
RGBColor RGBColor::powc(float p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}
