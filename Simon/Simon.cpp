#include "Simon.h"

// Calculates the distance between two points. Used for mouse collision checking.
float Simon::calculateDistance(int a_xPos, int a_yPos, int a_xPos2, int a_yPos2)
{
	double x_diff = a_xPos - a_xPos2;
	double y_diff = a_yPos - a_yPos2;
	return std::sqrt(x_diff*x_diff + y_diff * y_diff);
}

Simon::Simon()
{
	// Setup the four Triangles to be drawn onto Simon:
	circle[0].Set(1, 0, 0, -105, -105);	// red circle
	circle[1].Set(0, 1, 0, 105, -105);	// green circle
	circle[2].Set(0, 0, 1, 105, 105);	// blue circle
	circle[3].Set(1, 1, 0, -105, 105);	// yellow circle

}

Simon::~Simon()
{
}

void Simon::update(aie::Input * a_input, float a_widthH, float a_hightH)
{
	
	// Get the mouse coordinates.
	int mouse_x = a_input->getMouseX();
	int mouse_y = a_input->getMouseY();

	// Check if the mouse is currently hovering over one of the coloured circles. If it is, then update that circle.
	for (int i = 0; i <= 3; ++i)
	{
		if (calculateDistance(mouse_x, mouse_y, a_widthH - circle[i].x, a_hightH - circle[i].y) <= 100)
			circle[i].mouse_over = true;
		else
			circle[i].mouse_over = false;
	}

	// Randomly generate another colour and assign it to the end of the colour pattern.
	//if (new_pattern == true)
	//{
	//	new_pattern = false;
	//	countdown = .5;

	//	//switch (rand() % 3)
	//	//{
	//	//case 0:
	//	//	colour_pattern.Add('r');
	//	//	break;
	//	//case 1:
	//	//	colour_pattern.Add('g');
	//	//	break;
	//	//case 2:
	//	//	colour_pattern.Add('b');
	//	//	break;
	//	//case 3:
	//	//	colour_pattern.Add('y');
	//	//	break;
	//	//}
	//}

	// The countdown clock is used by the flashing colours of the colour pattern.
	if (countdown > .1)
		countdown -= .01;
	else
		countdown = 0;

}

void Simon::draw(aie::Renderer2D * a_renderer, float a_widthH, float a_heightH)
{

	// Draw the shadow behind the main board.
	a_renderer->setRenderColour(.8, .8, .8, 1);
	a_renderer->drawBox(a_widthH + 5, a_heightH - 5, a_widthH / .699, a_heightH / .699, 0, .3);

	// Draw the main board.
	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawBox(a_widthH, a_heightH, a_widthH / .7, a_heightH / .7, 0,.2);

	// Draw the base of Simon.
	a_renderer->setRenderColour(.7, .6, .4, 1);
	a_renderer->drawCircle(a_widthH, a_heightH, a_widthH / 3, .1);

	// Draw the four triangles of Simon.
	int temp_r, temp_g, temp_b;
	for (int i = 0; i <= 3; ++i)
	{

		// Draw the black shadow behind the circle.
		a_renderer->setRenderColour(0, 0, 0, 1);
		a_renderer->drawCircle(a_widthH - circle[i].x, a_heightH - circle[i].y, 102, 0);

		// Draw the coloured circle. If the mouse is over the circle brighten it's contents.
		if (circle[i].mouse_over == false)
		{
			temp_r = (circle[i].r - .3 > 0) ? circle[i].r : (circle[i].r - .3);
			temp_g = (circle[i].g - .3 > 0) ? circle[i].g : (circle[i].g - .3);
			temp_b = (circle[i].b - .3 > 0) ? circle[i].b : (circle[i].b - .3);
			a_renderer->setRenderColour(temp_r, temp_g, temp_b, 1);
		}
		else
			a_renderer->setRenderColour(circle[i].r, circle[i].g, circle[i].b, 1);
		a_renderer->drawCircle(a_widthH-circle[i].x, a_heightH-circle[i].y, 100, 0);
	}
	
}
