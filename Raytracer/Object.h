#ifndef H_Object
#define H_Object

enum shape { object, triangle, sphere };

// Standard library imports
#include <windows.h>
#include <glm/glm.hpp>

// Project file imports
#include "Material.h"
#include "Ray.h"

using namespace glm;

class Object {
// Public fields
public:
	// Constructors
	Object() {};
	Object(Material obj_mat, mat4 obj_transf);

	// Getter methods
	shape get_type();
	Material get_material();
	mat4 get_transf();

	// Virtual methods to be implemented by specific shape
	virtual bool intersects_ray(Ray & ray, float * t_hit, vec3 * normal) { return true; };

// Protected fields
protected:
	shape obj_type;
	Material obj_material;
	mat4 obj_transf;

};

#endif

