#ifndef H_Raytracer
#define H_Raytracer

// Standard library imports
#include <limits>

// Project file imports
#include "Ray.h"
#include "Color.h"
#include "Scene.h"
#include "HitInfo.h"

// Function declaration
HitInfo trace(Ray &ray, Scene * scene);

#endif