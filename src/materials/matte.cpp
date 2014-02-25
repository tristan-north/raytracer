#include "matte.h"

extern ulong g_numLightRays;

Matte::Matte () : AbstractMaterial()
{}

RGBColor Matte::shade(ShadeRec& sr, uint rayDepth) {
    Vector3 wo = -sr.ray.d;
    Vector3 wi;
    RGBColor finalColor	= 0;
    Ray shadowRay;
    shadowRay.o = sr.hit_point;
    AbstractLight* light;
	int numLights = sr.world.lights.size();
	uint numSamples;

	// Get illumination from each light.
    for (int j = 0; j < numLights; j++) {
		light = sr.world.lights[j];
		numSamples = light->get_num_samples();

        // For each light sample
		for (uint s = 0; s < numSamples; s++) {
            wi = light->get_direction(sr); // The length of wi here is the distance from shading point to light sample.
            double distToLight = wi.length();
            wi.normalize();

			float ndotwi = sr.normal * wi;

			if (ndotwi > 0.0) {
                bool in_shadow;
                shadowRay.d = wi;
                // Intersection test for geo between shading point and light sample.
				in_shadow = sr.world.accelStruct_ptr->shadow_intersection(shadowRay, distToLight);
                __sync_add_and_fetch(&g_numLightRays, 1);

				if (!in_shadow) {
					finalColor += diffuse_brdf.f(sr, wo, wi) * light->L(sr) * ndotwi * light->G(sr) / light->pdf(sr) / numSamples;
				}
			}
		}
	}

	// Get indirect illumination.
	Ray indirectRay;
	RGBColor indirectColor;
	indirectRay.o = sr.hit_point;

	// If shading the primary hit use indirectSamples number of samples. Otherwise
	// keep number of samples at 1 so that the number of indirect rays doesn't multiply
	// for each bounce.
	if( rayDepth < 1 )
		numSamples = sr.world.settings.indirectSamples*sr.world.settings.indirectSamples;
	else
		numSamples = 1;

	for( uint i = 0; i < numSamples; i++ ) {
		indirectRay.d = get_cosine_hemisphere_sample();
		// Transform ray dir to world space (based on hit point normal).
		indirectRay.d = indirectRay.d.x * sr.u +
						indirectRay.d.y * sr.v +
						indirectRay.d.z * sr.w;

		float ndotwi = sr.normal * indirectRay.d;

		if (ndotwi > 0.0) {
			indirectColor = sr.world.tracer_ptr->trace_ray(indirectRay, rayDepth + 1);
			finalColor += indirectColor * diffuse_brdf.f(sr, wo, indirectRay.d) * ndotwi / (invPI * (sr.normal*indirectRay.d)) / numSamples;
		}
	}

	return finalColor;
}
