#ifndef H_Bucket
#define H_Bucket

#include <vector>

#include "Color.h"

class Bucket
{
private:
	std::vector<Color> colors;
public:
	Bucket();
	~Bucket();
	void addColor(Color col2);
	Color computeAverage();
};

#endif