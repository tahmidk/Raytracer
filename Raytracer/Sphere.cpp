/*==================================================================
	File:	[Sphere.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a sphere 
			in the raytracer program.
==================================================================*/

#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(shape typ, float sz, float A[4], float D[4], float S[4], float E[4],
	float shininess, glm::mat4 transf, float x, float y, float z, float r) :
	Object(typ, sz, A, D, S, E, shininess, transf)
{
	this->center = Point(x, y, z);
	this->radius = r;
}

/*--------------[ Getter methods ]--------------*/
Point Sphere::get_center()	{ return center; }
float Sphere::get_radius()	{ return radius; }
