#include "pch.h"
#include "Ray.h"


Ray::Ray(Point posn, glm::vec3 dirn, float t_min, float t_max)
{
	this->posn = posn;
}
