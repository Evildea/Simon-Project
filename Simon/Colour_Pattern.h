#pragma once
#include <iostream>

// This represents an individual link in the colour pattern Link List.
struct Link
{
	char colour = 'x';		// The colour of this specific link in the Link List. 'x' represents no value.
	Link * next = nullptr;	// The next colour link in the Link List.
};

// This is the Link List which manages the colour pattern Link List.
class Colour_Pattern
{
private:
	Link * m_head;			// First link in the Link List.
	Link * m_current;		// Temporary pointer used when looping through the Link List.
	Link * m_next_current;	// Temporary pointer used when looping through the Link List.
	int m_size;				// The current number of links in the Link List.

public:

	Colour_Pattern();
	~Colour_Pattern();

	// This returns the first link in the Link List.
	Link * Get_Head();

	// This returns the current number of the links in the Link List.
	int Get_Size();

	// This pushes a new colour to the tail of the Link List.
	void Push_New_Colour(char a_colour);

};

