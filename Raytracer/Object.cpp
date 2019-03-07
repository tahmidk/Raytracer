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
	Args:	type - the class of shape of this object
			size - the size of this object
			ambient - the ambient light setting for this object
			diffuse - the diffuse light setting for this object
			specular - the specular light setting for this object
			emission - the emission light setting for this object
			shininess - the shininess of this object
			transform - the transformations applied to this object
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Object::Object(shape type, Color ambient, Color diffuse, Color specular,
	Color emission, float shininess, mat4 transform)
{
	// Set object properties
	this->type = type;
	this->shininess = shininess;

	// Initialize lighting and coloring properties
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emission = emission;

	// Set transformation properties
	this->transform = transform;
}

/*-------------[ Getter Methods ]-------------*/
shape Object::get_type()		{ return type; }
Color Object::get_ambient()		{ return ambient; }
Color Object::get_diffuse()		{ return diffuse; }
Color Object::get_specular()	{ return specular; }
Color Object::get_emission()	{ return emission; }
float Object::get_shininess()	{ return shininess; }
mat4 Object::get_transf()		{ return transform; }
