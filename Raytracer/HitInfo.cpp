/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the implementation of the data 
			structure used to record and communicate hit/collision
			information between rays and scene objects
==================================================================*/

#include "pch.h"
#include "HitInfo.h"

using namespace std;

/*-------------------------------------------------------------------
	Func:	Default Constructor [HitInfo]
	Args:	None
	Desc:	Defaults all instance fields to degenerate initializations
			HitInfo's made this way do not count as valid intersections
	Rtrn:	None
-------------------------------------------------------------------*/
HitInfo::HitInfo() {
	this->valid = false;
	this->t_hit = numeric_limits<float>::infinity();
	this->P_hit = vec3();
	this->norm = vec3();
	this->obj_hit = NULL;
}

/*-------------------------------------------------------------------
	Func:	Constructor [HitInfo]
	Args:	t - the t parameter of the Ray at intersection
			P - the 3D point of intersection
			N - the 3D surface normal at the intersection
			obj - a pointer to the object of collision
	Desc:	This constructor initializes all fields accordingly
	Rtrn:	None
-------------------------------------------------------------------*/
HitInfo::HitInfo(float t, vec3 P, vec3 N, Object * obj) {
	this->valid = true;
	this->t_hit = t;
	this->P_hit = P;
	this->norm = normalize(N);
	this->obj_hit = obj;
}

/*------------[ Getter Methods ]--------------*/
bool HitInfo::is_valid()		{ return this->valid; }
float HitInfo::get_t()			{ return this->t_hit; }
vec3 HitInfo::get_point()		{ return this->P_hit; }
vec3 HitInfo::get_norm()		{ return this->norm; }
Object * HitInfo::get_object()	{ return this->obj_hit; }
