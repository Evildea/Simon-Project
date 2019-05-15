#pragma once
#include <cmath>
#include "Input.h"
#include "Renderer2D.h"
#include "Colour_Pattern.h"
#include "Hash_Table.h"
#include "Circle.h"
#include <vector>

// State Machine that represents the various states the game can be in.
enum Game_State {New_Pattern_State,Flashing_State,User_Input_State,Pause_State,Lose_State,Restart_State};

class Simon
{
private:
	// Generate four circles that the player will click on to play the game.
	Game_State		m_game_state;			// This represents the current game state.
	Colour_Pattern	*m_pattern;				// This represents the colour pattern. It's holds a Link List.
	Link			*m_current_chain_link;	// This represents the current link in the Link List. It's used by the "Flashing" and "User Input" game states.
	vector<Circle*> m_circle;				// This represents the four coloured circles.
	short int		m_alarm01;				// This represents the timer used by the "Flashing" state to create a delay between the colours.
	short int		m_alarm02;				// This represents the timer used by the "Pause" state to create a delay between the user winning and the next pattern sequence.
	short int		m_alarm03;				// This represents the timer used by the "Lose" state to create a delay before restarting the game.
	short int		m_score;				// This represents the total score achieved.
	bool			m_mouse_lock;			// This represents mouse locking to stop multiple input.
	char			m_str[20];				// This represents a temporary string used for drawing.

	// Calculates the distance between two points. Used for mouse collision checking with the coloured circles.
	float Calculate_Distance(int a_xPos, int a_yPos, int a_xPos2, int a_yPos2);

	// Add a new colour to the Link List.
	void Add_Colour(char a_colour);

public:
	Simon();
	~Simon();

	// This is called by Bootstrap and manages the game state among other things.
	void Update(aie::Input * a_input, float a_m_widthH, float a_hightH);

	// This is called by Bootstrap and manages the back buffer.
	void Draw(Hash_Table * a_hashtable, aie::Renderer2D * a_renderer, aie::Font * a_font, int a_widthH, int a_heightH);

	// This returns whether the game is ready to be restarted.
	bool Restart_Required();

};

