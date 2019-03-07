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
void trace(Ray & ray, const int depth, Color * color)
{

}