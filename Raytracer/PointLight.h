#ifndef H_PointLight
#define H_PointLight

#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(Color col, vec3 posn, double attenuation);

	Color calculate_shading();
};

#endif