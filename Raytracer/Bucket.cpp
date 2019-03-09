/*==================================================================
	File:	[Bucket.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	A Bucket represents a list of colors in a single pixel
			When a pixel is rendered to the physical file, this 
			structure "mixes" the colors in it by taking an average
==================================================================*/

#include "pch.h"
#include "Bucket.h"

/*-------------------------------------------------------------------
	Func:	[addColor]
	Args:	col - the color to add
	Desc:	Adds a given color to the bucket
	Rtrn:	None
-------------------------------------------------------------------*/
void Bucket::addColor(Color col)
{
	this->colors.push_back(col);
}

/*-------------------------------------------------------------------
	Func:	[computeAverage]
	Args:	None
	Desc:	Mixes the colors in this bucket by taking the average of
			their RGB values and returning the mixed/averaged color
	Rtrn:	The average color
-------------------------------------------------------------------*/
Color Bucket::computeAverage()
{
	if (this->colors.size() == 0)
		return Color(0.0f, 0.0f, 0.0f);

	Color sum = Color(0.0f, 0.0f, 0.0f);
	for (Color col: this->colors)
		sum = sum + col;
	
	return (sum / this->colors.size());
}
