#include "pch.h"
#include "Light.h"

Light::Light(Color col, vec3 posn)
{
	this->color = color;
	this->posn = posn;
}

/*------------[ Getter Methods ]------------*/
Color Light::get_color()	{ return color; }
vec3 Light::get_posn()	{ return posn; }
