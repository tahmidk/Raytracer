#ifndef H_Camera
#define H_Camera

// Standard library imports
#include <glm/glm.hpp>

// Project file imports
#include "Sample.h"
#include "Ray.h"

using namespace glm;

class Camera
{
// Private fields
private:
	vec3 w;
	vec3 u;
	vec3 v;
	// Fields of view
	double fovx, fovy;

// Public fields
public:
	Camera(vec3 eye, vec3 center, vec3 up, double fovy, double width, double height);

	// Utility functions
	Ray generateRay(Sample sample, vec3 eye, int w, int h);

};

#endif