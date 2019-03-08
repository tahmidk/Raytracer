#ifndef H_Sphere
#define H_Sphere

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(shape typ, Color A, Color D, Color S, Color E,
		float shininess, mat4 transf, float x, float y, float z, float r);

	// Virtual method to implement
	bool intersects_ray(Ray ray, float * t_hit, vec3 * normal);

	// Getter methods
	vec3 get_center();
	float get_radius();
	Color getAmbient();
protected:
	vec3 center;
	float radius;
};

#endif // !H_Sphere

