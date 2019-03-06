#pragma once

class Point
{
	public:
		Point(float x, float y, float z);

		// Getter methods
		float get_x();
		float get_y();
		float get_z();

	protected:
		float x;
		float y;
		float z;
};

