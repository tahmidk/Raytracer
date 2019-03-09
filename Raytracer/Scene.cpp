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
	//delete[] this->objects;
	//delete[] this->lights;
}

/*-------------------------------------------------------------------
	Func:	[render]
	Args:	cam - the camera
			path - file path and name of the output PNG file
	Desc:	The main function responsible for rendering the output
			image. Iteratively calculates the color of each pixel
			by raytracing and writes the final image file
	Rtrn:	None
-------------------------------------------------------------------*/
void Scene::render(Camera & cam, string path)
{ 
	// Make a new image of size (this->w) by (this->h)
	film = new Film(w, h);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			Sample sample = Sample(i, j);
			Ray raySample = cam.generateRay(sample, camPos, w, h);
			HitInfo hit = trace(raySample, this);
			if (hit.is_valid()) {
				if (hit.get_object()->get_type() == triangle) {
					film->commit(sample, COLORS::red);
				}
				if (hit.get_object()->get_type() == sphere) {
					film->commit(sample, COLORS::white);
				}

				//film->commit(sample, hit.get_object()->get_ambient());
			}

		}
	}
	// Output the PNG file
	film->writeImage(path);
	delete film;
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

// Lighting and Material Property fields
Color Scene::getAmbient()			{ return this->ambient; }
double * Scene::getAttenuation()	{ return this->attenuation; }
int Scene::getMaxDepth()			{ return this->depth; }

// Scene lists
Object ** Scene::getAllObjects()	{ return objects; }
Light ** Scene::getAllLights()		{ return lights; }
int Scene::getNumObjects()		{ return num_objects; }
int Scene::getNumLights()		{ return num_lights; }

vector<vec3> Scene::getVertices()	{ return this->vertices; }