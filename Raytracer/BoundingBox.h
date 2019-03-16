#ifndef H_BoundingBox
#define H_BoundingBox

// Standard library imports
#include <list>

// Project import files
#include "Object.h"

using namespace glm;
using namespace std;

class BoundingBox
{
private:
	// Bounding Box definition fields
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	float z_min;
	float z_max;
	vec3 centroid;

	// List of objects this box contains
	list<Object*> objects;

public:
	// Constructors
	BoundingBox();
	BoundingBox(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
	BoundingBox(Object * obj);
	
	// Utility methods
	bool intersect_box(Ray & ray, float * t_hit);
	bool containsPoint(vec3 & point);
	BoundingBox operator+(const BoundingBox&);
	void addObject(Object * obj);

	// Getter methods
	float get_xmin();
	float get_xmax();
	float get_ymin();
	float get_ymax();
	float get_zmin();
	float get_zmax();
	vec3 get_centroid();
	int num_objects();
	list<Object*> get_objects();
};

#endif
