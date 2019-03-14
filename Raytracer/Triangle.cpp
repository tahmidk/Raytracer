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
Triangle::Triangle(Material mat, mat4 transf, vec3 vert_a, vec3 vert_b, vec3 vert_c) :
	Object::Object(mat, transf)
{
	this->obj_type = triangle;
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
bool Triangle::intersects_ray(Ray & ray, float * t_hit, vec3 * normal)
{
	// First, get point where ray intersects plane of triangle
	vec3 vec_AB = vert_b - vert_a;
	vec3 vec_AC = vert_c - vert_a;

	// Ray parameters
	vec3 P0 = ray.get_posn();
	vec3 P1 = ray.get_dirn();
	// Surface normal
	vec3 N = normalize(cross(vec_AB, vec_AC));

	float numer = dot(vert_a, N) - dot(P0, N);
	float denom = dot(P1, N);

	if (denom != 0) {
		float t_plane = numer / denom;
		if (t_plane < ray.get_tmin() || t_plane > ray.get_tmax()){
			t_hit = NULL;
			normal = NULL;
			return false;
		}

		// It intersects, get the point on the plane where ray intersects
		vec3 P_ray = ray.evaluate(t_plane);

		// See if P is in this triangle ABC using the area method
		float area_ABP = area(vert_a, vert_b, P_ray);
		float area_ACP = area(vert_a, vert_c, P_ray);
		float area_BCP = area(vert_b, vert_c, P_ray);
		float partial_area = area_ABP + area_ACP + area_BCP;
		float total_area = area();

		// P is in ABC if the subtriangles' areas roughly add up to the large triangle's
		if (partial_area <= total_area + TOLERANCE && partial_area >= total_area - TOLERANCE) {
			*t_hit = t_plane;
			*normal = N;
			return true;
		}
	}

	// No intersection
	t_hit = NULL;
	normal = NULL;
	return false;
}

/*-------------------------------------------------------------------
	Func:	[area]
	Args:	None
	Desc:	Calculate the area of this triangle
	Rtrn:	The area
-------------------------------------------------------------------*/
float Triangle::area() {
	return area(vert_a, vert_b, vert_c);
}

/*-------------------------------------------------------------------
	Func:	[area]
	Args:	vert_A - the first vertex
			vert_B - the second vertex
			vert_C - the third vertex
	Desc:	Calculate the area of this triangle
	Rtrn:	The area
-------------------------------------------------------------------*/
float Triangle::area(vec3 vert_A, vec3 vert_B, vec3 vert_C) {
	vec3 vec_AB = vert_B - vert_A;
	vec3 vec_AC = vert_C - vert_A;

	float area = 0.5f * length(cross(vec_AB, vec_AC));
	return abs(area);
}

/*--------------[ Getter Methods ]--------------*/
void Triangle::getVertices(vec3 * a, vec3 * b, vec3 * c)
{
	a = &(this->vert_a);
	b = &(this->vert_b);
	c = &(this->vert_c);
}
