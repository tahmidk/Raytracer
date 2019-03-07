/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the code to parse a given input file
			and is responsible for initializing the top-level scene
==================================================================*/

#include "pch.h"
#include "Parser.h"

/*-------------------------------------------------------------------
	Func:	Constructor: [Parser]
	Args:	filename - the name of the file to parse
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Parser::Parser(const char* fname) : filename(fname) {}

/*------------[ Helper Methods ]------------*/
bool readvals(stringstream &s, const int numvals, float* values)
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

void matransform(stack<mat4> &transfstack, float* values)
{
	mat4 transform = transfstack.top();
	vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
	vec4 newval = transform * valvec;
	for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top();
	T = T * M;
}

void Parser::parseFile() {
	string str, cmd;
	ifstream in;
	in.open(this->filename);
	if (in.is_open()) {

		
		stack <mat4> transfstack;
		int vertCount = 0;
		transfstack.push(mat4(1.0));  // identity

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {

				stringstream s(str);
				s >> cmd;
				float values[10]; // Position and color for light, colors for others
				bool validinput; // Validity of input
				ambient = Color(0.2, 0.2, 0.2);
				diffuse = Color(0.0, 0.0, 0.0);
				emission = Color(0.0, 0.0, 0.0);
				specular = Color(0.0, 0.0, 0.0);
				// Process the light, add it to database.
				// Lighting Command
				if (cmd == "ambient") {
					validinput = readvals(s, 3, values); // colors
					if (validinput) {
						ambient = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						diffuse = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						specular = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						emission = Color(values[0], values[1], values[2]);
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
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values); // 10 values eye cen up fov
					if (validinput) {
						eyeinit = vec3(values[0], values[1], values[2]);
						center = vec3(values[3], values[4], values[5]);
						up = vec3(values[6], values[7], values[8]);
						fovy = values[9];
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
				else if (cmd == "maxverts") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						int maxverts = (int)values[0];
					}
					vertices = vector<vec3>(maxverts);
				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					vec3 newVert = vec3(values[0], values[1], values[2]);
					vertices[vertCount++] = newVert;
				}
				else if (cmd == "tri") {

				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}
}
