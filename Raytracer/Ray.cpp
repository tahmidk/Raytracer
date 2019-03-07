/*==================================================================
	File:	[Ray.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the base implementation of a Ray, 
			defined by a start point and a direction as well as the
			time parameter t
==================================================================*/

#include "pch.h"
#include "Ray.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Ray]
	Args:	posn - the start position of the ray
			dirn - the direction of the ray
	Desc:	Constructs a Ray object represented by the equation:
				{ Ray = posn + dirn*t }
			for some time parameter t
	Rtrn:	None
-------------------------------------------------------------------*/
Ray::Ray(vec3 posn, vec3 dirn)
{
	this->posn = posn;
	this->dirn = dirn;
}

Ray::Ray(vec3 posn, vec3 dirn, float t_min, float t_max)
{
	this->posn = normalize(posn);
	this->dirn = normalize(dirn);
	this->t_min = t_min;
	this->t_max = t_max;
}

/*-------------------------------------------------------------------
	Func:	[evaluate]
	Args:	t - the t parameter to evaluate Ray at
	Desc:	Evaluates and returns the vector 3 representing the ray
			at time t
	Rtrn:	Ray(t)
-------------------------------------------------------------------*/
vec3 Ray::evaluate(float t)
{
	vec3 eval = posn + t * dirn;
	return eval;
}

/*------------[ Getter methods ]-------------*/
vec3 Ray::get_posn()	{ return posn; }
vec3 Ray::get_dirn()	{ return dirn; }
float Ray::get_tmin()	{ return t_min; }
float Ray::get_tmax()	{ return t_max; }
