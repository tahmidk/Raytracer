#ifndef H_Object
#define H_Object

//#include "variables.h"
enum shape { triangle, sphere };

#include <windows.h>
#include <glm/glm.hpp>
#include "Color.h"

class Object {
	// Public fields
public:
	// Constructor
	Object(shape type, Color ambient, Color diffuse, Color specular,
		Color emission, float shininess, glm::mat4 transform);

	// Getter methods
	shape get_type();
	Color get_ambient();
	Color get_diffuse();
	Color get_specular();
	Color get_emission();
	float get_shininess();
	glm::mat4 get_transf();

	// Virtual methods to be implemented by specific shape
	virtual bool intersects_ray() { return false; };

	// Protected fields
protected:
	// Instance fields of an object include shape, position and material properties
	shape type;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emission;
	float shininess;
	glm::mat4 transform;

};

#endif

