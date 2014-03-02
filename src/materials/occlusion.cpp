#include "occlusion.h"
#include "utilities/common.h"
#include <cmath>
#include <QDebug>

using namespace std;

Occlusion::Occlusion() : AbstractMaterial(), numSamples(4)
{}

void Occlusion::set_numSamples(int n)
{
    numSamples = n;
}


RGBColor Occlusion::evaluate(ShadeRec &sr, uint rayDepth)
{
    float totalContribution = 0;
    Ray shadowRay;
    shadowRay.o = sr.hit_point;

    // u, v, w is used to transform the ray to world space
    Vector3 v = sr.normal;
    Vector3 w = v ^ Vector3(0.0072, 1.0, 0.0034);     // Jitter up vector in case normal is vertical
    w.normalize();
    Vector3 u = w ^ v;

    float sampleSegmentSize = 1.0f/numSamples;
    for( int i = 0; i < numSamples; i++ ) {
        for( int j = 0; j < numSamples; j++ ) {
            bool hit = false;

            // Stratified samples
            float rnd1 = rand_float()*sampleSegmentSize + j*sampleSegmentSize;
            float rnd2 = rand_float()*sampleSegmentSize + i*sampleSegmentSize;

            // Uniform hemisphere distribution
            //        float sin_theta = sqrt(1 - rnd1*rnd1);
            //        float phi = 2 * PI * rnd2;

            //        shadowRay.d.x = sin_theta * sin(phi);
            //        shadowRay.d.y = rnd1;
            //        shadowRay.d.z = sin_theta * cos(phi);

            // Cosine hemisphere distribution.
            // This accounts for lamberts law which would otherwise need to be applied.
            float r = sqrt(rnd1);
            float theta = 2 * PI * rnd2;

            shadowRay.d.x = r * cos(theta);
            shadowRay.d.y = sqrt(max(0.0f, 1-rnd1));
            shadowRay.d.z = r * sin(theta);


            // Transform ray to world space
            shadowRay.d = u*shadowRay.d.x + v*shadowRay.d.y + w*shadowRay.d.z;

			hit = sr.world.accelStruct_ptr->shadow_intersection(shadowRay, kHugeValue);

            if(!hit) {
                totalContribution += 1;
            }
        }
    }

    return RGBColor(totalContribution/(numSamples*numSamples));
}
