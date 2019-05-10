#include "Controller.h"
#include "Application.h"

void Controller::Update(aie::Input * a_input, aie::Application * a_app)
{
	if(m_current_screen != Start_Game) {
		// If player selects "down" on the "Start Game" option move to the End Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_DOWN) && !m_keylock && m_selected_option == Start_Game)
		{
			m_selected_option = End_Game;
			m_keylock = true;
		}

		// If player selects "up" on the "End Game" option move to the Start Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_UP) && !m_keylock && m_selected_option == End_Game)
		{
			m_selected_option = Start_Game;
			m_keylock = true;
		}

		// Uplock the keyboard input once all keys are up.
		if (m_keylock == true && a_input->isKeyUp(aie::INPUT_KEY_UP) && a_input->isKeyUp(aie::INPUT_KEY_DOWN))
			m_keylock = false;

		// If player selects "Start Game" begin the Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_ENTER) && m_selected_option == Start_Game)
			m_current_screen = Start_Game;

		// If player selects "Exit Game" to end the Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_ENTER) && m_selected_option == End_Game)
			a_app->quit();

	}

}

Selection Controller::Get_State()
{
	return m_selected_option;
}

void Controller::Draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_m_widthH, float a_m_heightH)
{
	if (m_current_screen != Start_Game)
	{
		if (Get_State() == Start_Game)
			a_renderer->setRenderColour(255, 0, 0, 1);
		else
			a_renderer->setRenderColour(255, 255, 255, 1);
		a_renderer->drawText(a_font, "Start Game", a_m_widthH - 85, a_m_heightH + 25);

		if (Get_State() == End_Game)
			a_renderer->setRenderColour(255, 0, 0, 1);
		else
			a_renderer->setRenderColour(255, 255, 255, 1);
		a_renderer->drawText(a_font, "Exit Game", a_m_widthH - 78, a_m_heightH - 25);
	}
}

void Controller::Restart_Controller()
{
	m_selected_option		= Start_Game;
	m_current_screen		= Start_Screen;
	m_keylock				= false;
}

Selection Controller::Get_Current_Screen()
{
	return m_current_screen;
}
