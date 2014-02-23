#ifndef GRID_H
#define GRID_H

#include "abstractaccel.h"
#include "utilities/bbox.h"
#include "utilities/point3.h"
#include "geometricObjects/triangle.h"
#include <vector>

class Cell;

class Grid : public AbstractAccel
{
public:
	Grid(World &w);
	~Grid();

	virtual ShadeRec closest_intersection(const Ray& ray);
	virtual bool shadow_intersection(const Ray& ray, double distToLight);

private:
	BBox bbox;
	Cell* cells;
	struct {float x; float y; float z;} cellSize;
	struct {uint x; uint y; uint z;} gridRes;

	Cell* get_cell(int x, int y, int z);
	bool intersect(ShadeRec& returnSr, const Ray& ray, const bool isShadowRay, const double maxT);
};


class Cell
{
public:
	void addPrimitive(AbstractGeo* primitive);
	bool intersectPrimitives(const Ray& ray, ShadeRec& returnSr, ShadeRec& testSr);
	std::vector<AbstractGeo*> primitives;
};

#endif // GRID_H
