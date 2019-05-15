#include "Simon.h"
#include "MemTest.h"

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
	for (int i = 0; i <= 3; i++)
		m_circle.push_back(DBG_NEW Circle);


	m_circle[0]->Set(1, 0, 0, 'r', -105, -105);		// red circle
	m_circle[1]->Set(0, 1, 0, 'g', 105, -105);		// green circle
	m_circle[2]->Set(0, 0, 1, 'b', 105, 105);		// blue circle
	m_circle[3]->Set(1, 1, 0, 'y', -105, 105);		// yellow circle

	// Configure the State Machine for the colour selections.
	m_pattern				= DBG_NEW Colour_Pattern;
	m_game_state			= New_Pattern_State;
	m_current_chain_link	= nullptr;
	m_score					= 0;
	m_mouse_lock			= false;
}

// This is called by Bootstrap and manages the game state among other things.
void Simon::Update(aie::Input * a_input, float a_m_widthH, float a_hightH)
{
	// Store the mouse coordinates for use later.
	int mouse_x = a_input->getMouseX();
	int mouse_y = a_input->getMouseY();

	// Unlock the mouse if the left button is up.
	if (a_input->isMouseButtonUp(aie::INPUT_MOUSE_BUTTON_LEFT))
		m_mouse_lock = false;

	// If the mouse is hovering over one of the coloured circles then highlight it.
	for (int i = 0; i <= 3; ++i)
	{
		if (Calculate_Distance(mouse_x, mouse_y, a_m_widthH - m_circle[i]->x, a_hightH - m_circle[i]->y) <= 100)
			m_circle[i]->mouse_over = true;
		else
			m_circle[i]->mouse_over = false;
	}

	// NEW PATTERN STATE: Generate a new colour patten and add it to the Link List.
	if (m_game_state == New_Pattern_State)
	{
		m_score++;
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
		if (m_current_chain_link == nullptr) 
			m_current_chain_link = m_pattern->Get_Head();
	}

	// FLASHING STATE: Flash through each colour in the m_pattern sequence (stored as a Link List).
	if (m_alarm01 > 0)
		m_alarm01 --;
	else
	{
		if (m_game_state == Flashing_State) {
			m_alarm01 = 0;
			if (m_current_chain_link->next != nullptr)
			{
				m_current_chain_link = m_current_chain_link->next;
				m_alarm01 = 100;
			}
			else
			{
				m_game_state = User_Input_State;
				m_current_chain_link = m_pattern->Get_Head();
			}
		}
	}

	// USER INPUT STATE: Check user input against the colour m_pattern held by the Link List.
	if (m_game_state == User_Input_State)
	{
		for (int i = 0; i <= 3; ++i)
		{
			if (m_circle[i]->mouse_over && a_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && !m_mouse_lock)
			{
				m_mouse_lock = true;
				
				if (m_circle[i]->colour == m_current_chain_link->colour)
				{
					m_current_chain_link = m_current_chain_link->next;
					if (m_current_chain_link == nullptr)
					{
						m_game_state = Pause_State;
						m_alarm02 = 100;
						m_current_chain_link = m_pattern->Get_Head();
					}
				}
				else
					m_game_state = Lose_State;
			}
		}

	}

	// PAUSE STATE: Create a short pause between the players correct input and the initiation of a new m_pattern sequence.
	if (m_game_state == Pause_State)
	{
		if (m_alarm02 > 0)
			m_alarm02--;
		else
			m_game_state = New_Pattern_State;
	}

	// LOSE STATE: Set a short timer so the player has time to read the message that they lost then restart the game.
	if (m_game_state == Lose_State)
	{
		m_game_state = Restart_State;
		m_alarm03 = 200;
	}

	// RESTART STATE: Create a short pause before restarting the game.
	if (m_game_state == Restart_State && m_alarm03 > 0)
		m_alarm03--;
}

void Simon::Draw(Hash_Table * a_hashtable, aie::Renderer2D * a_renderer, aie::Font * a_font, int a_widthH, int a_heightH)
{

	// Draw the background textures based on the hashtable.
	a_renderer->drawSprite(a_hashtable->Get("simon"), a_widthH, a_heightH, 0, 0, 0, .15, .5, .5);
	a_renderer->drawSprite(a_hashtable->Get("board"), a_widthH, a_heightH, 0, 0, 0, .1, .5, .5);

	// Draw the four circles on Simon.
	float temp_r = 0.0f, temp_g = 0.0f, temp_b = 0.0f;
	for (int i = 0; i <= 3; ++i)
	{
		// Draw the black shadow behind the circle.
		a_renderer->setRenderColour(0, 0, 0, 1);

		// Draw the black border around the coloured circle. If the circle is currently flashing then make its border thicker.
		if (m_alarm01 > 20)
		{
			if (m_current_chain_link->colour == m_circle[i]->colour)
				a_renderer->drawCircle(a_widthH - m_circle[i]->x, a_heightH - m_circle[i]->y, 115, 0);
			else
				a_renderer->drawCircle(a_widthH - m_circle[i]->x, a_heightH - m_circle[i]->y, 105, 0);
		}
		else
			a_renderer->drawCircle(a_widthH - m_circle[i]->x, a_heightH - m_circle[i]->y, 105, 0);

		// Draw the coloured circle. If the mouse is over the circle or the circle is currently flashing then brighten it's contents.
		if (m_circle[i]->mouse_over == false)
		{
			if (m_alarm01 > 20)
			{
				if (m_current_chain_link->colour == m_circle[i]->colour)
					a_renderer->setRenderColour(m_circle[i]->r, m_circle[i]->g, m_circle[i]->b, 1);
				else
					a_renderer->setRenderColour(m_circle[i]->r - .6, m_circle[i]->g - .6, m_circle[i]->b - .6, 1);
			}
			else
				a_renderer->setRenderColour(m_circle[i]->r - .6, m_circle[i]->g - .6, m_circle[i]->b - .6, 1);
		}
		else
		{
			a_renderer->setRenderColour(m_circle[i]->r, m_circle[i]->g, m_circle[i]->b, 1);
		}
		a_renderer->drawCircle(a_widthH-m_circle[i]->x, a_heightH-m_circle[i]->y, 100, 0);
	}

	// Draw a "red circle" above the texture green dot.
	// This indicates that Simon is displaying a new colour m_pattern and the player is unable to enter input.
	if (m_alarm01 > 20)
	{
		a_renderer->setRenderColour(1, 0, 0, 1);
		a_renderer->drawCircle(a_widthH + 14, a_heightH - 19, 4, 0);
	}

	// Set the rendering colour to BLACK for all text printed after this point.
	a_renderer->setRenderColour(0, 0, 0, 1);

	// PAUSE STATE: Inform the user how long they have before the next m_pattern is presented.
	if (m_game_state == Pause_State)
	{
		snprintf(m_str, 4, "%i", m_alarm02);
		a_renderer->drawText(a_font, "Next", 260, 290);
		a_renderer->drawText(a_font, "Pattern:", 260, 255);
		a_renderer->drawText(a_font, m_str, 260, 220);
	}

	// RESTART STATE: Inform the user that they've lost the game and activate a restart.
	if (m_game_state == Restart_State)
	{
		a_renderer->drawText(a_font, "Wrong!", 260, 290);
		a_renderer->drawText(a_font, "Game will", 260, 255);
		a_renderer->drawText(a_font, "restart.", 260, 220);
	}

	// Draw the current m_score.
	if (m_score > 1)
	{
		snprintf(m_str, 4, "%i", m_score-1);
		a_renderer->drawText(a_font, "Score:", 100, 290);
		a_renderer->drawText(a_font, m_str, 100, 255);
	}
}

bool Simon::Restart_Required()
{
	return m_game_state == Restart_State && m_alarm03 == 0;
}

// Add a new colour to the Link List.
void Simon::Add_Colour(char a_colour)
{
	m_pattern->Push_New_Colour(a_colour);
	m_game_state = Flashing_State;
	m_alarm01 = 100;
}

Simon::~Simon()
{
	delete m_pattern;
	for (int i = 0; i <= 3; i++)
		delete m_circle[i];
}