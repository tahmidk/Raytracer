#ifndef H_Intersection
#define H_Intersection

#include "Scene.h"

class Intersection
{
private:
	vec3 posn;
	vec3 normal;
	bool intersecting;
	Object* obj;

public:
	Intersection();
	~Intersection();
};

#endif