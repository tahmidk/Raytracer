#include "pch.h"
#include "Sampler.h"


Sampler::Sampler()
{
}

Sampler::Sampler(int x, int y) {
	this->x = x;
	this->y = y;
}

int Sampler::getX() {
	return this->x;
}

int Sampler::getY() {
	return this->y;
}