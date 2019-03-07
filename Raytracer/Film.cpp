#include "pch.h"
#include "Film.h"


Film::Film()
{
	//set the initial pixel output to black.
	pixel = vector<vector<Color>>(scn->getHeight(), 
		vector<Color>(scn->getWidth(), Color(0.0, 0.0, 0.0)));
}

//writeImage function based on http://graphics.stanford.edu/courses/cs148-10-summer/docs/UsingFreeImage.pdf
void Film::writeImage(string path) {
	int bits = 24;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(scn->getWidth(), scn->getHeight(), bits);
	RGBQUAD color;
	//check if we can allocate bitmap
	if (!bitmap)
		exit(1);
	//set the corresponding color values (0-255) to the output variable
	for (int i = 0; i < scn->getWidth(); i++) {
		vector<Color> col = pixel[i];
		for (int j = 0; j < scn->getHeight(); j++) {
			color.rgbRed = col[j].getRed() * 255;
			color.rgbGreen = col[j].getGreen() * 255;
			color.rgbBlue = col[j].getBlue() * 255;
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}
	//save the file to the specified path with .png format
	FreeImage_Save(FIF_PNG, bitmap, path.c_str(), 0);
}

void Film::commit(Sampler& sample, Color& col) {
	this->pixel[sample.getX()][sample.getY()] = this->pixel[sample.getX()][sample.getY()] + col;
}
