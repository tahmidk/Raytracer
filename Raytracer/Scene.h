#ifndef SCENE_CPP
#define SCENE_CPP

// GLM imports
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard library imports
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

// Project file imports
#include "Transform.h"
#include "Color.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
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
	vec3 eyeinit;
	vec3 center;

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

	// Allow Parser class to set Scene's private fields
	friend class Parser;

public:
	Scene();
	~Scene();
	void render();
};

#endif
