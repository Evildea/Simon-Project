#pragma once
#include <iostream>

// This represents a individual links in the colour pattern Link List.
struct Link
{
	char colour = 'x';		// The colour of this link in the Link List. 'x' represents no value.
	Link * next = nullptr;	// The next link in the Link List.
};

// This is the manager of the colour pattern Link List.
class Colour_Pattern
{
private:
	Link * head;			// First Link in the Link List.
	Link * current;			// Temporary pointer used when looping through the Link List.
	Link * next_current;	// Temporary pointer used when looping through the Link List.
	int size;				// The current number of links in the Link List.

public:

	Colour_Pattern();
	~Colour_Pattern();

	// Return the first link in the Link List.
	Link * Get_Head();

	// Return the current number of links in the Link List.
	int Get_Size();

	// Push a new colour to the tail of the Link List.
	void Pust_New_Colour(char a_colour);

};

