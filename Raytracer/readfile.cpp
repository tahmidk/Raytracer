/*==================================================================
	File:	[readfile.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file is the parser for the inputs file passed via
			the command line. It will appropriately initialze all
			necessary variables for further use in the program 
			according to the instructions in the input
==================================================================*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <gl/GL.h>
#include "Transform.h"

using namespace std;
#include "variables.h"
#include "readfile.h"


// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, GLfloat* values)
{
	mat4 transform = transfstack.top();
	vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
	vec4 newval = transform * valvec;
	for (int i = 0; i < 4; i++) values[i] = newval[i];
}

/*-------------------------------------------------------------------
	Func:	[rightmultiply]
	Args:	M - the 4x4 transformation matrix to right multiply
			transfstack - the transformation stack
	Desc:	Performs a right multiply 
	Rtrn:	None
-------------------------------------------------------------------*/
void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top();
	T = T * M;
}

/*-------------------------------------------------------------------
	Func:	[readvals]
	Args:	s - a reference to the string instruction to parse
			numvals - the number of values in this instruction to parse
			values - the destination to put parsed values
	Desc:	A helper method used by readfile() method to parse single
			line instructions
	Rtrn:	True upon successful parse
			False otherwise
-------------------------------------------------------------------*/
bool readvals(stringstream &s, const int numvals, GLfloat* values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

/*-------------------------------------------------------------------
	Func:	[readfile]
	Args:	filename - the name of the input file
	Desc:	Parses the commands listed in the given file and appropriately
			initializes all relevant variables declared mostly in file
			'variables.h'
	Rtrn:	None
-------------------------------------------------------------------*/
void readfile(const char* filename)
{
	string str, cmd;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {

		// I need to implement a matrix stack to store transforms.
		// This is done using standard STL Templates
		stack <mat4> transfstack;
		transfstack.push(mat4(1.0));  // identity

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				stringstream s(str);
				s >> cmd;
				int i;
				GLfloat values[10]; // Position and color for light, colors for others
				// Up to 10 params for cameras.
				bool validinput; // Validity of input

				// Lighting command
				if (cmd == "light") {
					if (numused == numLights) { // No more Lights
						cerr << "Reached Maximum Number of Lights " 
							<< numused << " Will ignore further lights\n";
					}
					else {
						validinput = readvals(s, 8, values); // Position/color for lts.
						if (validinput) {
							// Place lights in appropriate positions in the arrays
							for (i = 0; i < 4; i++) {
								lightposn[i + 4 * numused] = values[i];
								lightcolor[i + 4 * numused] = values[i + 4];
							}
							++numused;
						}
					}
				}

				// Material Commands
				else if (cmd == "ambient") {
					validinput = readvals(s, 4, values); // colors
					if (validinput) {
						for (i = 0; i < 4; i++) {
							ambient[i] = values[i];
						}
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							diffuse[i] = values[i];
						}
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							specular[i] = values[i];
						}
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							emission[i] = values[i];
						}
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}
				else if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						w = (int)values[0]; h = (int)values[1];
					}
				}

				// Camera command
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values); // 10 values eye cen up fov
					if (validinput) {
						eyeinit = vec3(values[0], values[1], values[2]);
						center = vec3(values[3], values[4], values[5]);
						upinit = vec3(values[6], values[7], values[8]);
						fovy = values[9];
					}
				}

				// Object commands
				else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
					if (numobjects == maxobjects) { // No more objects
						cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n";
					}
					else {
						validinput = readvals(s, 1, values);
						if (validinput) {
							object * obj = &(objects[numobjects]);
							obj->size = values[0];

							// Set the object's light properties
							for (i = 0; i < 4; i++) {
								(obj->ambient)[i] = ambient[i];
								(obj->diffuse)[i] = diffuse[i];
								(obj->specular)[i] = specular[i];
								(obj->emission)[i] = emission[i];
							}
							obj->shininess = shininess;

							// Set the object's transform
							obj->transform = transfstack.top();

							// Set the object's type
							if (cmd == "sphere") {
								obj->type = sphere;
							}
							else if (cmd == "cube") {
								obj->type = cube;
							}
							else if (cmd == "teapot") {
								obj->type = teapot;
							}
						}
						++numobjects;
					}
				}

				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						float tx = values[0];
						float ty = values[1];
						float tz = values[2];
						mat4 translation = Transform::translate(tx, ty, tz);
						rightmultiply(translation, transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						float sx = values[0];
						float sy = values[1];
						float sz = values[2];
						mat4 scaling = Transform::scale(sx, sy, sz);
						rightmultiply(scaling, transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						vec3 axis = vec3(values[0], values[1], values[2]);
						float degrees = values[3];
						mat3 rotation = Transform::rotate(degrees, axis);
						mat4 converted;
						converted[0] = vec4(rotation[0], 0);
						converted[1] = vec4(rotation[1], 0);
						converted[2] = vec4(rotation[2], 0);
						converted[3] = vec4(0, 0, 0, 1);
						rightmultiply(converted, transfstack);
					}
				}

				// I include the basic push/pop code for matrix stacks
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform") {
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {
						transfstack.pop();
					}
				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}

		// Set up initial position for eye, up and amount and booleans
		eye = eyeinit;
		up = upinit;
		amount = amountinit;
		sx = sy = 1.0;  // keyboard controlled scales in x and y
		tx = ty = 0.0;  // keyboard controllled translation in x and y
		useGlu = false; // don't use the glu perspective/lookat fns

		//glEnable(GL_DEPTH_TEST);
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}
}