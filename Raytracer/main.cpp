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
#include <iomanip>
#include <chrono>

// FreeImage library
#include "FreeImage.h"

// Project file imports
#include "Raytracer.h"
#include "Parser.h"
#include "Scene.h"
#include "Triangle.h"

using namespace std;
using namespace glm;

/*-----[ Acceleration switch ]-----*/
const bool ACCELERATE = true;

Scene * scn;

int main(int argc, char *argv[])
{
	// Argument validity check
	if (argc != 2)
		cerr << "Unexpected number of arguments!" << endl;

    // This is a test to make sure FreeImage is working
	cerr << "FreeImage_" << FreeImage_GetVersion() << endl;
	cerr << FreeImage_GetCopyrightMessage() << endl;


	// Read in and parse input file
	const char * input_file = argv[1];
	cerr << "\nParsing \"" << input_file << "\"..." << endl;
	Parser parser(input_file);


	// Initialize environment
	cerr << "Initializing scene..." << endl;
	scn = new Scene();
	parser.initScene(scn);
	Camera cam(scn->getCamPos(), scn->getLookAt(), scn->getUpVector(), 
		scn->getFovy(), scn->getWidth(), scn->getHeight());

	// Begin Raytracing/render and time the process
	auto start = chrono::steady_clock::now();
	scn->render(cam, scn->getPath());
	auto end = chrono::steady_clock::now();

	auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
	cerr << "Elapsed Time: " << fixed << setprecision(2) << (elapsed/60.0f) << " min" << endl;

	// Clean up
	delete scn;
}
