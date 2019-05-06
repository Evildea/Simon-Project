#pragma once

// This struct represents a link in the chain of the DynamicLinkedList.
struct Chain_Link
{
	bool activate = false;

	bool red = false;
	bool green = false;
	bool blue = false;
	bool yellow = false;

	/*void SetRed()
	{
		if (activate == false) {
			red = true;
			activate = true;
		}
	}

	void SetGreen()
	{
		if (activate == false) {
			green = true;
			activate = true;
		}
	}
	
	void SetBlue()
	{
		if (activate == false) {
			blue = true;
			activate = true;
		}
	}

	void SetYellow()
	{
		if (activate == false) {
			yellow = true;
			activate = true;
		}
	}*/
};

class DynamicLinkedList
{
private:
	Chain_Link * chain[10];
	short int max_chain = 10;
	short int current_fill = 0;

public:
	DynamicLinkedList();
	~DynamicLinkedList();

	// Add a new link to the chain and give it a colour.
	void Add(char a_colour);
};

