/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file represents a generic light. It serves as a
			superclass for children classes DirectionalLight and
			PointLight
==================================================================*/

// Project file imports
#include "pch.h"
#include "Light.h"

// Standard library imports
#include <algorithm>
#include <iostream>

/*-------------------------------------------------------------------
	Func:	Constructor: [Light]
	Args:	col - the color of this light
			posn - the position or direction of this light, interpretation
					dependent on what specific type of light this is
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Light::Light(Color col, vec3 posn)
{
	this->color = col;
	this->posn = posn;
}

/*-------------------------------------------------------------------
	Func:	[compute_lighting]
	Args:	dirn - the direction from hit point towards light.
			half - the half angle between normal and reflected ray
			atten - the constant, linear, and quadratic attenuation constants
			hit_info - the hit data
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	The resulting shaded color
-------------------------------------------------------------------*/
Color Light::compute_lighting(vec3 dirn, vec3 half, double * atten, HitInfo * hit_info)
{
	// Extract useful info from hit info
	Material obj_mat = hit_info->get_object()->get_material();
	vec3 hit_pos = hit_info->get_point();
	vec3 norm = hit_info->get_norm();

	// Normalize the directions just in case (hit_info's norm is normalized guaranteed)
	dirn = normalize(dirn);
	half = normalize(half);

	// Calculate lambert term
	float nDotL = (dot(norm, dirn) > 0.0f) ? dot(norm, dirn) : 0.0f;
	Color lambert = obj_mat.get_diffuse() * nDotL;

	// Calculate phong term
	float nDotH = (dot(norm, half) > 0.0f) ? dot(norm, half) : 0.0f;
	Color phong = obj_mat.get_specular() * (float) pow(nDotH, obj_mat.get_shininess());

	// Calculate attenuation for point lights (dirn lights have attenuation of 1)
	float attenuation = 1.0f;
	if(atten != nullptr){
		float dist = length(this->posn - hit_pos);
		attenuation = (float) (atten[0] + atten[1]*dist + atten[2]*dist*dist);
		// Sanity check in case attenuation is still 0
		if (attenuation == 0) {
			cerr << "Attenuation is still 0!" << endl;
			attenuation = 1.0f;
		}
	}

	// I = Li / attenuation * (D*max(N dot L, 0) + S*max(N dot H)^shininess)
	Color retval = (this->color / attenuation) * (lambert + phong);
	return retval;
}

/*------------[ Getter Methods ]------------*/
Color Light::get_color()	{ return color; }
vec3 Light::get_posn()		{ return posn; }
