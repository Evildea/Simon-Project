#include "DynamicLinkedList.h"



DynamicLinkedList::DynamicLinkedList()
{
}


DynamicLinkedList::~DynamicLinkedList()
{
}

void DynamicLinkedList::Add(char a_colour)
{
	// Add a new link to the chain.
	chain[current_fill] = new Chain_Link;

	/*switch (a_colour)
	{
	case 'r':
		chain[current_fill]->SetRed();
		break;
	case 'b':
		chain[current_fill]->SetBlue();
		break;
	case 'g':
		chain[current_fill]->SetGreen();
		break;
	case 'y':
		chain[current_fill]->SetYellow();
		break;
	}*/
	current_fill++;
}
