#ifndef H_Sphere
#define H_Sphere

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(Material mat, mat4 transf, float x, float y, float z, float r);

	// Virtual method to implement
	virtual bool intersects_ray(Ray & ray, float * t_hit, vec3 * normal);
	virtual vec2 bounds(axis a);

	// Getter methods
	vec3 get_center();
	float get_radius();

protected:
	vec3 center;
	float radius;

	vec3 calc_centroid();
};

#endif // !H_Sphere

