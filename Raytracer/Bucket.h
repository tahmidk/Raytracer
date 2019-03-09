#ifndef H_Bucket
#define H_Bucket

// Standard library imports
#include <vector>

// Project file imports
#include "Color.h"

using namespace std;

class Bucket
{
private:
	vector<Color> colors;

public:
	Bucket() {};

	// Utilite methods
	void addColor(Color col2);
	Color computeAverage();
};

#endif