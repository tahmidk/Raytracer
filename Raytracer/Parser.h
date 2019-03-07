#ifndef H_Parser
#define H_Parser

#include "Scene.h"

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

