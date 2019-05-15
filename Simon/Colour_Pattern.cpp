#include "Colour_Pattern.h"
#include "MemTest.h"

Colour_Pattern::Colour_Pattern()
{
	m_head	= nullptr;
	m_current = nullptr;
	m_size	= 0;
}


Colour_Pattern::~Colour_Pattern()
{
	if (m_head != nullptr)
	{
		m_current = m_head;
		m_next_current = m_head;

		while (m_next_current != nullptr)
		{
			m_current = m_next_current;
			m_next_current = m_current->next;
			if (m_current != nullptr)
				delete m_current;
		}
	}
}

Link * Colour_Pattern::Get_Head()
{
	return m_head;
}

int Colour_Pattern::Get_Size()
{
	return m_size;
}

void Colour_Pattern::Push_New_Colour(char a_colour)
{
	// If adding a Link to an empty chain add it to the head otherwise add it to the tail.
	if (m_head == nullptr)
	{
		m_head = new Link;
		m_current = m_head;
		m_head->colour = a_colour;
	}
	else
	{
		m_current = m_head;
		m_next_current = m_head;

		while (m_next_current != nullptr)
		{
			m_current = m_next_current;
			m_next_current = m_current->next;
		}
		m_current->next = DBG_NEW Link;
		m_current->next->colour = a_colour;
	}
	m_size++;
}
