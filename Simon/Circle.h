#pragma once
class Circle
{
public:
	float r, g, b;
	int x, y;
	char colour;
	bool mouse_over;
	bool selected;

	Circle();
	~Circle();

	void Set(float a_red, float a_green, float a_blue, char a_colour, int a_xPos, int a_yPos);

};

