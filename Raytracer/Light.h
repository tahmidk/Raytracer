#ifndef H_Light
#define H_Light

#include <glm/glm.hpp>
#include "Color.h"

using namespace glm;

class Light {
public:
	Light() {}
	Light(Color col, vec3 posn);

	virtual Color calculate_shading() { return Color(); };

	// Getter methods
	Color getColor();
	vec3 getPosn();

protected:
	Color color;
	vec3 posn;
};

#endif