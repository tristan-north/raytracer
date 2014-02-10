#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor
{
public:

	float	r, g, b;

	RGBColor(void);										// default constructor
	RGBColor(float c);									// constructor
	RGBColor(float _r, float _g, float _b);				// constructor
	RGBColor(const RGBColor& c); 						// copy constructor
	~RGBColor(void);									// destructor

	RGBColor& operator= (const RGBColor& rhs);			// assignment operator
	RGBColor operator+ (const RGBColor& c) const;		// addition
	RGBColor& operator+= (const RGBColor& c);			// compound addition
	RGBColor operator* (const float a) const; 			// multiplication by a float on the right
	RGBColor& operator*= (const float a);				// compound multiplication by a float on the right
	RGBColor operator/ (const float a) const;			// division by a float
	RGBColor& operator/= (const float a);				// compound division by a float
	RGBColor operator* (const RGBColor& c) const;		// component-wise multiplication
	bool operator== (const RGBColor& c) const;			// are two RGBColours the same?

	RGBColor powc(float p) const;						// raise components to a power
	float average(void) const;							// the average of the components
};



// inlined member functions

// addition of two colors
inline RGBColor RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}

// compound addition of two colors
inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
	r += c.r; g += c.g; b += c.b;
	return (*this);
}

// multiplication by a float on the right
inline RGBColor RGBColor::operator* (const float a) const {
	return (RGBColor (r * a, g * a, b * a));
}

// compound multiplication by a float on the right
inline RGBColor& RGBColor::operator*= (const float a) {
	r *= a; g *= a; b *= a;
	return (*this);
}

// division by float
inline RGBColor RGBColor::operator/ (const float a) const {
	return (RGBColor (r / a, g / a, b / a));
}

// compound division by float
inline RGBColor& RGBColor::operator/= (const float a) {
	r /= a; g /= a; b /= a;
	return (*this);
}

// component-wise multiplication of two colors
inline RGBColor RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor (r * c.r, g * c.g, b * c.b));
}

// are two RGBColors the same?
inline bool RGBColor::operator== (const RGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}

// the average of the three components
inline float RGBColor::average(void) const {
	return (0.333333333333 * (r + g + b));
}


// inlined non-member function

// multiplication by a float on the left
RGBColor operator* (const float a, const RGBColor& c);

inline RGBColor operator* (const float a, const RGBColor& c) {
	return (RGBColor (a * c.r, a * c.g, a * c.b));
}


#endif // RGBCOLOR_H
