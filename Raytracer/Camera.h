#ifndef H_Camera
#define H_Camera

#include "Scene.h"

class Camera
{
// Private fields
private:
	vec3 w;
	vec3 up;
	vec3 v;
	// Fields of view
	double fovx, fovy;

// Public fields
public:
	Camera();
	~Camera();

	// Utility functions
	Ray generateRay(Sampler sample);
};

#endif