#include "Controller.h"

void Controller::update(aie::Input * a_input)
{
	if(current_screen != Start_Game) {
		// If player selects "down" on the "Start Game" option move to the High Score.
		if (a_input->isKeyDown(aie::INPUT_KEY_DOWN) && !keylock && selected_option == Start_Game)
		{
			selected_option = High_Score;
			keylock = true;
		}

		// If player selects "up" on the "High Score" option move to the Start Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_UP) && !keylock && selected_option == High_Score)
		{
			selected_option = Start_Game;
			keylock = true;
		}

		// Uplock the keyboard input once all keys are up.
		if (keylock == true && a_input->isKeyUp(aie::INPUT_KEY_UP) && a_input->isKeyUp(aie::INPUT_KEY_DOWN))
			keylock = false;

		// If player selects "Start Game" begin the Game.
		if (a_input->isKeyDown(aie::INPUT_KEY_ENTER) && selected_option == Start_Game)
			current_screen = Start_Game;
	}

}

Selection Controller::getState()
{
	return selected_option;
}

void Controller::draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_widthH, float a_hightH)
{
	if (current_screen != Start_Game)
	{
		if (getState() == Start_Game)
			a_renderer->setRenderColour(255, 0, 0, 1);
		else
			a_renderer->setRenderColour(255, 255, 255, 1);
		a_renderer->drawText(a_font, "Start Game", a_widthH - (5 * 17), a_hightH + 25);

		if (getState() == High_Score)
			a_renderer->setRenderColour(255, 0, 0, 1);
		else
			a_renderer->setRenderColour(255, 255, 255, 1);
		a_renderer->drawText(a_font, "High Score", a_widthH - (5 * 17), a_hightH - 25);
	}
}

Selection Controller::getCurrentScreen()
{
	return current_screen;
}
