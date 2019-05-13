#pragma once
#include "Texture.h"

using namespace std;
using namespace aie;


struct Key
{
	int key;
	Texture * data;
};

class Hash_Table
{
private:
	int capacity;
	int size = 0;
	Key * m_table = new Key[capacity];

public:
	Hash_Table(int a_capacity) : capacity(a_capacity) {};

	int Set(char a_string[50], Texture * a_texture)
	{
		size++;
		int value = 0;
		for (int i = 0; i < 50; i++)
			value += a_string[i];

		m_table[size].data = a_texture;
		m_table[size].key = value;
		return value;
	}

	Texture * Get(int a_key)
	{
		for (int i = 0; i <= size; i++)
		{
			if (a_key == m_table[i].key)
				return m_table[i].data;
		}
	}

};

