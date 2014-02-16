int g_width = 720/4;
int g_height = 576/4;

void World::build(int hres, int vres) {

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

	// view plane
	vp.set_hres(hres);
	vp.set_vres(vres);
	vp.set_samples(4);  // This is total samples per pixel and should be a square number.
	vp.set_gamma(2.2);

	tracer_ptr = new RayCast(this);


	// camera
	Camera* cam_ptr = new Camera;
	cam_ptr->set_eye(0, 100, -450);
	cam_ptr->set_lookat(0, 70, 0);
	cam_ptr->set_view_distance(400);
	cam_ptr->compute_uvw();
	set_camera(cam_ptr);


	// lights
	RectLight* light_ptr = new RectLight;
	light_ptr->set_intensity(12);
	light_ptr->set_color(1, 1, 1);
	light_ptr->set_num_samples(4);
	light_ptr->set_transform(0, 138, 80,
							  180, 0, 0,
							  50, 50, 50);
	add_light(light_ptr);

	EnvLight* envlight_ptr = new EnvLight;
	envlight_ptr->set_intensity(0.5);
	envlight_ptr->set_num_samples(16);
	add_light(envlight_ptr);
}
