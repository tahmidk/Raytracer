/*==================================================================
	File:	[Object.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a generic 
			object in the raytracer program. 
==================================================================*/

#include "pch.h"
#include "Object.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Object]
	Args:	obj_type - the exact geometric shape of this object
			obj_material - the Object's material properties
			obj_transf - the Object's transformation matrix
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Object::Object(Material obj_material, mat4 obj_transf)
{
	this->obj_type = object;
	this->obj_material = obj_material;
	this->obj_transf = obj_transf;

	this->x_bounds = vec2(0.0f, 0.0f);
	this->y_bounds = vec2(0.0f, 0.0f);
	this->z_bounds = vec2(0.0f, 0.0f);
}

/*-------------[ Getter Methods ]-------------*/
shape Object::get_type()		{ return obj_type; }
Material Object::get_material() { return obj_material; }
mat4 Object::get_transf()		{ return obj_transf; }
vec3 Object::get_centroid()		{ return centroid; }
vec2 Object::get_bounds(axis a)
{
	vec2 ret;
	switch (a){
		case axis_x:
			ret = this->x_bounds;
			break;
		case axis_y:
			ret = this->y_bounds;
			break;
		case axis_z:
			ret = this->z_bounds;
			break;
		default:
			break;
	}
	return ret;
}
