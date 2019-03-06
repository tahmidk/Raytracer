#ifndef H_Ray
#define H_Ray

#include <glm/glm.hpp>
#include "Point.h"

class Ray
{
public:
	Ray() {};
	Ray(Point posn, glm::vec3 dirn, float t_min, float t_max);

protected:
	Point posn;
	glm::vec3 dirn;
	float t_min;
	float t_max;
};

#endif