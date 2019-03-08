/*==================================================================
	File:	[Color.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file represents an RGB color
==================================================================*/

#include "pch.h"
#include "Color.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Color]
	Args:	Either no args or:
			red - R color value
			green - G color value
			blue - B color value
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Color::Color() : r(0.0f), g(0.0f), b(0.0f) {}
Color::Color(double red, double green, double blue) : r(red), g(green), b(blue) {}

/*-------------[ Operator Overloads]---------------*/
Color Color::operator+(const Color& col2) {
	Color ret(this->r+col2.r, this->g + col2.g, this->b + col2.b);
	return ret;
}

/*---------------[ Getter Methods ]----------------*/
double Color::getRed()		{ return this->r; }
double Color::getGreen()	{ return this->g; }
double Color::getBlue()		{ return this->b; }
