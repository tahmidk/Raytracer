#ifndef H_Color
#define H_Color

class Color {
private:
	double r, g, b;
public:
	Color();
	Color(double red, double green, double blue);
	Color operator+(const Color& col2);
	Color operator/(int c);
	double getRed();
	double getGreen();
	double getBlue();
};

#endif