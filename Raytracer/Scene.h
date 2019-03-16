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
#include "Light.h"
#include "Camera.h"
#include "Sample.h"
#include "Film.h"
#include "Raytracer.h"

using namespace glm;
using namespace std;

// Important constants
constexpr int NUM_OBJECTS = 2000;
constexpr int NUM_LIGHTS = 2000;

class Scene {
// Private fields
private:
	// Width and Height
	int w, h;

	// Camera fields
	vec3 camPos;
	vec3 eyeinit;
	vec3 up;
	vec3 lookAt;
	double fovy;
	vec3 center;

	// General fields for other classes
	vector<vec3> vertices;
	Color ambient;
	Color diffuse;
	Color emission;
	Color specular;
	double shininess;
	double attenuation[3];
	int depth;

	// List of objects and lights
	Object * objects[NUM_OBJECTS];
	int num_objects;
	Light * lights[NUM_LIGHTS];
	int num_lights;

	// Path for output
	string path;

	// Scene renderer
	Raytracer raytracer;

	// Allow Parser class to set Scene's private fields
	friend class Parser;

// Public fields
public:
	Scene();
	~Scene();

	// Utility methods
	void render(Camera & cam, string path);
	Color determine_color(HitInfo * hit_info, Ray & ray_in);
	Color _determine_color(HitInfo * hit_info, Ray & ray_in, vec3 eye, const int depth);

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
	double * getAttenuation();
	int getMaxDepth();

	vector<vec3> getVertices();

	Object ** getAllObjects();
	Light ** getAllLights();
	int getNumObjects();
	int getNumLights();
	std::string getPath();
};

#endif
