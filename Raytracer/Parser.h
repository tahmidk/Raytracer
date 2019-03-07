#ifndef H_Parser
#define H_Parser

#include "Scene.h"

class Parser
{
public:
	Parser(const char* filename);

	Scene initScene();

private:
	void parseFile();

	// Instance fields
	const char * filename;
};

#endif // !H_Parser

