#pragma once
#include "Renderer2D.h"
#include "Input.h"
#include "Simon.h"
#include "Font.h"

// This represents the current status of the Start Screen options.
enum Selection { Start_Screen, Start_Game, End_Game };

class Controller
{
private:
	Selection		m_selected_option		= Start_Game;
	Selection		m_current_screen		= Start_Screen;
	bool			m_keylock				= false;

public:
	void Update(aie::Input * a_input, aie::Application * a_app);
	void Draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_m_widthH, float a_m_heightH);

	// This function resets the start screen.
	void Restart_Controller();


	Selection Get_Current_Screen();
	Selection Get_State();
};

