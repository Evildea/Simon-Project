#include "Simon.h"

// Calculates the distance between two points. Used for mouse collision checking with the coloured circles.
float Simon::Calculate_Distance(int a_xPos, int a_yPos, int a_xPos2, int a_yPos2)
{
	double x_diff = a_xPos - a_xPos2;
	double y_diff = a_yPos - a_yPos2;
	return std::sqrt(x_diff*x_diff + y_diff * y_diff);
}

Simon::Simon()
{
	// Configure the settings of the four coloured circles:
	circle[0].Set(1, 0, 0, 'r', -105, -105);	// red circle
	circle[1].Set(0, 1, 0, 'g', 105, -105);		// green circle
	circle[2].Set(0, 0, 1, 'b', 105, 105);		// blue circle
	circle[3].Set(1, 1, 0, 'y', -105, 105);		// yellow circle

	// Configure the State Machine for the colour selections.
	pattern = new Colour_Pattern;
	game_state = New_Pattern_State;
	current_chain_link = nullptr;
}

Simon::~Simon()
{
	delete pattern;
	delete [] circle;
}

// This is called by Bootstrap and manages the game state among other things.
void Simon::update(aie::Input * a_input, float a_widthH, float a_hightH)
{
	// Store the mouse coordinates for use later.
	int mouse_x = a_input->getMouseX();
	int mouse_y = a_input->getMouseY();

	// Unlock the mouse if the left button is up.
	if (a_input->isMouseButtonUp(aie::INPUT_MOUSE_BUTTON_LEFT))
		mouse_lock = false;

	// If the mouse is hovering over one of the coloured circles highlight it.
	for (int i = 0; i <= 3; ++i)
	{
		if (Calculate_Distance(mouse_x, mouse_y, a_widthH - circle[i].x, a_hightH - circle[i].y) <= 100)
			circle[i].mouse_over = true;
		else
			circle[i].mouse_over = false;
	}

	// NEW PATTERN STATE: Generate a new colour patten and add it to the Link List.
	if (game_state==New_Pattern_State)
	{
		switch (rand() % 3)
		{
		case 0:
			Add_Colour('r');
			break;
		case 1:
			Add_Colour('g');
			break;
		case 2:
			Add_Colour('b');
			break;
		case 3:
			Add_Colour('y');
			break;
		}
		if (current_chain_link == nullptr) 
			current_chain_link = pattern->Get_Head();
	}

	// FLASHING STATE: Flash through each colour in the pattern sequence (stored as a Link List).
	if (alarm01 > 0)
		alarm01 --;
	else
	{
		if (game_state == Flashing_State) {
			alarm01 = 0;
			if (current_chain_link->next != nullptr)
			{
				current_chain_link = current_chain_link->next;
				alarm01 = 100;
			}
			else
			{
				mouse_clicks = 0;
				game_state = User_Input_State;
				current_chain_link = pattern->Get_Head();
			}
		}
	}

	// USER INPUT STATE: Check user input against the colour pattern held by the Link List.
	if (game_state == User_Input_State)
	{
		for (int i = 0; i <= 3; ++i)
		{
			if (circle[i].mouse_over)
			{
				if (a_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && mouse_lock == false)
				{
					mouse_lock = true;
					if (circle[i].colour == current_chain_link->colour)
					{
						current_chain_link = current_chain_link->next;
						if (current_chain_link == nullptr)
						{
							std::cout << "good" << std::endl;
							game_state = Pause_State;
							alarm02 = 100;
							current_chain_link = pattern->Get_Head();
						}
						else
							mouse_clicks++;
					}
					else
						mouse_clicks++;
				}
			}
		}

		// If the mouse clicks is equal to the size of the pattern and they still haven't reached the end of the Link List then cause the game to fail.
		if(mouse_clicks==pattern->Get_Size())
		{
			game_state = Lose_State;
			std::cout << "failed" << std::endl;
		}
	}

	// PAUSE STATE: Create a short pause between the players correct input and the initiation of a new pattern sequence.
	if (game_state == Pause_State)
	{
		if (alarm02 > 0)
			alarm02--;
		else
			game_state = New_Pattern_State;
	}
}

void Simon::draw(aie::Renderer2D * a_renderer, aie::Font * a_font, float a_widthH, float a_heightH)
{

	// Draw the shadow behind the main board.
	a_renderer->setRenderColour(.8, .8, .8, 1);
	a_renderer->drawBox(a_widthH + 5, a_heightH - 5, a_widthH / .699, a_heightH / .699, 0, .3);

	// Draw the main board.
	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawBox(a_widthH, a_heightH, a_widthH / .7, a_heightH / .7, 0,.2);

	// Draw the circular base of Simon.
	a_renderer->setRenderColour(.7, .6, .4, 1);
	a_renderer->drawCircle(a_widthH, a_heightH, a_widthH / 3, .1);

	// Draw the four circles on Simon.
	float temp_r = 0.0f;
	float temp_g = 0.0f;
	float temp_b = 0.0f;

	for (int i = 0; i <= 3; ++i)
	{
		// Draw the black shadow behind the circle.
		a_renderer->setRenderColour(0, 0, 0, 1);

		// Draw the black border around the coloured circle. If the circle is currently flashing then make its border thicker.
		if (alarm01 > 20)
		{
			if (current_chain_link->colour == circle[i].colour)
				a_renderer->drawCircle(a_widthH - circle[i].x, a_heightH - circle[i].y, 110, 0);
			else
				a_renderer->drawCircle(a_widthH - circle[i].x, a_heightH - circle[i].y, 105, 0);
		}
		else
			a_renderer->drawCircle(a_widthH - circle[i].x, a_heightH - circle[i].y, 105, 0);

		// Draw the coloured circle. If the mouse is over the circle or the circle is currently flashing then brighten it's contents.
		if (circle[i].mouse_over == false)
		{
			if (alarm01 > 20)
			{
				if (current_chain_link->colour == circle[i].colour)
					a_renderer->setRenderColour(circle[i].r, circle[i].g, circle[i].b, 1);
				else
					a_renderer->setRenderColour(circle[i].r - .6, circle[i].g - .6, circle[i].b - .6, 1);
			}
			else
				a_renderer->setRenderColour(circle[i].r - .6, circle[i].g - .6, circle[i].b - .6, 1);
		}
		else
		{
			a_renderer->setRenderColour(circle[i].r, circle[i].g, circle[i].b, 1);
		}
		a_renderer->drawCircle(a_widthH-circle[i].x, a_heightH-circle[i].y, 100, 0);
	}

	// PAUSE STATE: Inform the user how long they have before the next Patter is presented.
	if (game_state == Pause_State)
	{
		snprintf(str, 20, "Next Pattern: %i", alarm02);
		a_renderer->setRenderColour(0, 0, 0, 1);
		a_renderer->drawText(a_font, str, a_widthH - (9 * 17), a_heightH - 250);
	}

}

// Add a new colour to the Link List.
void Simon::Add_Colour(char a_colour)
{
	pattern->Pust_New_Colour(a_colour);
	game_state = Flashing_State;
	alarm01 = 100;
}
