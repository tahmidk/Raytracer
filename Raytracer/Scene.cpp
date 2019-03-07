#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	delete this->objects;
	delete this->lights;
}

void Scene::render()
{
}

/*--------------[ Getter Methods ]----------------*/
// Camera fields
vec3 Scene::getCamPos()				{ return this->camPos; }
vec3 Scene::getUpVector()			{ return this->up; }
vec3 Scene::getLookAt()				{ return this->lookAt; }
vec3 Scene::getEyeInit()			{ return this->eyeinit; }
vec3 Scene::getCenter()				{ return this->center; }
double Scene::getFovy()				{ return this->fovy; }
double Scene::getHeight()			{ return this->h; }
double Scene::getWidth()			{ return this->w; }

// Lighting and Material fields
Color Scene::getAmbient()			{ return this->ambient; }
Color Scene::getDiffuse()			{ return this->diffuse; }
Color Scene::getEmission()			{ return this->emission; }
Color Scene::getSpecular()			{ return this->specular; }
double Scene::getShininess()		{ return this->shininess; }

vector<vec3> Scene::getVertices()	{ return this->vertices; }

// Scene lists
Object ** Scene::getAllObjects()	{ return objects; }
Light ** Scene::getAllLights()		{ return lights; }
float Scene::getNumObjects()		{ return num_objects; }
float Scene::getNumLights()			{ return num_lights; }