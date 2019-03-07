#ifndef H_Ray
#define H_Ray

#include <glm/glm.hpp>

using namespace glm;

class Ray
{
public:
	Ray() {};
	Ray(vec3 posn, vec3 dirn, float t_min, float t_max);

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