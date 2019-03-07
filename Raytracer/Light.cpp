#include "pch.h"
#include "Light.h"

Light::Light(Color col, vec3 posn)
{
	this->color = color;
	this->posn = posn;
}

/*------------[ Getter Methods ]------------*/
Color Light::getColor()	{ return color; }
vec3 Light::getPosn()	{ return posn; }
