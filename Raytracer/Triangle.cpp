/*==================================================================
	File:	[Triangle.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a triangular
			surface in the raytracer program.
==================================================================*/

#include "pch.h"
#include "Triangle.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Triangle]
	Args:	All args of Object
			vert_a - the first vertex of the triangle
			vert_b - the first vertex of the triangle
			vert_c - the first vertex of the triangle
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Triangle::Triangle(shape typ, Color A, Color D, Color S, Color E, 
	float shininess, mat4 transf, vec3 vert_a, vec3 vert_b, vec3 vert_c) :
	Object::Object(typ, A, D, S, E, shininess, transf)
{
	this->vert_a = vert_a;
	this->vert_b = vert_b;
	this->vert_c = vert_c;
}

/*-------------------------------------------------------------------
	Func:	[intersects_ray]
	Args:	ray - the ray to calculate intersection for
			t_hit - an output param to store the t of intersection
					or NULL if no intersection
			normal - an output param to store the surface normal at
					the intersection or NULL if no intersection
	Desc:	Using the equation of a sphere given in lecture, this
			function determines whether the given Ray intersects this
			triangle surface and accordingly returns the intersection
			information
	Rtrn:	True if ray intersects triangle
			False otherwise
-------------------------------------------------------------------*/
bool Triangle::intersects_ray(Ray ray, float * t_hit, vec3 * normal)
{
	t_hit = NULL;
	normal = NULL;

	// Given Ray :	P = P0 + P1*t
	// And Sphere:	(P - C) dot (P - C) - R^2 = 0
	// Solve: (P1 dot P1)t^2 + 2(P1 dot (P0 - C))t + (P0 - C) dot (P0 - C) - R^2

	// No intersection
	return false;
}

/*--------------[ Getter Methods ]--------------*/
void Triangle::getVertices(vec3 * a, vec3 * b, vec3 * c)
{
	a = &(this->vert_a);
	b = &(this->vert_b);
	c = &(this->vert_c);
}