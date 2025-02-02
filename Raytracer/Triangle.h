#ifndef H_Triangle
#define H_Triangle

#include "Object.h"

// This is a tolerance value when testing intersections
constexpr float TOLERANCE = 0.0001f;

class Triangle : public Object
{
public:
	Triangle(Material mat, mat4 transf, vec3 vert_a, vec3 vert_b, vec3 vert_c);

	// Virtual method to implement
	virtual bool intersects_ray(Ray & ray, float * t_hit, vec3 * normal);
	virtual vec2 bounds(axis a);

	float area();										// Area of this triangle
	float area(vec3 vert_A, vec3 vert_B, vec3 vert_C);	// Area of specified triangle

	// Getter methods
	void getVertices(vec3 * a, vec3 * b, vec3 * c);

protected:
	vec3 vert_a;
	vec3 vert_b;
	vec3 vert_c;

	vec3 calc_centroid();
};

#endif
