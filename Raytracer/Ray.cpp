#include "pch.h"
#include "Ray.h"


Ray::Ray(Point posn, glm::vec3 dirn, float t_min, float t_max)
{
	this->posn = posn;
	this->dirn = dirn;
	this->t_min = t_min;
	this->t_max = t_max;
}
