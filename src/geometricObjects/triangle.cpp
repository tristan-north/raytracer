#include <algorithm> // For min() max()
#include "triangle.h"
#include "utilities/common.h"
#include "utilities/timer.h"

using namespace std;

Triangle::Triangle()
    : 	AbstractGeo(),
		mesh_ptr(0),
		vIndex0(0), vIndex1(0), vIndex2(0),
		nIndex0(0), nIndex1(0), nIndex2(0)
{}

Triangle::Triangle(MeshData* _mesh_ptr, const uint v0, const uint v1, const uint v2,
										const uint n0, const uint n1, const uint n2)
    : 	AbstractGeo(),
        mesh_ptr(_mesh_ptr),
		vIndex0(v0), vIndex1(v1), vIndex2(v2),
		nIndex0(n0), nIndex1(n1), nIndex2(n2)
{}


//void Triangle::compute_normal(const bool reverse_normal) {
//	normal = (mesh_ptr->vertices[vIndex1] - mesh_ptr->vertices[vIndex0]) ^
//			 (mesh_ptr->vertices[vIndex2] - mesh_ptr->vertices[vIndex0]);
//	normal.normalize();

//	if (reverse_normal)
//		normal = -normal;
//}


Normal Triangle::get_normal() const {
	return mesh_ptr->normals[nIndex0];
}


BBox Triangle::get_bbox() const {
	Point3 v1(mesh_ptr->vertices[vIndex0]);
	Point3 v2(mesh_ptr->vertices[vIndex1]);
	Point3 v3(mesh_ptr->vertices[vIndex2]);

    return(BBox(min(min(v1.x, v2.x), v3.x) - kEpsilon, max(max(v1.x, v2.x), v3.x) + kEpsilon,
                min(min(v1.y, v2.y), v3.y) - kEpsilon, max(max(v1.y, v2.y), v3.y) + kEpsilon,
                min(min(v1.z, v2.z), v3.z) - kEpsilon, max(max(v1.z, v2.z), v3.z) + kEpsilon));
}


bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	Point3 v0(mesh_ptr->vertices[vIndex0]);
	Point3 v1(mesh_ptr->vertices[vIndex1]);
	Point3 v2(mesh_ptr->vertices[vIndex2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom  = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

    if (beta < 0.0) {
		return (false);
    }

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

    if (gamma < 0.0) {
		return (false);
    }

    if (beta + gamma > 1.0) {
		return (false);
    }

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

    if (t < kEpsilon) {
		return (false);
    }

	tmin = t;
	sr.normal = get_normal();

	return (true);
}


bool Triangle::shadow_hit(const Ray& ray, double& tmin) const {
	Point3 v0(mesh_ptr->vertices[vIndex0]);
	Point3 v1(mesh_ptr->vertices[vIndex1]);
	Point3 v2(mesh_ptr->vertices[vIndex2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom  = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

    if (beta < 0.0) {
		return (false);
    }

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

    if (gamma < 0.0 ) {
		return (false);
    }

    if (beta + gamma > 1.0) {
		return (false);
    }

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

    if (t < kEpsilon) {
		return (false);
    }

	tmin = t;

	return (true);
}
