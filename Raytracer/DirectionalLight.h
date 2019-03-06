#ifndef H_DirectionalLight
#define H_DirectionalLight

#include "Light.h"
class DirectionalLight :
	public Light
{

public:
	DirectionalLight();
	DirectionalLight(Color col, Point posn);

	Color calculate_shading();
};

#endif