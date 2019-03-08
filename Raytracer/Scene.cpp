/*==================================================================
	File:	[Scene.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains important information and code to
			build the environment and output the scene as a .png
			file
==================================================================*/

#include "pch.h"
#include "Scene.h"
#include "HitInfo.h"
#include "Raytracer.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Scene]
	Args:	None
	Desc:	Constructor doesn't do anything other than make the Scene
			object
	Rtrn:	None
-------------------------------------------------------------------*/
Scene::Scene()
{
}

Scene::~Scene()
{
	delete[] this->objects;
	delete[] this->lights;
}

/*-------------------------------------------------------------------
	Func:	[render]
	Args:	None
	Desc:	The main function responsible for rendering the output
			image. Iteratively calculates the color of each pixel
			by raytracing and writes the final image file
	Rtrn:	None
-------------------------------------------------------------------*/
void Scene::render(Camera & cam)
{ 
	// Make a new image of size (this->w) by (this->h)
	
	// NOTE: Wrap this in some loop over all samples
	{
		//Ray ray_sample() = cam.generateRay(sample, camPos, w, h);
		//HitInfo hit_info = trace(ray_sample, this);
		// Commit the color to film
	}

	// Output the PNG file
}

/*--------------[ Getter Methods ]----------------*/
// Camera fields
vec3 Scene::getCamPos()				{ return this->camPos; }
vec3 Scene::getUpVector()			{ return this->up; }
vec3 Scene::getLookAt()				{ return this->lookAt; }
vec3 Scene::getEyeInit()			{ return this->eyeinit; }
vec3 Scene::getCenter()				{ return this->center; }
double Scene::getFovy()				{ return this->fovy; }
double Scene::getWidth()			{ return this->w; }
double Scene::getHeight()			{ return this->h; }

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
int Scene::getNumObjects()		{ return num_objects; }
int Scene::getNumLights()		{ return num_lights; }