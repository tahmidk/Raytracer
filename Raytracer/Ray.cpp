/*==================================================================
	File:	[Ray.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a Ray, 
			defined by a start point and a direction as well as the
			distance parameter t
==================================================================*/

#include "pch.h"
#include "Ray.h"


Ray::Ray(vec3 posn, vec3 dirn, float t_min, float t_max)
{
	this->posn = posn;
	this->dirn = dirn;
	this->t_min = t_min;
	this->t_max = t_max;
}

/*------------[ Getter methods ]-------------*/
vec3 Ray::get_posn()	{ return posn; }
vec3 Ray::get_dirn()	{ return dirn; }
float Ray::get_tmin()	{ return t_min; }
float Ray::get_tmax()	{ return t_max; }
