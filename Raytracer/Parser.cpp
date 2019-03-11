/*==================================================================
	File:	[Raytracer.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file contains the code to parse a given input file
			and is responsible for initializing the top-level scene
==================================================================*/

#include "pch.h"
#include "Parser.h"

Parser::~Parser()
{
}

/*-------------------------------------------------------------------
	Func:	Constructor: [Parser]
	Args:	filename - the name of the file to parse
	Desc:	Constructor that initializes all relevant instance fields
	Rtrn:	None
-------------------------------------------------------------------*/
Parser::Parser(const char* fname) : filename(fname) {}

/*-------------------------------------------------------------------
	Func:	[initScene]
	Args:	None
	Desc:	Initializes a new scene based on the input file
	Rtrn:	The new scene described by .test file
-------------------------------------------------------------------*/
void Parser::initScene(Scene * scene) {
	parseFile(scene);
}

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

/*-------------------------------------------------------------------
	Func:	[parserFile]
	Args:	scene - the scene reference to initialize while parsing
	Desc:	Parses the file and extracts meaningful information and
			uses it to initialize the given scene pointer
	Rtrn:	None
-------------------------------------------------------------------*/
void Parser::parseFile(Scene * scene) {
	string str, cmd;
	ifstream in;
	in.open(this->filename);
	if (in.is_open()) {
		Color diffuse;
		Color emission;
		Color specular;
		double shininess = 0.0;
		
		stack <mat4> transfstack;
		int vertCount = 0;
		int objCount = 0;
		int lightCount = 0;
		transfstack.push(mat4(1.0));  // identity

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {

				stringstream s(str);
				s >> cmd;
				float values[10]; // Position and color for light, colors for others
				bool validinput; // Validity of input
				scene->ambient = Color(0.2, 0.2, 0.2);
				scene->diffuse = Color(0.0, 0.0, 0.0);
				scene->emission = Color(0.0, 0.0, 0.0);
				scene->specular = Color(0.0, 0.0, 0.0);
				// Process the light, add it to database.
				// Lighting Command
				if (cmd == "ambient") {
					validinput = readvals(s, 3, values); // colors
					if (validinput) {
						scene->ambient = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						scene->diffuse = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						scene->specular = Color(values[0], values[1], values[2]);

					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						scene->emission = Color(values[0], values[1], values[2]);
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						scene->shininess = values[0];
					}
				}
				else if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						scene->w = (int)values[0]; 
						scene->h = (int)values[1];
					}
				}
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values); // 10 values eye cen up fov
					if (validinput) {
						scene->camPos = vec3(values[0], values[1], values[2]);
						scene->lookAt = vec3(values[3], values[4], values[5]);
						scene->up = vec3(values[6], values[7], values[8]);
						scene->fovy = values[9];

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
						scene->vertices = vector<vec3>(maxverts);
					}

				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					vec3 newVert = vec3(values[0], values[1], values[2]);
					scene->vertices[vertCount++] = newVert;
				}
				else if (cmd == "tri") {
					//read input
					validinput = readvals(s, 3, values);
					if (validinput) {
						vec4 v1 = vec4(scene->vertices[(int)values[0]], 1);
						vec4 v2 = vec4(scene->vertices[(int)values[1]], 1);
						vec4 v3 = vec4(scene->vertices[(int)values[2]], 1);
						vec3 vert1 = vec3(transfstack.top() * v1);
						vec3 vert2 = vec3(transfstack.top() * v2);
						vec3 vert3 = vec3(transfstack.top() * v3);

						// Create new triangle
						Material obj_mat(scene->diffuse, scene->ambient, scene->emission, scene->specular, scene->shininess);
						scene->objects[objCount++] = new Triangle(obj_mat, transfstack.top(), 
							vert1, vert2, vert3);
						scene->num_objects = objCount;
					}
				} else if (cmd == "attenuation") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (int i = 0; i < 3; i++) {
							scene->attenuation[i] = values[i];
						}
					}
				}
				else if (cmd == "sphere") {
					//read input
					validinput = readvals(s, 4, values);
					if (validinput) {
						vec3 center = vec3(values[0], values[1], values[2]);
						double radius = values[3];

						// Create new sphere
						Material obj_mat(scene->diffuse, scene->ambient, scene->emission, scene->specular, scene->shininess);
						scene->objects[objCount++] = new Sphere(obj_mat, transfstack.top(), 
							(float) center.x, (float) center.y, (float) center.z, (float) radius);
						scene->num_objects = objCount;
					}
				}
				else if (cmd == "point") {
					//read input
					validinput = readvals(s, 3, values);
					if (validinput) {
						vec3 posn = vec3(transfstack.top() * vec4(values[0], values[1], values[2], 1));
						Color col = Color(values[3], values[4], values[5]);

						// Create the new point light
						scene->lights[lightCount++] = new PointLight(col, posn);
						scene->num_lights = lightCount;
					}
				}
				else if (cmd == "directional") {
					//read input
					validinput = readvals(s, 3, values);
					if (validinput) {
						vec3 dirn = vec3(transfstack.top() * vec4(values[0], values[1], values[2], 1));
						Color col = Color(values[3], values[4], values[5]);

						// Create the new point light
						scene->lights[lightCount++] = new DirectionalLight(col, dirn);
						scene->num_lights = lightCount;
					}
				}
				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}
	}
	else {
		cerr << "Unable to Open Input Data File " << this->filename << "\n";
		throw 2;
	}
}
