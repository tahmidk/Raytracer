/*==================================================================
	File:	[main.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the main function and logic. The 
			Raytracer program starts and ends with this file
==================================================================*/

// Standard imports
#include "pch.h"
#include <iostream>

// FreeImage library
#include "FreeImage.h"

// Project file imports
#include "Raytracer.h"
#include "Parser.h"
#include "Scene.h"
#include "Triangle.h"

using namespace std;
using namespace glm;

// Note: scn is declared as a Scene* and it's accessible in external files
Scene * scn;

int main(int argc, char *argv[])
{
	// Argument validity check
	if (argc != 2)
		cerr << "Unexpected number of arguments!" << endl;

    // This is a test to make sure FreeImage is working
	cout << "FreeImage_" << FreeImage_GetVersion() << endl;
	cout << FreeImage_GetCopyrightMessage() << endl;

	// Read in and parse input file
	const char * input_file = argv[1];
	Parser parser(input_file);

	// Initialize environment
	scn = new Scene();
	parser.initScene(scn);
	Camera cam(scn->getCamPos(), scn->getLookAt(), scn->getUpVector(), 
		scn->getFovy(), scn->getWidth(), scn->getHeight());

	// Begin Raytracing/render process
	scn->render(cam, scn->getPath());

	// Clean up
	delete scn;
}
