#ifndef H_Light
#define H_Light

// Standard library imports
#include <glm/glm.hpp>

// Project file imports
#include "HitInfo.h"

using namespace glm;
using namespace std;

class Light {
public:
	Light() {}
	Light(Color col, vec3 posn);

	// Utility virtual function to implement in children class
	virtual Color calculate_shading(HitInfo * hit_info, vec3 eye, double * attenuation) { return COLORS::blue; };
	virtual vec3 get_towards_dirn(vec3 from) { return vec3(); };
	virtual float get_tmax(vec3 from) { return 0.0f; };

	// Getter methods
	Color get_color();
	vec3 get_posn();

protected:
	Color color;
	vec3 posn;

	// Helper method for light subclasses
	Color compute_lighting(vec3 dirn, vec3 half, double * attenuation, HitInfo * hit_info);
};

#endif