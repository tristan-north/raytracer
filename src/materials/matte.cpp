#include "matte.h"

extern ulong g_numLightRays;

Matte::Matte () : AbstractMaterial()
{}

RGBColor Matte::shade(ShadeRec& sr) {
    Vector3 wo = -sr.ray.d;
    Vector3 wi;
    RGBColor finalColor	= 0;
    Ray shadowRay;
    shadowRay.o = sr.hit_point;
    AbstractLight* light;
    int numLights = sr.w.lights.size();

    // For each light
    for (int j = 0; j < numLights; j++) {
        light = sr.w.lights[j];
        int numSamples = light->get_num_samples();

        // For each light sample
        for (int s = 0; s < numSamples; s++) {
            wi = light->get_direction(sr); // The length of wi here is the distance from shading point to light sample.
            double distToLight = wi.length();
            wi.normalize();

			float ndotwi = sr.normal * wi;

			if (ndotwi > 0.0) {
                bool in_shadow;
                shadowRay.d = wi;
                // Intersection test for geo between shading point and light sample.
				in_shadow = sr.w.accelStruct_ptr->shadow_intersection(shadowRay, distToLight);
                __sync_add_and_fetch(&g_numLightRays, 1);

				if (!in_shadow) {
                    finalColor += diffuse_brdf.f(sr, wo, wi) * light->L(sr) * ndotwi * light->G(sr) / light->pdf(sr) / numSamples; ;
				}
			}
		}
	}

    return (finalColor);
}
