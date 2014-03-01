extern const uint g_hres = 720/2;
extern const uint g_vres = 576/2;

void World::build() {
	// Settings
	settings.pixelSamples = 3;
	settings.maxRayDepth = 2;
	settings.indirectSamples = 4;

	// Materials
	Matte* greyMaterial = new Matte;
	greyMaterial->set_kd(0.7);
	greyMaterial->set_cd(RGBColor(1, 1, 1));
	add_material(greyMaterial);

	Matte* redMaterial = new Matte;
	redMaterial->set_kd(0.7);
	redMaterial->set_cd(RGBColor(1, 0, 0));
	redMaterial->assignment = "wall_left";
	add_material(redMaterial);

	Matte* greenMaterial = new Matte;
	greenMaterial->set_kd(0.7);
	greenMaterial->set_cd(RGBColor(0, 1, 0));
	greenMaterial->assignment = "wall_right";
	add_material(greenMaterial);

	// Lights
	RectLight* light_ptr = new RectLight;
	light_ptr->set_intensity(7);
	light_ptr->set_color(1, 1, 1);
	light_ptr->set_num_samples(4);
	light_ptr->set_transform(0, 138, 80,  // translate
							 180, 0, 0,   // rotate
							 100, 100, 100); // scale
	add_light(light_ptr);

//	EnvLight* envlight_ptr = new EnvLight;
//	envlight_ptr->set_intensity(0.5);
//	envlight_ptr->set_num_samples(16);
//	add_light(envlight_ptr);

	// Camera
	camera.fov = 40;
//	camera.set_transform(-32.317, 9.23, -113.608,  // translate
//						 5.062, 187.8, 0); // rotate
	camera.set_transform(0, 100, -205,  // translate
						 -7.6, 180, 0); // rotate


	// Load geo
	if( !ObjLoader::load(*this, "testModel.obj") )
		return;

	accelStruct_ptr = new Grid(*this);
	tracer_ptr = new RayCast(*this);
}
