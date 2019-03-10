#ifndef H_Color
#define H_Color

class Color {
private:
	double r, g, b;
public:
	Color();
	Color(double red, double green, double blue);

	// Operator overloads
	Color operator+(const Color& col2);
	Color operator/(float c);
	Color operator*(float c);
	Color operator*(Color other);

	// Getter methods
	double getRed();
	double getGreen();
	double getBlue();
};

// Define common colors for convenience
namespace COLORS {
	const Color black = Color();
	const Color red = Color(1.0f, 0.0f, 0.0f);
	const Color green = Color(0.0f, 1.0f, 0.0f);
	const Color blue = Color(0.0f, 0.0f, 1.0f);
	const Color white  = Color(1.0f, 1.0f, 1.0f);
}

#endif