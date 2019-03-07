#include "pch.h"
#include "Color.h"


Color::Color(){
		r = 0.0;
		g = 0.0;
		b = 0.0;
}

Color::Color(double red, double green, double blue) : r(red), g(green), b(blue) {

}

Color Color::operator+(const Color& col2) {
	Color ret(this->r+col2.r, this->g + col2.g, this->b + col2.b);
	return ret;
}

double Color::getRed()
{
	return this->r;
}

double Color::getGreen()
{
	return this->g;
}

double Color::getBlue()
{
	return this->b;
}
