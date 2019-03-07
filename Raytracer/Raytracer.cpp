/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains implementation of the base raytracing
			algorithm
==================================================================*/

#include "pch.h"
#include "Raytracer.h"

/*-------------------------------------------------------------------
	Func:	[trace]
	Args:	ray - the ray to evaluate for collisions
			depth - the maximum recursive depth to consider
			color - a reference to the color variable to manipulate
	Desc:	This function traces the given ray to see if it collides
			with any objects initialized in the scene. If so, it 
			assigns the appropriate color to the given color reference
			depending on scene lights and object properties. If it does
			not collide with any object, it sets color to black
	Rtrn:	None
-------------------------------------------------------------------*/
void trace(Ray & ray, Scene * scene)
{
	// Set minimum distance to collided object to infinity and object to NULL
	float t_min = numeric_limits<float>::infinity();
	Object * obj_hit = NULL;

	// Loop over all objects in the scene scouring for intersections
	Object ** objects = scene->getAllObjects();

	Object * curr_obj = objects[0];
	for (int obj_num = 0; curr_obj != NULL; obj_num++) {
		float * t_hit;	// Output parameter to store t parameter at hit location
		vec3 * norm;	// Output parameter to store surface normal

		// If the intersection is closer to the ray origin, record it
		bool intersects = curr_obj->intersects_ray(ray, t_hit, norm);
		if (intersects && (*t_hit > 0)  && (*t_hit < t_min)) {
			t_min = *t_hit;
			obj_hit = curr_obj;
		}

		// Update for next iteration
		curr_obj = objects[obj_num + 1];
	}
}