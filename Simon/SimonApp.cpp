#include "SimonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

SimonApp::SimonApp() {
	m_simon = nullptr;
}

SimonApp::~SimonApp() {
}

bool SimonApp::startup() {
	
	m_2dRenderer	= DBG_NEW aie::Renderer2D();
	m_widthH		= (this->getWindowWidth() / 2);
	m_heightH		= (this->getWindowHeight() / 2);

	// This generates the controller that controls the start screen.
	m_controller = DBG_NEW Controller;

	// Generate the Hashtable that stores the texture and font IDs.
	m_hashtable = DBG_NEW Hash_Table;

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = DBG_NEW aie::Font("./bin/font/consolas.ttf", 32);

	//m_simon_texture = 
		m_hashtable->Set("simon", DBG_NEW aie::Texture("./bin/textures/Simon_BackGround.png"));
	//m_background_texture = 
		m_hashtable->Set("board", DBG_NEW aie::Texture("./bin/textures/Background.png"));

	return true;
}

void SimonApp::shutdown() {

	delete m_controller;
	delete m_font;
	delete m_2dRenderer;
	delete m_hashtable->Get("simon");
	delete m_hashtable->Get("board");
	delete m_hashtable;
	delete m_simon;
}

void SimonApp::update(float deltaTime) {

	// This represents the keyboard and mouse input.
	input = aie::Input::getInstance();

	// This updates the "start screen" and "end game" options.
	m_controller->Update(input, this);

	// This generates "Simon" if we have entered "Start Game" mode and "Simon" hasn't been generated already.
	if (m_controller->Get_Current_Screen() == Start_Game && m_simon == nullptr)
		m_simon = DBG_NEW Simon;

	// This performs updates for "Simon" and also checks whether "Simon" needs to restart.
	if (m_simon != nullptr)
	{
		m_simon->Update(input, m_widthH, m_heightH);
		if (m_simon->Restart_Required() == true)
		{
			delete m_simon;
			m_simon = nullptr;
			m_controller->Restart_Controller();
		}
	}

	// This exits the game.
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		delete m_simon;
		m_simon = nullptr;
		quit();
	}
}

void SimonApp::draw() {
	// If game over isn't active then draw the contents of the screen.
	if (!m_gameOver)
	{

		// This wipes the screen to the background colour.
		clearScreen();

		// This begins to draw the back buffer.
		m_2dRenderer->begin();

		// This draws the "Start Screen" and "End Game" modes.
		m_controller->Draw(m_2dRenderer, m_font, m_widthH, m_heightH);

		// This draws the object "Simon".
		if (m_simon != nullptr)
			m_simon->Draw(m_hashtable,m_2dRenderer, m_font, m_widthH, m_heightH);

		// This outputs the text Press ESC to the screen.
		m_2dRenderer->setRenderColour(255, 255, 255, 1);
		m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

		// This end the back buffer.
		m_2dRenderer->end();

	}
}
