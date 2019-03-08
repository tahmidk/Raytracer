/*==================================================================
	File:	[Camera.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file builds a basic camera and implements methods
			to cast rays from said camera to a given pixel location
==================================================================*/

// Project file imports
#include "pch.h"
#include "Transform.h"
#include "Camera.h"
#include <iostream>

/*-------------------------------------------------------------------
	Func:	Constructor: [Scene]
	Args:	eye - the position of the camera
			center - the output of lookAt
			up - the up direction of the camera
			fovy - the vertical field of view in degrees
			width - the width of the image plane
			height - the height of the image plane
	Desc:	Constructor derives camera vectors and initializes all
			camera parameters
	Rtrn:	None
-------------------------------------------------------------------*/
Camera::Camera(vec3 eye, vec3 center, vec3 up, double fovy, double width, 
	double height)
{
	// Set basic camera vectors
	this->w = normalize(eye - center);
	this->up = normalize(cross(up, w));
	this->v = glm::cross(w, this->up);

	// Convert FOV-y from degrees to radians
	this->fovy = fovy * PI  / 180.0;

	// Initialize FOV-x
	double z = tan(this->fovy / 2);
	z = (1 / z) * height / 2;
	this->fovx = 2 * atan((width / 2) / z);
}

/*-------------------------------------------------------------------
	Func:	[generateRay]
	Args:	sample - the sample to serve as the endpoint of the Ray
			eye - the position of the camera
			w - the scene width
			h - the scene height
	Desc:	This method casts a ray with the start point being this
			camera and the endpoint being the pixel sample indicated 
			in the arguments
	Rtrn:	None
-------------------------------------------------------------------*/
Ray Camera::generateRay(Sample sample, vec3 eye, int w, int h)
{
	float alpha = (float) (tan(fovx / 2) * (sample.getX() - float(w)/2.0f) / (float(w)/2.0f));
	float beta = (float) (tan(fovy / 2) * (float(h)/2.0f - sample.getY()) / (float(h)/2.0f));
	vec3 dirn = normalize(alpha * this->up + beta * this->v - this->w);

	return Ray(eye, dirn);
}
