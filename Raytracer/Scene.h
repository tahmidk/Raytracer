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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
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
	Object* objects[100];
	Light* lights[100];

	vector<vec3> vertices;
	int maxverts;

	int depth;

public:
	Scene();
	void readFile(const char* filename);
};

#endif