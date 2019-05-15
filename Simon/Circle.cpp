#include "Circle.h"



Circle::Circle()
{
	mouse_over = false;
	selected = false;
}


Circle::~Circle()
{
}

void Circle::Set(float a_red, float a_green, float a_blue, char a_colour, int a_xPos, int a_yPos)
{
	r = a_red;
	g = a_green;
	b = a_blue;
	colour = a_colour;
	x = a_xPos;
	y = a_yPos;
}
