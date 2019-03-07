/*==================================================================
	File:	[Sphere.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a sphere 
			in the raytracer program.
==================================================================*/

#include "pch.h"
#include "Sphere.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Sphere]
	Args:	All args of Object
			x - x-coordinate of Sphere's center
			y - y-coordinate of Sphere's center
			z - z-coordinate of Sphere's center
			r - the sphere's radius
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Sphere::Sphere(shape typ, Color A, Color D, Color S, Color E,
	float shininess, mat4 transf, float x, float y, float z, float r) :
	Object::Object(typ, A, D, S, E, shininess, transf)
{
	vec3 c(x, y, z);
	this->center = c;
	this->radius = r;
}

/*-------------------------------------------------------------------
	Func:	[intersects_ray]
	Args:	ray - the ray to calculate intersection for
	Desc:	Using the equation of a sphere given in lecture, this
			function determines whether the given Ray intersects this
			sphere surface and accordingly returns all intersection
			points
	Rtrn:	A (potentially empty) list of intersection points
-------------------------------------------------------------------*/
bool Sphere::intersects_ray(Ray ray) {
	return true;
}

/*--------------[ Getter methods ]--------------*/
vec3 Sphere::get_center()	{ return center; }
float Sphere::get_radius()	{ return radius; }
