/*==================================================================
	File:	[Scene.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains important information and code to
			build the environment and output the scene as a .png
			file
==================================================================*/

// Project file imports
#include "pch.h"
#include "Scene.h"
#include "HitInfo.h"
#include "Raytracer.h"

// Standard library imports
#include <list>

/*-------------------------------------------------------------------
	Func:	Constructor: [Scene]
	Args:	None
	Desc:	Constructor doesn't do anything other than make the Scene
			object and initialize all objects and lights to NULL
	Rtrn:	None
-------------------------------------------------------------------*/
Scene::Scene()
{
	// Nullify all objects
	for (int i = 0; i < NUM_OBJECTS; i++)
		this->objects[i] = NULL;
	// Nullify all lights
	for (int i = 0; i < NUM_LIGHTS; i++)
		this->lights[i] = NULL;
}

/*-------------------------------------------------------------------
	Func:	Destructor: [Scene]
	Args:	None
	Desc:	Delete all dynamically allocated objects and lights
	Rtrn:	None
-------------------------------------------------------------------*/
Scene::~Scene()
{
	// Delete all objects
	for (int i = 0; this->objects[i] != NULL; i++)
		delete (this->objects[i]);
	// Delete all lights
	for (int i = 0; this->lights[i] != NULL; i++)
		delete (this->lights[i]);
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
	Film * film = new Film(w, h);
	for (int pixel_x = 0; pixel_x < w; pixel_x++) {
		for (int pixel_y = 0; pixel_y < h; pixel_y++) {
			Sample sample = Sample(pixel_x, pixel_y);
			Ray raySample = cam.generateRay(sample, camPos, w, h);
			HitInfo hit = trace(raySample, this);
			if (hit.is_valid()) {
				/* // Milestone code
				if (hit.get_object()->get_type() == triangle) {
					film->commit(sample, COLORS::green);
				}
				if (hit.get_object()->get_type() == sphere) {
					film->commit(sample, COLORS::white);
				}
				*/
				Color hit_color = determine_color(&hit, this->depth);
				film->commit(sample, hit_color);
			}

		}
	}

	// Output the PNG file
	film->writeImage(path);
	delete film;
}


/*-------------------------------------------------------------------
	Func:	[determine_color]
	Args:	hit_info - the collision data to base color calculations on
	Desc:	The main function responsible for rendering the output
			image. Iteratively calculates the color of each pixel
			by raytracing and writes the final image file
	Rtrn:	None
-------------------------------------------------------------------*/
Color Scene::determine_color(HitInfo * hit_info, const int depth)
{
	// Extract material data from HitInfo
	Material obj_mat = hit_info->get_object()->get_material();
	Color diffuse = obj_mat.get_diffuse();
	Color emission = obj_mat.get_emission();
	Color specular = obj_mat.get_specular();
	double shininess = obj_mat.get_shininess();

	// Determine which lights illuminate this hit point
	list<Light> visibleLights;

	Light ** lights = getAllLights();
	Light * curr_light = lights[0];
	for (int light_num = 0; curr_light != NULL; light_num++) {
		// Light is visible iff its shadow ray does not collide with another object
		vec3 P0 = hit_info->get_point();
		vec3 P1 = curr_light->get_towards_dirn(P0);
		Ray shadowRay(P0, P1, EPSILON);

		HitInfo collision = trace(shadowRay, this);
		if (!collision.is_valid())
			visibleLights.push_back(*curr_light);

		// Update for next iteration
		curr_light = lights[light_num + 1];
	}

	// For each visible light, do the respective calculations
	// I = A + E + (Li / attenuation)*(D*max(N dot L, 0) + S*max(N dot H, 0)^s) for each visible light
	Color finalCol = this->ambient + emission;
	for (Light light : visibleLights) {
		Color shading = light.calculate_shading(hit_info, this->camPos, attenuation);
		finalCol = finalCol + shading;
	}

	return finalCol;
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