#ifndef H_Object
#define H_Object

// Some enumerators for readability
enum shape { object, triangle, sphere };
enum axis { axis_x, axis_y, axis_z };

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
	vec3 get_centroid();
	vec2 get_bounds(axis a);

	// Virtual methods to be implemented by specific shape
	virtual bool intersects_ray(Ray & ray, float * t_hit, vec3 * normal) { return true; };
	virtual vec2 bounds(axis a) { return vec2(0.0f); }

// Protected fields
protected:
	shape obj_type;
	Material obj_material;
	mat4 obj_transf;
	vec3 centroid;

	// Bounded box parameters of this primitive
	vec2 x_bounds;
	vec2 y_bounds;
	vec2 z_bounds;

};

#endif

