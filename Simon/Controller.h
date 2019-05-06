#pragma once
#include "Input.h"
#include "Renderer2D.h"
#include "Font.h"
#include "Simon.h"

enum Selection { Start_Screen, Start_Game, High_Score };

class Controller
{
private:
	Selection selected_option = Start_Game;
	Selection current_screen = Start_Screen;
	bool keylock = false;

public:
	void update(aie::Input * a_input);
	void draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_widthH, float a_hightH);
	Selection getCurrentScreen();
	Selection getState();
};

