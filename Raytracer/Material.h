#ifndef H_Material
#define H_Material

#include "Color.h"

class Material
{
// Public fields
public:
	Material();
	Material(Color diffuse, Color emission, Color specular, double shininess);

	// Getter methods
	Color get_diffuse();
	Color get_emission();
	Color get_specular();
	double get_shininess();

// Private fields
private:
	Color diffuse;
	Color emission;
	Color specular;
	double shininess;
};

#endif // !H_Material

