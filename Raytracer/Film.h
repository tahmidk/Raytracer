#ifndef H_Film
#define H_Film

#include <vector>
#include "Scene.h"
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