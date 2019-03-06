/*==================================================================
	File:	[main.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the main function and logic. The 
			Raytracer program starts and ends with this file
==================================================================*/

#include "pch.h"	  
#include <iostream>	  
#include "FreeImage.h"

#include "readfile.h"
#include "variables.h"

using namespace std;

int main()
{
    // This is a test to make sure FreeImage is working
	FreeImage_Initialise();
	cout << "FreeImage_" << FreeImage_GetVersion() << endl;
	cout << FreeImage_GetCopyrightMessage() << endl;
	FreeImage_DeInitialise();
}
