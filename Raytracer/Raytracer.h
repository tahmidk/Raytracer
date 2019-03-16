#ifndef H_Raytracer
#define H_Raytracer

// Standard library imports
#include <limits>

// Project file imports
#include "BVHTree.h"

// Use acceleration or not
constexpr bool ACCELERATE = true;

class Raytracer 
{
private:
	BVHTree bvh;
	bool accelerated;
	Object ** objects;

	HitInfo trace_normal(Ray &ray);
	HitInfo trace_accel(Ray &ray);

public:
	// Constructor
	Raytracer();
	Raytracer(bool acceleration, Object ** objects);

	// Utility method
	HitInfo trace(Ray & ray);
};

#endif