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

/*-----[ Acceleration Options ]-----*/
const bool ACCELERATE = true;	// Acceleration on or off?
const int MAX_NODE_SIZE = 100;	// Change this according to scene's density (100 for scene7, minimum 2)

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
	cout << "\nParsing \"" << input_file << "\"..." << endl;
	Parser parser(input_file);


	// Initialize environment
	cout << "Initializing scene..." << endl;
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
