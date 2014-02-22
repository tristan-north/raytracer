#ifndef WORLD_H
#define WORLD_H

#include <vector>
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
	World();
	~World();

	AbstractAccel*				accelStruct_ptr;
	RGBColor					background_color;
    AbstractTracer*				tracer_ptr;
	Camera						camera;
	vector<AbstractGeo*>        primitives;
    vector<AbstractLight*> 		lights;
    vector<AbstractMaterial*>   materials;
    vector<MeshData*>           meshDatas;
	uint* 						screen_buffer;
	uint 						pixelSamples;

	void add_primitive(AbstractGeo* primitive_ptr);
	void add_light(AbstractLight* light_ptr);
    void add_material(AbstractMaterial* mat_ptr);
    void add_meshData(MeshData* meshData_ptr);
	void build();
	void render_scanline(int scanlineNum);
	void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

private:
	void delete_objects(void);
	void delete_lights(void);
    void delete_materials(void);
    void delete_meshDatas(void);
	float rand_float();
};


inline void World::add_primitive(AbstractGeo* primitive_ptr) {
	primitives.push_back(primitive_ptr);
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


#endif // WORLD_H
