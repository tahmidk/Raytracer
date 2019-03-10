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
Sphere::Sphere(Material mat, mat4 transf, float x, float y, float z, float r) :
	Object::Object(mat, transf)
{
	this->obj_type = sphere;
	this->center = vec3(x, y, z);
	this->radius = r;
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
			sphere surface and accordingly returns the intersection
			information
	Rtrn:	True if ray intersects triangle
			False otherwise
-------------------------------------------------------------------*/
bool Sphere::intersects_ray(Ray & ray, float * t_hit, vec3 * normal) {
	// Given Ray :	P = P0 + P1*t
	// And Sphere:	(P - C) dot (P - C) - R^2 = 0
	// Solve: (P1 dot P1)t^2 + 2(P1 dot (P0 - C))t + (P0 - C) dot (P0 - C) - R^2
	vec3 P0 = ray.get_posn();
	vec3 P1 = ray.get_dirn();

	// Initialize a, b, and c of quadratic equation
	float a = dot(P1, P1);
	float b = 2.0f * dot(P1, (P0 - center));
	float c = dot(P0 - center, P0 - center) - radius*radius;

	// Determine if this equation has atleast 1 solution
	float discriminant = b*b - 4*a*c;
	if (discriminant >= 0) {
		// Find the 2 solutions and pick the smaller one
		float soln_1 = (-b + sqrt(discriminant)) / (2 * a);
		float soln_2 = (-b - sqrt(discriminant)) / (2 * a);

		if (soln_1 > 0 && soln_2 > 0)
			// Both solutions positive. Pick smaller (closer) one
			*t_hit = (soln_1 < soln_2) ? soln_1 : soln_2;
		else
			// One of the solutions is negative. Pick positive one
			*t_hit = (soln_1 > soln_2) ? soln_1 : soln_2;

		// Make sure t_hit is at least larger than Ray's t_min
		if (*t_hit < ray.get_tmin()) {
			t_hit = NULL;
			normal = NULL;
			return false;
		}

		*normal = normalize(ray.evaluate(*t_hit) - center);
		return true;
	}

	// No intersection
	t_hit = NULL;
	normal = NULL;
	return false;
}

/*--------------[ Getter methods ]--------------*/
vec3 Sphere::get_center()	{ return center; }
float Sphere::get_radius()	{ return radius; }
