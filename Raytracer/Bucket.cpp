#include "pch.h"
#include "Bucket.h"


Bucket::Bucket()
{
}


Bucket::~Bucket()
{
}

void Bucket::addColor(Color col2)
{
	this->colors.push_back(col2);
}

Color Bucket::computeAverage()
{
	Color sum = Color(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < this->colors.size(); i++) {
		sum = sum + colors[i];
	}
	return sum / this->colors.size();
}
