#include <algorithm>
#include "bbox.h"
#include "utilities/common.h"

using namespace std;

BBox::BBox ()
	: xMin(kHugeValue), xMax(-kHugeValue), yMin(kHugeValue), yMax(-kHugeValue), zMin(kHugeValue), zMax(-kHugeValue) {}

BBox::BBox (	const double _x0, const double _x1,
				const double _y0, const double _y1,
				const double _z0, const double _z1)
	: xMin(_x0), xMax(_x1), yMin(_y0), yMax(_y1), zMin(_z0), zMax(_z1) {}

BBox::BBox (const Point3 pMin, const Point3 pMax)
	: xMin(pMin.x), xMax(pMax.x), yMin(pMin.y), yMax(pMax.y), zMin(pMin.z), zMax(pMax.z) {}


bool BBox::hit(const Ray& ray, double &tmin) const {
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	// Find the t value where the ray intersects the 6 planes.
	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (xMin - ox) * a;
		tx_max = (xMax - ox) * a;
	}
	else {
		tx_min = (xMax - ox) * a;
		tx_max = (xMin - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (yMin - oy) * b;
		ty_max = (yMax - oy) * b;
	}
	else {
		ty_min = (yMax - oy) * b;
		ty_max = (yMin - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (zMin - oz) * c;
		tz_max = (zMax - oz) * c;
	}
	else {
		tz_min = (zMax - oz) * c;
		tz_max = (zMin - oz) * c;
	}

	double t0, t1;

	// The largest entering t value is one which
	// lies on the box. Find largest entering t value.
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	// find smallest exiting t value
	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	tmin = t0;
	if( tmin < 0 )
		tmin = t1;

	return (t0 < t1 && t1 > kEpsilon);
}


bool BBox::inside(const Point3& p) const {
	return ((p.x > xMin && p.x < xMax) && (p.y > yMin && p.y < yMax) && (p.z > zMin && p.z < zMax));
}


void BBox::expandToFit(const BBox &inBBox)
{
	xMin = min(xMin, inBBox.xMin);
	yMin = min(yMin, inBBox.yMin);
	zMin = min(zMin, inBBox.zMin);

	xMax = max(xMax, inBBox.xMax);
	yMax = max(yMax, inBBox.yMax);
	zMax = max(zMax, inBBox.zMax);
}
