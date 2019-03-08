/*==================================================================
	File:	[Film.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	This file represents the film where all output colors
			will be stored and eventually rendered as a physical
			PNG file
==================================================================*/

#include "pch.h"
#include "Film.h"

Film::Film() {

}

Film::Film(int width, int height)
{
	this->width = width;
	this->height = height;
	//set the initial pixel output to black.
	pixel = std::vector<std::vector<Bucket>>((int) height, 
		std::vector<Bucket>((int) width, Bucket()));
}

/*-------------------------------------------------------------------
	Func:	[writeImage]
	Args:	path - the path/filename of the file to write
	Desc:	Renders the actual PNG image. [writeImage] function based on 
			http://graphics.stanford.edu/courses/cs148-10-summer/docs/UsingFreeImage.pdf
	Rtrn:	None
-------------------------------------------------------------------*/
void Film::writeImage(std::string path) {
	int bits = 24;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate((int) width, (int) height, bits);
	RGBQUAD color;
	//check if we can allocate bitmap
	if (!bitmap) {
		exit(1);
	}

	//set the corresponding color values (0-255) to the output variable
	for (int i = 0; i < height; i++) {
		std::vector<Bucket> col = pixel[i];
		for (int j = 0; j < width; j++) {
			color.rgbRed = (BYTE) (col[j].computeAverage().getRed() * 255);
			color.rgbGreen = (BYTE) (col[j].computeAverage().getGreen() * 255);
			color.rgbBlue = (BYTE) (col[j].computeAverage().getBlue() * 255);
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}
	//save the file to the specified path with .png format
	FreeImage_Save(FIF_PNG, bitmap, path.c_str(), 0);
}

void Film::commit(Sample& sample, Color& col) {
	this->pixel[sample.getX()][sample.getY()].addColor(col);
}
