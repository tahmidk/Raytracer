#ifndef H_Triangle
#define H_Triangle

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle(shape typ, Color A, Color D, Color S, Color E,
		float shininess, mat4 transf, vec3 vert_a, vec3 vert_b, vec3 vert_c);

	// Virtual method to implement
	bool intersects_ray(Ray ray, float * t_hit, vec3 * normal);

	float area();										// Area of this triangle
	float area(vec3 vert_A, vec3 vert_B, vec3 vert_C);	// Area of specified triangle

	// Getter methods
	void getVertices(vec3 * a, vec3 * b, vec3 * c);
	Color getAmbient();
protected:
	vec3 vert_a;
	vec3 vert_b;
	vec3 vert_c;
};

#endif
