#include "point2.h"

Point2::Point2(void)
	: x(0.0), y(0.0)
{}

Point2::Point2(const float arg)
	: x(arg), y(arg)
{}

Point2::Point2(const float x1, const float y1)
	: x(x1), y(y1)
{}

Point2::Point2(const Point2& p)
	: x(p.x), y(p.y)
{}

Point2& Point2::operator= (const Point2& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x;
	y = rhs.y;

	return (*this);
}
