#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include "world/world.h"
#include "utilities/point3.h"

class ObjLoader
{
public:
	static int load(World& world, const std::string filepath);

private:
	// Takes a line from the .obj file and returns the numbers in that line as strings.
	static std::vector<std::string> getNumbersAsStrings(const std::string& line);
	static void computeNormal(const Point3& v0, const Point3& v1, const Point3& v2, Normal& normal);
	static uint getNormalIndexFromString(const std::string& str);

};

#endif // OBJLOADER_H
