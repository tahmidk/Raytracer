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
}

/*-------------[ Getter Methods ]-------------*/
shape Object::get_type()		{ return obj_type; }
Material Object::get_material() { return obj_material; }
mat4 Object::get_transf()		{ return obj_transf; }
