/*==================================================================
	File:	[variables.h]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This is the basic include file for the global variables 
			in the program. Since all files need access to it, we 
			define EXTERN as either blank or extern, depending on 
			if included in the main program or not.
==================================================================*/

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif
#include <windows.h>
#include <glm/glm.hpp>

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN glm::vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN glm::vec3 up;  // The (regularly updated) vector coordinates of the up 

#ifdef MAINPROGRAM 
glm::vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
glm::vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
glm::vec3 center(0.0,0.0,0.0) ; // Center look at point 
int amountinit = 5;
int w = 500, h = 500 ; // width and height 
float fovy = 90.0 ; // For field of view
#else 
EXTERN glm::vec3 eyeinit ; 
EXTERN glm::vec3 upinit ; 
EXTERN glm::vec3 center ; 
EXTERN int amountinit;
EXTERN int w, h ; 
EXTERN float fovy ; 
#endif 

EXTERN bool useGlu; // Toggle use of "official" opengl/glm transform vs user 
EXTERN unsigned int vertexshader, fragmentshader, shaderprogram ; // shaders
EXTERN glm::mat4 projection, modelview; // The mvp matrices
EXTERN unsigned int projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot} ;
EXTERN float sx, sy ; // the scale in x and y 
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ; 
EXTERN float lightposn [4*numLights] ; // Light Positions
EXTERN float lightcolor[4*numLights] ; // Light Colors
EXTERN float lightransf[4*numLights] ; // Lights transformed by modelview
EXTERN int numused ;                     // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[4] ; 
EXTERN float diffuse[4] ; 
EXTERN float specular[4] ; 
EXTERN float emission[4] ; 
EXTERN float shininess ; 

// For multiple objects, read from a file.  
const int maxobjects = 10 ; 
EXTERN int numobjects ; 
/*
EXTERN struct object {
  shape type ; 
  float size ;
  float ambient[4] ; 
  float diffuse[4] ; 
  float specular[4] ;
  float emission[4] ; 
  float shininess ;
  glm::mat4 transform ; 
} objects[maxobjects] ;
*/

// Variables to set uniform params for lighting fragment shader 
EXTERN unsigned int lightcol ; 
EXTERN unsigned int lightpos ; 
EXTERN unsigned int numusedcol ; 
EXTERN unsigned int enablelighting ; 
EXTERN unsigned int ambientcol ; 
EXTERN unsigned int diffusecol ; 
EXTERN unsigned int specularcol ; 
EXTERN unsigned int emissioncol ; 
EXTERN unsigned int shininesscol ; 

