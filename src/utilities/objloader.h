#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include "world/world.h"

class ObjLoader
{
public:
	int load(World& world, const std::string filepath);

private:
	// Takes a line from the .obj file and returns the numbers in that line as strings.
	static std::vector<std::string> getNumbersAsStrings(const std::string& line);

};

#endif // OBJLOADER_H
