#pragma once
#include "Renderer2D.h"
#include "Input.h"
#include <cmath>
#include "Colour_Pattern.h"
#include <string>

#include <iostream>

// State Machine that represents the various states the game can be in.
enum Game_State {New_Pattern_State,Flashing_State,User_Input_State,Pause_State,Lose_State};

// Structs that represent each coloured circle that is drawn to the screen.
struct Circle
{
	float r, g, b;
	int x, y;
	char colour;
	bool mouse_over = false;
	bool selected = false;
	void Set(float a_red, float a_green, float a_blue, char a_colour, int a_xPos, int a_yPos)
	{
		r = a_red;
		g = a_green;
		b = a_blue;
		colour = a_colour;
		x = a_xPos;
		y = a_yPos;
	}
};

class Simon
{
private:
	// Generate four circles that the player will click on to play the game.
	Circle * circle = new Circle[3];	// This represents the four coloured circles.
	Game_State game_state;				// This represents the current game state.
	Colour_Pattern * pattern;			// This represents the colour pattern. It's holds a Link List.
	Link * current_chain_link;			// This represents the current link in the Link List. It's used by the "Flashing" and "User Input" game states.
	short int alarm01 = 0;				// This represents the timer used by the "Flashing" state to create a delay between the colours.
	short int alarm02 = 0;				// This represents the timer used by the "Pause" state to create a delay between the user winning and the next pattern sequence.
	short int mouse_clicks = 0;			// This represents the number of mouse clicks made. It's used by the "User Input" state.
	bool mouse_lock = false;
	char str[20];

	// Calculates the distance between two points. Used for mouse collision checking with the coloured circles.
	float Calculate_Distance(int a_xPos, int a_yPos, int a_xPos2, int a_yPos2);

	// Add a new colour to the Link List.
	void Add_Colour(char a_colour);

public:
	Simon();
	~Simon();

	// This is called by Bootstrap and manages the game state among other things.
	void update(aie::Input * a_input, float a_widthH, float a_hightH);

	// This si called by Bootstrap and manages the back buffer.
	void draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_widthH, float a_heightH);

};

