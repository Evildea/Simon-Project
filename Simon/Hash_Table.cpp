#include "Hash_Table.h"

int Hash_Table::Set(char a_string[50], Texture * a_texture)
{
	int value = 0;
	for (int i = 0; i < 50; i++)
		value += a_string[i];

	value = value % capacity;
	m_table[value] = a_texture;
	return value;
}

Texture * Hash_Table::Get(char a_string[50])
{
	int value = 0;
	for (int i = 0; i < 50; i++)
		value += a_string[i];

	value = value % capacity;

	return m_table[value];
}
