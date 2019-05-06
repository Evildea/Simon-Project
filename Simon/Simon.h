#pragma once
#include "Renderer2D.h"
#include "Input.h"
#include <cmath>

#include <iostream>

struct Circle
{
	float r, g, b;
	int x, y;
	bool mouse_over = false;
	bool selected = false;
	void Set(float a_red, float a_green, float a_blue, int a_xPos, int a_yPos)
	{
		r = a_red;
		g = a_green;
		b = a_blue;
		x = a_xPos;
		y = a_yPos;
	}
};

class Simon
{
private:
	// Generate four circles that the player will click on to play the game.
	Circle circle[3];

	// Calculates the distance between two points. Used for mouse collision checking.
	float calculateDistance(int a_xPos, int a_yPos, int a_xPos2, int a_yPos2);

	// Setup the State Machine for the colour selections.
	bool new_pattern = true;
	float countdown = 0;

public:
	Simon();
	~Simon();

	void update(aie::Input * a_input, float a_widthH, float a_hightH);
	void draw(aie::Renderer2D * a_renderer, float a_widthH, float a_hightH);
};

