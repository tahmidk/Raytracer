/*==================================================================
	File:	[Material.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	A Material is a data structure belonging to an individual 
			Object of the Scene that contains information on the
			Object's material properties including diffuse color,
			emission color, specular color, and its shininess
==================================================================*/

#include "pch.h"
#include "Material.h"

/*-------------------------------------------------------------------
	Func:	Default Constructor: [Material]
	Args:	None
	Desc:	Constructor initializes all material properties to black
			and shininess to 0.0
	Rtrn:	None
-------------------------------------------------------------------*/
Material::Material() {
	this->diffuse = COLORS::black;
	this->emission = COLORS::black;
	this->specular = COLORS::black;
	this->shininess = 0.0;
}

/*-------------------------------------------------------------------
	Func:	Constructor: [Material]
	Args:	diffuse - the diffuse color
			emission - the emission color
			specular - the specular color
			shininess - the shininess ratio
	Desc:	Constructor initializes all fields properly
	Rtrn:	None
-------------------------------------------------------------------*/
Material::Material(Color diffuse, Color ambient, Color emission, Color specular, double shininess)
{
	this->diffuse = diffuse;
	this->ambient = ambient;
	this->emission = emission;
	this->specular = specular;
	this->shininess = shininess;
}

/*------------[ Getter Methods ]--------------*/
Color Material::get_diffuse()		{ return diffuse; }
Color Material::get_ambient()		{ return ambient; }
Color Material::get_emission()		{ return emission; }
Color Material::get_specular()		{ return specular; }
double Material::get_shininess()	{ return shininess; }
