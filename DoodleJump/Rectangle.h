#pragma once

struct Rectangle // Rectangle collision box for GameObjects
{
	float x, y;
	int width, height;

	Rectangle() = default;

	Rectangle(float x_, float y_, int width_, int height_)
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
	}


	
	
};