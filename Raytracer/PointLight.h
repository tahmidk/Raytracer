#ifndef H_PointLight
#define H_PointLight

#include "Light.h"

class PointLight : public Light
{
public:
	// Constructors
	PointLight();
	PointLight(Color col, vec3 posn);

	// Utility virtual function
	Color calculate_shading(HitInfo * hit_info, vec3 eye, double * attenuation);
	vec3 get_towards_dirn(vec3 from);
};

#endif