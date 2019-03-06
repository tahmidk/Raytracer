#ifndef H_Light
#define H_Light

#include "Color.h"
#include "Point.h"

class Light {
protected:
	Color color;
	Point posn;

public:
	Light() {}
	Light(Color col, Point posn);

	virtual Color calculate_shading() { return Color(); };

};

#endif