#ifndef POINT2_H
#define POINT2_H

class Point2
{
public:

	float	x, y;

	Point2 (void);										// default constructor
	Point2 (const float arg);							// constructor
	Point2 (const float x1, const float y1);			// constructor
	Point2 (const Point2& p); 						// copy constructor
	~Point2 (void) {}									// destructor

	Point2& operator= (const Point2& rhs);			// assignment operator
	Point2	operator* (const float a);					// multiplication on right by scalar

};


// scales the point by the float a
inline Point2 Point2::operator* (const float a) {
	return (Point2(a * x, a * y));
}


#endif // POINT2_H
