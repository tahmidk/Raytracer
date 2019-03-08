#ifndef H_Ray
#define H_Ray

// Standard library imports
#include <glm/glm.hpp>

// Project file imports
#include "Light.h"

using namespace glm;

class Ray
{
public:
	Ray() {};								// Default constructor
	Ray(vec3 posn, vec3 dirn);				// General ray constructor
	Ray(vec3 posn, Light light);			// Used to generate a ray towards a light source
	Ray(vec3 norm, vec3 posn, Ray ray_in);	// Used to generate reflected rays at a hit point
	Ray(vec3 posn, vec3 dirn, float t_min, float t_max);	// Restricted Ray constructor

	// Utility methods
	vec3 evaluate(float t);
	Ray transformRay(mat4 transf);

	// Getter methods
	vec3 get_posn();
	vec3 get_dirn();
	float get_tmin();
	float get_tmax();

private:
	vec3 posn;
	vec3 dirn;
	float t_min;
	float t_max;
};

#endif