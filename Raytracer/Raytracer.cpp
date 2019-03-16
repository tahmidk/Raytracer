/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains implementation of the base raytracing
			algorithm
==================================================================*/

#include "pch.h"
#include "Raytracer.h"

Raytracer::Raytracer()
{
	this->objects = nullptr;
	this->accelerated = false;
	this->bvh = BVHTree();
}

/*-------------------------------------------------------------------
	Func:	Constructor: [Raytracer]
	Args:	acceleration - use acceleration or not

	Desc:	This function traces the given ray to see if it collides
			with any objects initialized in the scene. If so, it
			returns the appropriate collision data stored in a HitInfo
			object
	Rtrn:	The HitInfo object representing the closest collision
-------------------------------------------------------------------*/
Raytracer::Raytracer(bool acceleration, Object ** objects)
{
	this->objects = objects;
	this->accelerated = acceleration;
	this->bvh = (acceleration) ? BVHTree(objects) : BVHTree();
}

/*-------------------------------------------------------------------
	Func:	[trace]
	Args:	ray - the ray to evaluate for collisions
	Desc:	Delegates to either the normal trace implementation or
			the accelerate trace implementation
	Rtrn:	The HitInfo object representing the closest collision
-------------------------------------------------------------------*/
HitInfo Raytracer::trace(Ray & ray)
{
	if (this->accelerated)
		return trace_accel(ray);

	return trace_normal(ray);
}

/*-------------------------------------------------------------------
	Func:	[trace_normal]
	Args:	ray - the ray to evaluate for collisions
	Desc:	This function traces the given ray to see if it collides
			with any objects initialized in the scene. If so, it 
			returns the appropriate collision data stored in a HitInfo 
			object
	Rtrn:	The HitInfo object representing the closest collision
-------------------------------------------------------------------*/
HitInfo Raytracer::trace_normal(Ray & ray)
{
	// True if at least 1 Ray-Scene collision detected, false otherwise
	bool collision = false;

	// Set minimum distance to collided object to infinity and object to NULL
	float t_min = numeric_limits<float>::infinity();
	vec3 P_hit;		// A variable to hold point of collision in world-coord
	vec3 norm_hit;	// A variable to hold surface normal at point of contact
	Object * obj_hit = nullptr;

	// Loop over all objects in the scene scouring for intersections
	Object ** objects = this->objects;
	Object * curr_obj = objects[0];
	for (int obj_num = 0; curr_obj != nullptr; obj_num++) {
		float t_hit;	// Output parameter to store t parameter at hit location
		vec3 norm;		// Output parameter to store surface normal

		// Transform ray by inverse M before running the intersection test
		mat4 M = curr_obj->get_transf();
		mat4 M_inv = inverse(M);
		Ray ray_transf = ray.transformRay(M_inv);
		bool intersects = curr_obj->intersects_ray(ray_transf, &t_hit, &norm);

		// If the intersection is closer to the ray origin, record it as long
		// as it's also greater than the minimum allowed t for this array
		if (intersects && (t_hit > ray.get_tmin())  && (t_hit < t_min)) {
			// Collision detected
			collision = true;

			// Appropriately re-untransform and update point and surface normal at hit point
			t_min = t_hit;
			P_hit = vec3(M * vec4(ray_transf.evaluate(t_min), 1.0f));
			norm_hit = vec3(transpose(M_inv) * vec4(norm, 0.0f));
			obj_hit = curr_obj;
		}

		// Update for next iteration
		curr_obj = objects[obj_num + 1];
	}

	// At least 1 collision detected
	if (collision == true)
		return HitInfo(t_min, P_hit, norm_hit, obj_hit);

	// Not collisions w/ any of the objects in this scene
	return HitInfo();
}

/*-------------------------------------------------------------------
	Func:	[trace_accel]
	Args:	ray - the ray to evaluate for collisions
	Desc:	Same as [trace] but using an acceleration structure in the
			form of a BVH Tree
	Rtrn:	The HitInfo object representing the closest collision
-------------------------------------------------------------------*/
HitInfo Raytracer::trace_accel(Ray & ray)
{
	HitInfo hit_info;
	
	bool collision = bvh.intersect(ray, &hit_info);
	if (collision == true)
		return hit_info;

	return HitInfo();
}