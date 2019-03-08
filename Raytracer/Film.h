#ifndef H_Film
#define H_Film

// Standard library imports
#include <vector>

// Project file imports
#include "Scene.h"
#include "Camera.h"
#include "FreeImage.h"

class Film
{
private:
	std::vector<vector<Color>> pixel;
public:
	Film();

	void writeImage(string path);
	void commit(Sampler& sample, Color& col);
};

#endif