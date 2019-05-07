#include "Colour_Pattern.h"

Colour_Pattern::Colour_Pattern()
{
	head = nullptr;
	current = nullptr;
	size = 0;
}


Colour_Pattern::~Colour_Pattern()
{
	if (head != nullptr)
	{
		current = head;
		next_current = head;

		while (next_current != nullptr)
		{
			next_current = current->next;
			current = next_current;
			delete current;
		}
	}
}

Link * Colour_Pattern::Get_Head()
{
	return head;
}

int Colour_Pattern::Get_Size()
{
	return size;
}

void Colour_Pattern::Pust_New_Colour(char a_colour)
{
	// If adding a Link to an empty chain add it to the head otherwise add it to the tail.
	if (head == nullptr)
	{
		head = new Link;
		current = head;
		head->colour = a_colour;
	}
	else
	{
		current = head;
		next_current = head;

		while (next_current != nullptr)
		{
			current = next_current;
			next_current = current->next;
		}
		current->next = new Link;
		current->next->colour = a_colour;
	}
	size++;
}
