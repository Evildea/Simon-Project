#include "SimonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <iostream>

SimonApp::SimonApp() {

}

SimonApp::~SimonApp() {

}

bool SimonApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	widthH = (this->getWindowWidth() / 2);
	heightH = (this->getWindowHeight() / 2);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// Generate the Game Controller
	controller = new Controller;

	return true;
}

void SimonApp::shutdown() {

	delete controller;
	delete m_font;
	delete m_2dRenderer;
}

void SimonApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// This updates the "Start Screen" and "High Score" options if not in "Start Game" mode.
	controller->update(input);

	// This generates "Simon" if we have entered "Start Game" mode and "Simon" hasn't been generated already.
	if (controller->getCurrentScreen() == Start_Game && simon == nullptr)
		simon = new Simon;

	// This person the "Simon" updates.
	if (simon != nullptr)
		simon->update(input, widthH, heightH);

	// This exits the application.
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void SimonApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// This draws the "Start Screen" and "High Score" modes.
	controller->draw(m_2dRenderer, m_font, widthH, heightH);

	// This draws "Simon".
	if (simon != nullptr)
		simon->draw(m_2dRenderer, m_font, widthH, heightH);
	
	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(255, 255, 255, 1);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}