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
	Func:	General Constructor: [Ray]
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
	this->t_min = 0;
}

/*-------------------------------------------------------------------
	Func:	Restricted Constructor: [Ray]
	Args:	posn - the start position of the ray
			dirn - the direction of the ray
			epsilon - very small epsilon shift value to prevent rounding 
				errors when checking for intersections
	Desc:	Constructs a restricted Ray object represented by the equation:
				{ Ray = posn + dirn*t }		for		t_min <= t <= t_max
	Rtrn:	None
-------------------------------------------------------------------*/
Ray::Ray(vec3 posn, vec3 dirn, float epsilon)
{
	this->posn = posn;
	this->dirn = dirn;
	this->t_min = epsilon;
}

/*-------------------------------------------------------------------
	Func:	Reflected Ray Constructor: [Ray]
	Args:	norm - the surface normal at the reflection point
			posn - the point of reflection
			ray_in - the incident ray
	Desc:	Generates a light ray from a point towards a light source
	Rtrn:	None
-------------------------------------------------------------------*/
Ray::Ray(vec3 norm, vec3 posn, Ray ray_in) {
	vec3 v_in = ray_in.get_dirn();

	// Use Snell's law to compute reflected ray: v_out = v_in - 2(v_in dot n)n
	vec3 v_out = v_in - 2*dot(v_in, norm)*norm;

	this->posn = posn;
	this->dirn = v_out;
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

/*-------------------------------------------------------------------
	Func:	[transformRay]
	Args:	transf - the 4x4 transformation matrix
	Desc:	Returns the ray resulting from transforming this ray with
			the given transformation matrix. Does not mutate this Ray
	Rtrn:	The transformed Ray
-------------------------------------------------------------------*/
Ray Ray::transformRay(mat4 transf) {
	// Convert ray components to homogeneous coordinates
	vec4 posn_hom = vec4(posn.x, posn.y, posn.z, 1.0f);
	vec4 dirn_hom = vec4(dirn.x, dirn.y, dirn.z, 0.0f);
	//normalize(dirn_hom);

	// Apply transformation to both
	vec4 posn_transf = transf * posn_hom;
	vec4 dirn_transf = transf * dirn_hom;
	//normalize(dirn_transf);

	// Reconvert back to vec3
	vec3 posn_new = vec3(posn_transf.x, posn_transf.y, posn_transf.z);
	vec3 dirn_new = vec3(dirn_transf.x, dirn_transf.y, dirn_transf.z);
	return Ray(posn_new, dirn_new, this->t_min);
}

/*------------[ Getter methods ]-------------*/
vec3 Ray::get_posn()	{ return posn; }
vec3 Ray::get_dirn()	{ return dirn; }
float Ray::get_tmin()	{ return t_min; }
