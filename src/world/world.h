#ifndef WORLD_H
#define WORLD_H

// The World class does not have a copy constructor or an assignment operator, for the followign reasons:
// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory.


#include <vector>
#include "world/viewplane.h"
#include "world/camera.h"
#include "utilities/rgbcolor.h"
#include "tracers/abstracttracer.h"
#include "geometricObjects/abstractgeo.h"
#include "lights/abstractlight.h"
#include "utilities/ray.h"
#include "utilities/meshdata.h"
#include "utilities/common.h"
#include "accelerators/abstractaccel.h"

using namespace std;

class Matte;

class World
{
public:
	AbstractAccel*				accelStruct_ptr;
	ViewPlane					vp;
	RGBColor					background_color;
    AbstractTracer*				tracer_ptr;
	Camera*						camera_ptr;
    vector<AbstractGeo*>        objects;
    vector<AbstractLight*> 		lights;
    vector<AbstractMaterial*>   materials;
    vector<MeshData*>           meshDatas;
	unsigned int* 				screen_buffer;

    World();
	~World();

	void add_object(AbstractGeo* object_ptr);
	void add_light(AbstractLight* light_ptr);
    void add_material(AbstractMaterial* mat_ptr);
    void add_meshData(MeshData* meshData_ptr);
	void set_camera(Camera* c_ptr);
	void build(int hres, int vres);
	void render_scanline(int scanlineNum);
	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

private:
	void delete_objects(void);
	void delete_lights(void);
    void delete_materials(void);
    void delete_meshDatas(void);
	float rand_float();
};


inline void World::add_object(AbstractGeo* object_ptr) {
	objects.push_back(object_ptr);
}

inline void World::add_light(AbstractLight* light_ptr) {
	lights.push_back(light_ptr);
}

inline void World::add_material(AbstractMaterial* mat_ptr) {
    materials.push_back(mat_ptr);
}

inline void World::add_meshData(MeshData* meshData_ptr) {
    meshDatas.push_back(meshData_ptr);
}

inline void World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}

#endif // WORLD_H
