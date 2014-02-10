#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include "world/world.h"

using std::string;

class ObjLoader
{
public:
    ObjLoader();
    int load(World&  world, const string filepath, AbstractMaterial *material);  // Allocates a new MeshData object and adds triangles world.

private:
	// Takes a line from the .obj file and returns the numbers in that line as strings.
	vector<string> getNumbersAsStrings(const string& line);

};

#endif // OBJLOADER_H
