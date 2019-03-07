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

#define NUM_OBJECTS 100
#define NUM_LIGHTS 100

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
	Object * objects[NUM_OBJECTS];
	Light * lights[NUM_LIGHTS];

	vector<vec3> vertices;
	int maxverts;

	int depth;
	vec3 eyeinit;
	vec3 center;

	// Allow Parser class to set Scene's private fields
	friend class Parser;

public:
	Scene();
	void render();
};

#endif