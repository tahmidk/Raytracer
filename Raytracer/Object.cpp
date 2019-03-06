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
Object::Object(shape type, float size, float ambient[4], float diffuse[4], 
	float specular[4], float emission[4], float shininess, glm::mat4 transform)
{
	// Set object properties
	this->type = type;
	this->size = size;
	this->shininess = shininess;

	// Initialize lighting and coloring properties
	for (int i = 0; i < 4; i++) {
		(this->ambient)[i] = ambient[i];
		(this->diffuse)[i] = diffuse[i];
		(this->specular)[i] = specular[i];
		(this->emission)[i] = emission[i];
	}

	// Set transformation properties
	this->transform = transform;
}

/*-------------[ Getter Methods ]-------------*/
shape Object::get_type()			{ return type; }
float Object::get_size()			{ return size; }
float * Object::get_ambient()		{ return ambient; }
float * Object::get_diffuse()		{ return diffuse; }
float * Object::get_specular()	{ return specular; }
float * Object::get_emission()	{ return emission; }
float Object::get_shininess()		{ return shininess; }
glm::mat4 Object::get_transf()		{ return transform; }
