/*==================================================================
	File:	[Sphere.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a sphere 
			in the raytracer program.
==================================================================*/

#include "pch.h"
#include "Sphere.h"

#include <algorithm>

constexpr float MOE = 0.001f;

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

	this->x_bounds = bounds(axis_x);
	this->y_bounds = bounds(axis_y);
	this->z_bounds = bounds(axis_z);
	this->centroid = calc_centroid();
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

		if (soln_1 + MOE > 0 && soln_2 + MOE > 0)
			// Both solutions positive. Pick smaller (closer) one
			*t_hit = (soln_1 < soln_2) ? soln_1 : soln_2;
		else
			// One of the solutions is negative. Pick positive one
			*t_hit = (soln_1 > soln_2) ? soln_1 : soln_2;

		// Make sure t_hit is at least larger than Ray's t_min
		if (*t_hit < ray.get_tmin() || *t_hit > ray.get_tmax()) {
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

/*-------------------------------------------------------------------
	Func:	[calc_centroid]
	Args:	None
	Desc:	Calculates and returns this primitive's centroid
	Rtrn:	The position of its transformed centroid
-------------------------------------------------------------------*/
vec3 Sphere::calc_centroid()
{
	vec4 centroid = this->obj_transf * vec4(this->center, 1.0f);
	centroid = centroid / centroid.w;
	return vec3(centroid.x, centroid.y, centroid.z);
}

/*-------------------------------------------------------------------
	Func:	[bounds]
	Args:	a - the axis to consider
	Desc:	Calculates and returns the minimum and maximum bounds of
			this sphere along the given axis
	Rtrn:	A vector with the first element representing x_min and
			the second representing x_max
-------------------------------------------------------------------*/
vec2 Sphere::bounds(axis a) {
	vec2 ret(0.0f);

	// Credit to: https://blog.yiningkarlli.com/2013/02/bounding-boxes-for-ellipsoids.html
	// for method to bound ellipsoid
	mat4 unit_sphere = mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f
	);
	mat4 R = this->obj_transf * inverse(unit_sphere) * transpose(this->obj_transf);
	float r11 = R[0][0];
	float r14 = R[3][0];
	float r22 = R[1][1];
	float r24 = R[3][1];
	float r33 = R[2][2];
	float r34 = R[3][2];
	float r44 = R[3][3];

	// Choose the appropriate bounds along axis a
	switch (a){
		case axis_x:
			ret[0] = std::min((r14 + sqrt(r14*r14 - r44 * r11)) / r44, (r14 - sqrt(r14*r14 - r44 * r11)) / r44);
			ret[1] = std::max((r14 + sqrt(r14*r14 - r44 * r11)) / r44, (r14 - sqrt(r14*r14 - r44 * r11)) / r44);
			break;
		case axis_y:
			ret[0] = std::min((r24 + sqrt(r24*r24 - r44 * r22)) / r44, (r24 - sqrt(r24*r24 - r44 * r22)) / r44);
			ret[1] = std::max((r24 + sqrt(r24*r24 - r44 * r22)) / r44, (r24 - sqrt(r24*r24 - r44 * r22)) / r44);
			break;
		case axis_z:
			ret[0] = std::min((r34 + sqrt(r34*r34 - r44 * r33)) / r44, (r34 - sqrt(r34*r34 - r44 * r33)) / r44);
			ret[1] = std::max((r34 + sqrt(r34*r34 - r44 * r33)) / r44, (r34 - sqrt(r34*r34 - r44 * r33)) / r44);
			break;
		default:
			break;
	}

	return ret;
}

/*--------------[ Getter methods ]--------------*/
vec3 Sphere::get_center()	{ return center; }
float Sphere::get_radius()	{ return radius; }
