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
#include "Camera.h"
#include "Sample.h"
#include "Film.h"

using namespace std;
using namespace glm;

#define NUM_OBJECTS 100
#define NUM_LIGHTS 100

class Scene;

extern Scene* scn;

class Scene {
// Private fields
private:
	// Width and Height
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
	int num_objects;
	Light * lights[NUM_LIGHTS];
	int num_lights;

	vector<vec3> vertices;
	int maxverts;

	int depth;

	Film * film;
	// Allow Parser class to set Scene's private fields
	friend class Parser;

// Public fields
public:
	Scene();
	~Scene();

	// Utility methods
	void render(Camera & cam, std::string path);

	// Getter methods
	vec3 getCamPos();
	vec3 getUpVector();
	vec3 getLookAt();
	vec3 getEyeInit();
	vec3 getCenter();
	double getFovy();
	double getHeight();
	double getWidth();

	Color getAmbient();
	Color getDiffuse();
	Color getEmission();
	Color getSpecular();
	double getShininess();

	vector<vec3> getVertices();

	Object ** getAllObjects();
	Light ** getAllLights();
	int getNumObjects();
	int getNumLights();
};

#endif
