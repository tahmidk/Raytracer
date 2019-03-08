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

using namespace std;
using namespace glm;

Scene * scn;

int main(int argc, char *argv[])
{
	// Argument validity check
	if (argc != 2)
		cerr << "Unexpected number of arguments!" << endl;

    // This is a test to make sure FreeImage is working
	FreeImage_Initialise();
	cout << "FreeImage_" << FreeImage_GetVersion() << endl;
	cout << FreeImage_GetCopyrightMessage() << endl;

	// Read in and parse input file
	const char * input_file = argv[1];
	Parser parser(input_file);
	//note that scn is declared as a Scene* and it's accessible in external files
	scn = new Scene();
	parser.initScene(scn);

	// Begin Raytracing

	// Render all pixels to image via FreeImage

	// Clean up
	FreeImage_DeInitialise();
	//delete scene;
}
