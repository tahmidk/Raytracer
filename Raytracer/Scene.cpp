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
#include "Raytracer.h"

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
		this->objects[i] = nullptr;
	// Nullify all lights
	for (int i = 0; i < NUM_LIGHTS; i++)
		this->lights[i] = nullptr;

	// Store defaults
	this->ambient = Color(0.2f, 0.2f, 0.2f);
	this->diffuse = COLORS::black;
	this->emission = COLORS::black;
	this->specular = COLORS::black;
	this->shininess = 1.0f;
	this->attenuation[0] = 1.0f;
	this->attenuation[1] = 0.0f;
	this->attenuation[2] = 0.0f;
	this->depth = 5;
	this->path = "test.png";
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
	for (int i = 0; this->objects[i] != nullptr; i++)
		delete (this->objects[i]);
	// Delete all lights
	for (int i = 0; this->lights[i] != nullptr; i++)
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
	cerr << "Rendering scene..." << endl;
	cerr << "  File:          " << path << endl;
	cerr << "  Size:          " << w << "x" << h << endl;
	cerr << "  Acceleration:  " << (ACCELERATE ? "ON" : "OFF") << endl;
	cerr << "  Max Node Size: " << MAX_NODE_SIZE << endl << endl;

	// Initialize the tracer
	this->raytracer = Raytracer(objects);

	// Make a new image of size (this->w) by (this->h)
	Film * film = new Film(w, h);
	for (int pixel_x = 0; pixel_x < w; pixel_x++) {
		for (int pixel_y = 0; pixel_y < h; pixel_y++) {
			// Half-way Progress
			if (pixel_x == w/2 && pixel_y == h/2)
				cerr << "Reached center" << endl;

			// Cast and trace ray
			Sample sample = Sample(pixel_x, pixel_y);
			Ray raySample = cam.generateRay(sample, camPos, w, h);
			HitInfo hit = raytracer.trace(raySample);
			if (hit.is_valid()) {
				Color hit_color = determine_color(&hit, raySample);
				film->commit(sample, hit_color);
			}
		}
	}

	// Output the PNG file
	cerr << "Writing to image file..." << endl;
	film->writeImage(path);
	delete film;
}

/*-------------------------------------------------------------------
	Func:	[determine_color]
	Args:	hit_info - the collision data to base color calculations on
			ray_in - the incoming ray
			eye - the relative eye/camera position
			depth - the maximum recursive depth
	Desc:	Determines the final color of a ray intersection using the 
			given collision data and incoming ray
	Rtrn:	The color of intersection
-------------------------------------------------------------------*/
Color Scene::determine_color(HitInfo * hit_info, Ray & ray_in) {
	return _determine_color(hit_info, ray_in, this->camPos, this->depth);
}

/*-------------------------------------------------------------------
	Func:	[_determine_color]
	Args:	hit_info - the collision data to base color calculations on
			ray_in - the incoming ray
			eye - the relative eye/camera position 
			depth - the maximum recursive depth
	Desc:	A helper recursive method that determines the final color of 
			a ray intersection using the given collision data
	Rtrn:	The color of intersection
-------------------------------------------------------------------*/
Color Scene::_determine_color(HitInfo * hit_info, Ray & ray_in, vec3 eye, const int depth)
{
	// Base case
	if (depth == 0)
		return Color();

	// Extract material data from HitInfo
	Material obj_mat = hit_info->get_object()->get_material();
	Color diffuse = obj_mat.get_diffuse();
	Color ambient = obj_mat.get_ambient();
	Color emission = obj_mat.get_emission();
	Color specular = obj_mat.get_specular();
	double shininess = obj_mat.get_shininess();

	// For each visible light, do the respective calculations
	// I = A + E + (Li / attenuation)*(D*max(N dot L, 0) + S*max(N dot H, 0)^s) for each visible light
	Light ** lights = getAllLights();
	Light * curr_light = lights[0];
	Color finalCol = ambient + emission;
	for (int light_num = 0; curr_light != nullptr; light_num++) {
		// Light is visible iff its shadow ray does not collide with another object
		vec3 P0 = hit_info->get_point();
		vec3 P1 = curr_light->get_towards_dirn(P0);
		float t_max = curr_light->get_tmax(P0);
		Ray shadowRay(P0, P1, t_max);

		HitInfo collision = raytracer.trace(shadowRay);
		if (!collision.is_valid()) {
			// Compute shading for this light
			Color shading = curr_light->calculate_shading(hit_info, eye, attenuation);
			finalCol = finalCol + shading;
		}

		// Update for next iteration
		curr_light = lights[light_num + 1];
	}

	// Finally, do tail recursive reflection calculations
	Ray ray_refl = Ray(hit_info->get_norm(), hit_info->get_point(), ray_in);
	HitInfo hit_refl = raytracer.trace(ray_refl);
	if (hit_refl.is_valid()) {
		// Calculate reflection
		vec3 new_eye = hit_info->get_point();
		return finalCol + (specular * _determine_color(&hit_refl, ray_refl, new_eye, depth - 1));
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

std::string Scene::getPath()
{
	return this->path;
}

vector<vec3> Scene::getVertices()	{ return this->vertices; }
