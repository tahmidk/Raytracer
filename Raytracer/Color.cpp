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

Color Color::operator/(const float c)
{
	if(c != 0)
		return Color(this->r/c, this->g/c, this->b/c);

	return COLORS::black;
}

Color Color::operator*(const float c) {
	return Color(r*c, g*c, b*c);
}

Color Color::operator*(Color other) {
	return Color(r*other.r, g*other.g, b*other.b);
}

/*---------------[ Getter Methods ]----------------*/
double Color::getRed()		{ return (this->r > 1.0) ? 1.0 : this->r; }
double Color::getGreen()	{ return (this->g > 1.0) ? 1.0 : this->g; }
double Color::getBlue()		{ return (this->b > 1.0) ? 1.0 : this->b; }
