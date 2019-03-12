#include "pch.h"
#include "Sample.h"


Sample::Sample()
{
}

Sample::Sample(int x, int y) {
	this->x = x + 0.5f;
	this->y = y + 0.5f;
}

float Sample::getX() {
	return this->x;
}

float Sample::getY() {
	return this->y;
}