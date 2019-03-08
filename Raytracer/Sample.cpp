#include "pch.h"
#include "Sample.h"


Sample::Sample()
{
}

Sample::Sample(int x, int y) {
	this->x = x;
	this->y = y;
}

int Sample::getX() {
	return this->x;
}

int Sample::getY() {
	return this->y;
}