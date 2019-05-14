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

	int Set(char a_string[50], Texture * a_texture);

	Texture * Get(char a_string[50]);

};

