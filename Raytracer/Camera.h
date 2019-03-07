#ifndef H_Camera
#define H_Camera

#include "Scene.h"

class Camera
{
private:
	vec3 w;
	vec3 up;
	vec3 v;
	double fovx, fovy;
public:
	Camera();
	~Camera();
	Ray generateRay(Sampler sample);
};

#endif