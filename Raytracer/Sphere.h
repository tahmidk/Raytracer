#ifndef H_Sphere
#define H_Sphere

#include "Object.h"
#include "Point.h"

class Sphere : public Object
{
public:
	Sphere(shape typ, Color A, Color D, Color S, Color E,
		float shininess, glm::mat4 transf, float x, float y, float z, float r);
	bool intersects_ray();

	// Getter methods
	Point get_center();
	float get_radius();

protected:
	Point center;
	float radius;
};

#endif // !H_Sphere

