/*==================================================================
	File:	[BoundingBox.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	A bounding box is the tightest rectangular prism capable
			of entirely containing one or a set of Objects (aka 
			primitives)
==================================================================*/

#include "pch.h"
#include "BoundingBox.h"

#include <algorithm>

/*-------------------------------------------------------------------
	Func:	Default Constructor: [BoundingBox]
	Args:	None
	Desc:	Creates a trivial bounding box
	Rtrn:	None
-------------------------------------------------------------------*/
BoundingBox::BoundingBox() {
	this->x_min = 0.0f;
	this->x_max = 0.0f;
	this->y_min = 0.0f;
	this->y_max = 0.0f;
	this->z_min = 0.0f;
	this->z_max = 0.0f;
	this->centroid = vec3(0.0f);
}

/*-------------------------------------------------------------------
	Func:	General Constructor: [BoundingBox]
	Args:	x_min - the minimum x value
			x_max - the maximum x value
			y_min - the minimum y value
			y_max - the maximum y value
			z_min - the minimum z value
			z_max - the maximum z value
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
BoundingBox::BoundingBox(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	this->z_min = z_min;
	this->z_max = z_max;

	this->centroid = vec3();
	this->centroid.x = (x_min + x_max) / 2.0f;
	this->centroid.y = (y_min + y_max) / 2.0f;
	this->centroid.z = (z_min + z_max) / 2.0f;
}

/*-------------------------------------------------------------------
	Func:	Special Constructor: [BoundingBox]
	Args:	object - a pointer to the object primitive to bound
	Desc:	Constructor that specifically creates a bounding box for
			the given object
	Rtrn:	None
-------------------------------------------------------------------*/
BoundingBox::BoundingBox(Object * obj)
{
	// Find bounds for the 3 axes
	vec2 x_bounds = obj->get_bounds(axis_x);
	vec2 y_bounds = obj->get_bounds(axis_y);
	vec2 z_bounds = obj->get_bounds(axis_z);

	// Accordingly define the bounding box
	this->x_min = x_bounds[0];
	this->x_max = x_bounds[1];
	this->y_min = y_bounds[0];
	this->y_max = y_bounds[1];
	this->z_min = z_bounds[0];
	this->z_max = z_bounds[1];

	this->centroid = vec3();
	this->centroid.x = (x_min + x_max) / 2.0f;
	this->centroid.y = (y_min + y_max) / 2.0f;
	this->centroid.z = (z_min + z_max) / 2.0f;

	// Finally add this object to the bounding box
	this->objects.push_back(obj);
}

/*---------------------[ Utility methods]-------------------*/
/*-------------------------------------------------------------------
	Func:	[intersect]
	Args:	ray - the incoming ray
			t_hit - the t at which ray intersects this bounding box
	Desc:	Determines whether or not the given ray intersects this
			bounding box
	Rtrn:	True if it intersects
			False otherwise
-------------------------------------------------------------------*/
bool BoundingBox::intersect_box(Ray & ray, float * t_hit) {
	// Trivial case: if ray's origin is inside, the ray is inside
	if (containsPoint(ray.get_posn())) {
		*t_hit = 0.0f;
		return true;
	}

	// Find the faces that would get hit first given the ray's dirn
	// If ray is going in -x dirn, it would hit the +x face first if
	// it actually intersects this box
	float hit_x = (ray.get_dirn().x > 0) ? x_min : x_max;
	float hit_y = (ray.get_dirn().y > 0) ? y_min : y_max;
	float hit_z = (ray.get_dirn().z > 0) ? z_min : z_max;

	float t_hit_x = (hit_x - ray.get_posn().x) / ray.get_dirn().x;
	float t_hit_y = (hit_y - ray.get_posn().y) / ray.get_dirn().y;
	float t_hit_z = (hit_z - ray.get_posn().z) / ray.get_dirn().z;

	// The plane with the highest t of collision is the plane hit first
	float t_max = std::max(std::max(t_hit_x, t_hit_y), t_hit_z);
	if (t_max > ray.get_tmin() && t_max < ray.get_tmax()) {
		vec3 P_hit = ray.evaluate(t_max);
		if (containsPoint(P_hit)) {
			*t_hit = t_max;
			return true;
		}
	}

	// No intersection
	*t_hit = numeric_limits<float>().infinity();
	return false;
}

/*-------------------------------------------------------------------
	Func:	[containsPoint]
	Args:	point - the point to test
	Desc:	Determines whether or not the given point lies within this
			bounded box
	Rtrn:	True if it does
			False otherwise
-------------------------------------------------------------------*/
bool BoundingBox::containsPoint(vec3 & point)
{
	if (point.x < (this->x_min - MOE) || point.x > (this->x_max + MOE))
		return false;
	if (point.y < (this->y_min - MOE) || point.y > (this->y_max + MOE))
		return false;
	if (point.z < (this->z_min - MOE) || point.z > (this->z_max + MOE))
		return false;

	return true;
}

/*-------------------------------------------------------------------
	Func:	[operator+]
	Args:	other - the other BoundingBox
	Desc:	Acts as a union operator that creates a tight-fitting 
			bounding box encompassing both [this] and [other]
	Rtrn:	The union of this and other

	NOTE: Make sure not to union the same bounding box with itself
-------------------------------------------------------------------*/
BoundingBox BoundingBox::operator+(const BoundingBox & other)
{
	// Get the new bounds of this bounding box
	float x_min = (this->x_min < other.x_min) ? this->x_min : other.x_min;
	float x_max = (this->x_max > other.x_max) ? this->x_max : other.x_max;
	float y_min = (this->y_min < other.y_min) ? this->y_min : other.y_min;
	float y_max = (this->y_max > other.y_max) ? this->y_max : other.y_max;
	float z_min = (this->z_min < other.z_min) ? this->z_min : other.z_min;
	float z_max = (this->z_max > other.z_max) ? this->z_max : other.z_max;
	BoundingBox bb_union(x_min, x_max, y_min, y_max, z_min, z_max);

	// Add all objects from both BB to new unioned BB
	for (Object * obj : this->objects)
		bb_union.addObject(obj);
	for (Object * obj : other.objects)
		bb_union.addObject(obj);

	return bb_union;
}

/*-------------------------------------------------------------------
	Func:	[addObject]
	Args:	obj - the object pointer to include in this bounding box
	Desc:	Simply adds the given object to this bounding box's list
			of primitives
	Rtrn:	None
-------------------------------------------------------------------*/
void BoundingBox::addObject(Object * obj)
{
	this->objects.push_back(obj);
}

/*----------------------[ Getter methods ]-------------------*/
float BoundingBox::get_xmin() { return x_min; }
float BoundingBox::get_xmax() { return x_max; }
float BoundingBox::get_ymin() { return y_min; }
float BoundingBox::get_ymax() { return y_max; }
float BoundingBox::get_zmin() { return z_min; }
float BoundingBox::get_zmax() { return z_max; }
vec3 BoundingBox::get_centroid() { return centroid; }
int BoundingBox::num_objects() { return objects.size(); }
list<Object*> BoundingBox::get_objects() { return objects; }