#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include "world/world.h"

using std::string;

struct MaterialsList {
	vector<string> assignments;
	vector<AbstractMaterial*> materials;
};

class ObjLoader
{
public:
	int load(World& world, const string filepath, const MaterialsList& materialsList);

private:
	// Takes a line from the .obj file and returns the numbers in that line as strings.
	static vector<string> getNumbersAsStrings(const string& line);

};

#endif // OBJLOADER_H
