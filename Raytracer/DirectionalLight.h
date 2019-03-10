#ifndef H_DirectionalLight
#define H_DirectionalLight

#include "Light.h"

class DirectionalLight : public Light
{
public:
	// Constructors
	DirectionalLight();
	DirectionalLight(Color col, vec3 posn);

	// Utility virtual function
	Color calculate_shading(HitInfo * hit_info, vec3 eye, double * attenuation);
	vec3 get_towards_dirn(vec3 from);
};

#endif