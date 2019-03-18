/*==================================================================
	File:	[DirectionalLight.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file represents a directional light and is equipped 
			with a method to do the appropriate lighting calculations
==================================================================*/

#include "pch.h"
#include "DirectionalLight.h"

// Constructors do constructor stuff
DirectionalLight::DirectionalLight() {}
DirectionalLight::DirectionalLight(Color col, vec3 posn) : Light(col, posn) {}

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
Color DirectionalLight::calculate_shading(HitInfo * hit_info, vec3 eye_pos, double * attenuation)
{
	// For directional lights, this->posn is actually just its direction
	vec3 dirn_L = normalize(this->posn);

	// Calculate half-angle between direction to light and direction to eye
	vec3 dirn_eye = normalize(eye_pos - hit_info->get_point());
	vec3 dirn_half = normalize(dirn_L + dirn_eye);

	return compute_lighting(dirn_L, dirn_half, nullptr, hit_info);
}

/*-------------------------------------------------------------------
	Func:	[get_towards_dirn]
	Args:	from - the from-point
	Desc:	This method gets the direction from the given point towards
			the point light's position. For Directional Lights though,
			direction is always just given by this->posn. Then, the 
			direction from point to light is just the reverse of that.
	Rtrn:	A normalized direction vector towards the light
-------------------------------------------------------------------*/
vec3 DirectionalLight::get_towards_dirn(vec3 from) {
	return (this->posn);
}

/*-------------------------------------------------------------------
	Func:	[get_tmax]
	Args:	from - the from-point
	Desc:	This method calculates the t-value at which a ray pointed
			towards this light from the given point would intersect
			the light itself. Used to restrict shadow rays. For directional
			lights, this it just infinity
	Rtrn:	The t value
-------------------------------------------------------------------*/
float DirectionalLight::get_tmax(vec3 from) {
	return std::numeric_limits<float>::infinity();
}
