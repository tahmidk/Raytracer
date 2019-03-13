/*==================================================================
	File:	[PointLight.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file represents a point light and is equipped with
			a method to do the appropriate lighting calculations
==================================================================*/

#include "pch.h"
#include "PointLight.h"

// Constructors do constructor stuff
PointLight::PointLight() {}
PointLight::PointLight(Color col, vec3 posn) : Light(col, posn) {}

/*-------------------------------------------------------------------
	Func:	[calculate_shading]
	Args:	hit_info - a reference to the hit data
			eye_pos - the position of the eye
			attenuation - the constant, linear, and quadratic attenuation constants
	Desc:	This method computes the color at the given intersection
			relative to the given position of observation (eye) due
			to this point light illuminating it
	Rtrn:	The resulting shaded color
-------------------------------------------------------------------*/
Color PointLight::calculate_shading(HitInfo * hit_info, vec3 eye_pos, double * attenuation)
{
	// Calculate direction from hitpoint to light
	vec3 dirn_L = normalize(this->posn - hit_info->get_point());

	// Calculate half-angle between direction to light and direction to eye
	vec3 dirn_eye = normalize(eye_pos - hit_info->get_point());
	vec3 dirn_half = normalize(dirn_L + dirn_eye);

	return compute_lighting(dirn_L, dirn_half, attenuation, hit_info);
}

/*-------------------------------------------------------------------
	Func:	[get_towards_dirn]
	Args:	from - the from-point 
	Desc:	This method gets the direction from the given point towards
			the point light's position
	Rtrn:	A normalized direction vector towards the light
-------------------------------------------------------------------*/
vec3 PointLight::get_towards_dirn(vec3 from) {
	return normalize(this->posn - from);
}

/*-------------------------------------------------------------------
	Func:	[get_tmax]
	Args:	from - the from-point
	Desc:	This method calculates the t-value at which a ray pointed
			towards this light from the given point would intersect
			the light itself. Used to restrict shadow rays
	Rtrn:	The t value
-------------------------------------------------------------------*/
float PointLight::get_tmax(vec3 from)
{
	vec3 dirn = get_towards_dirn(from);

	float t_max = 0.0f;
	if(dirn.x != 0.0f)
		t_max = ((this->posn).x - from.x) / dirn.x;
	else if (dirn.y != 0.0f)
		t_max = ((this->posn).y - from.y) / dirn.y;
	else if (dirn.z != 0.0f)
		t_max = ((this->posn).z - from.z) / dirn.z;

	return t_max;
}
