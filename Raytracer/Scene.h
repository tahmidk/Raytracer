#ifndef SCENE_CPP
#define SCENE_CPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Transform.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"

using namespace std;
using namespace glm;

class Scene {
private:
	int w, h;

	// Camera fields
	vec3 camPos;
	vec3 up;
	vec3 lookAt;
	double fovy;

	// Object fields
	Color ambient;
	Color diffuse;
	Color emission;
	Color specular;
	double shininess;
	double attenuation[3];

	// List of objects and lights
	Object objects[100];
	Light lights[100];

	vector<vec3> vertices;
	int maxverts;

	int depth;
	vec3 eyeinit;
	vec3 center;
public:
	Scene();
	void readFile(const char* filename);
};

#endif