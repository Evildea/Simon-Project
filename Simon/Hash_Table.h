#pragma once
#include "Texture.h"

using namespace std;
using namespace aie;

class Hash_Table
{
private:
	int capacity = 50;
	Texture * m_table[50];

public:

	int Set(char a_string[50], Texture * a_texture)
	{
		int value = 0;
		for (int i = 0; i < 50; i++)
			value += a_string[i];

		value = value % capacity;
		m_table[value] = a_texture;
		return value;
	}

	Texture * Get(char a_string[50])
	{
		int value = 0;
		for (int i = 0; i < 50; i++)
			value += a_string[i];

		value = value % capacity;

		return m_table[value];
	}

};

