/*==================================================================
	File:	[Triangle.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a triangular
			surface in the raytracer program.
==================================================================*/

#include "pch.h"
#include "Triangle.h"

#include <algorithm>

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

	this->x_bounds = bounds(axis_x);
	this->y_bounds = bounds(axis_y);
	this->z_bounds = bounds(axis_z);
	this->centroid = calc_centroid();
}

/*-------------------------------------------------------------------
	Func:	[intersects_ray]
	Args:	ray - the ray to calculate intersection for
			t_hit - an output param to store the t of intersection
					or nullptr if no intersection
			normal - an output param to store the surface normal at
					the intersection or nullptr if no intersection
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
			t_hit = nullptr;
			normal = nullptr;
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
	t_hit = nullptr;
	normal = nullptr;
	return false;
}

/*-------------------------------------------------------------------
	Func:	[calc_centroid]
	Args:	None
	Desc:	Calculates and returns this primitive's centroid
	Rtrn:	The position of its transformed centroid
-------------------------------------------------------------------*/
vec3 Triangle::calc_centroid()
{
	vec3 center(
		(vert_a.x + vert_b.x + vert_c.x) / 3.0f,
		(vert_a.y + vert_b.y + vert_c.y) / 3.0f,
		(vert_a.z + vert_b.z + vert_c.z) / 3.0f
	);

	vec4 centroid = this->obj_transf * vec4(center, 1.0f);
	centroid = centroid / centroid.w;
	return vec3(centroid.x, centroid.y, centroid.z);
}

/*-------------------------------------------------------------------
	Func:	[bounds]
	Args:	a - the axis to consider
	Desc:	Calculates and returns the minimum and maximum bounds of
			this triangle along the given axis
	Rtrn:	A vector with the first element representing x_min and 
			the second representing x_max
-------------------------------------------------------------------*/
vec2 Triangle::bounds(axis a) {
	vec2 ret(0.0f, 0.0f);

	// First apply the transformations
	vec4 a_transf = this->obj_transf * vec4(this->vert_a, 1.0f);
	vec4 b_transf = this->obj_transf * vec4(this->vert_b, 1.0f);
	vec4 c_transf = this->obj_transf * vec4(this->vert_c, 1.0f);
	a_transf = a_transf / a_transf.w;
	b_transf = b_transf / b_transf.w;
	c_transf = c_transf / c_transf.w;

	// Calculate the bounds along axis a
	switch (a){
		case axis_x:
			ret[0] = std::min(std::min(a_transf.x, b_transf.x), c_transf.x);
			ret[1] = std::max(std::max(a_transf.x, b_transf.x), c_transf.x);
			break;
		case axis_y:
			ret[0] = std::min(std::min(a_transf.y, b_transf.y), c_transf.y);
			ret[1] = std::max(std::max(a_transf.y, b_transf.y), c_transf.y);
			break;
		case axis_z:
			ret[0] = std::min(std::min(a_transf.z, b_transf.z), c_transf.z);
			ret[1] = std::max(std::max(a_transf.z, b_transf.z), c_transf.z);
			break;
		default:
			break;
	}

	return ret;
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
