#ifndef H_Parser
#define H_Parser

#include "Scene.h"
#include "Triangle.h"
#include "Sphere.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class Parser
{
public:
	~Parser();
	Parser(const char* filename);
	void initScene(Scene* scene);

private:
	void parseFile(Scene * scene);

	// Instance fields
	const char * filename;
};

#endif // !H_Parser

