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

using namespace std;

int main()
{
    // This is a test to make sure FreeImage is working
	FreeImage_Initialise();
	cout << "FreeImage_" << FreeImage_GetVersion() << endl;
	cout << FreeImage_GetCopyrightMessage() << endl;
	FreeImage_DeInitialise();

	// Read in and parse input file

	// Begin Raytracing

	// Render all pixels to image via FreeImage

}
