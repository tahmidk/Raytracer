#include "pch.h"
#include "Point.h"

Point::Point(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/*-----------[ Getter Methods ]-----------*/
float Point::get_x() { return x; }
float Point::get_y() { return y; }
float Point::get_z() { return z; }
