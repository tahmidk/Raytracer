#ifndef H_Film
#define H_Film

// Standard library imports
#include <vector>
#include <string>

// Project file imports
#include "Sample.h"
#include "Color.h"
#include "Camera.h"
#include "FreeImage.h"

class Film
{
private:
	std::vector<std::vector<Color>> pixel;
	int width, height;
public:
	Film();
	Film(int width, int height);

	void writeImage(std::string path);
	void commit(Sample& sample, Color& col);
};

#endif