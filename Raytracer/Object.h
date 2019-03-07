#ifndef H_Object
#define H_Object

//#include "variables.h"
enum shape { triangle, sphere };

#include <windows.h>
#include <glm/glm.hpp>
#include "Color.h"
#include "Ray.h"

using namespace glm;

class Object {
	// Public fields
public:
	// Constructors
	Object() {};
	Object(shape type, Color ambient, Color diffuse, Color specular,
		Color emission, float shininess, mat4 transform);

	// Getter methods
	shape get_type();
	Color get_ambient();
	Color get_diffuse();
	Color get_specular();
	Color get_emission();
	float get_shininess();
	mat4 get_transf();

	// Virtual methods to be implemented by specific shape
	virtual bool intersects_ray(Ray ray, float * t_hit, vec3 * normal) {};

	// Protected fields
protected:
	// Instance fields of an object include shape, position and material properties
	shape type;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emission;
	float shininess;
	mat4 transform;

};

#endif

