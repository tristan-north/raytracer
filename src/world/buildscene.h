extern const uint g_hres = 720/4;
extern const uint g_vres = 576/4;

void World::build() {
	settings.pixelSamples = 2;
	settings.maxRayDepth = 1;
	settings.indirectSamples = 4;

//    Occlusion* material = new Occlusion;
//    material->set_numSamples(6);
    Matte* material = new Matte;
    material->set_kd(1.0);
    material->set_cd(RGBColor(1, 1, 1));
    add_material(material);


    ObjLoader objLoader;
    if( !objLoader.load(*this, "testModel.obj", material) )
        return;

	accelStruct_ptr = new Grid(*this);
	tracer_ptr = new RayCast(this);

	// camera
	camera.fov = 40;
	camera.set_transform(0, 100, -205,  // translate
						 -7.6, 180, 0);  // rotate

	// lights
	RectLight* light_ptr = new RectLight;
	light_ptr->set_intensity(15);
	light_ptr->set_color(1, 1, 1);
	light_ptr->set_num_samples(4);
	light_ptr->set_transform(0, 138, 80,   // translate
							  180, 0, 0,   // rotate
							  50, 50, 50); // scale
	add_light(light_ptr);

//	EnvLight* envlight_ptr = new EnvLight;
//	envlight_ptr->set_intensity(0.5);
//	envlight_ptr->set_num_samples(16);
//	add_light(envlight_ptr);
}
