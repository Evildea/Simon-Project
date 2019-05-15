#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Controller.h"
#include "Simon.h"
#include "Hash_Table.h"
#include "MemTest.h"

class SimonApp : public aie::Application {
public:

	SimonApp();
	virtual ~SimonApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Input*			input;
	aie::Renderer2D*	m_2dRenderer;			// This is the renderer used for the Back Buffer.
	aie::Font*			m_font;					// This is the font used by the renderer.
	Controller*			m_controller;			// This is the controller for the Start game screen.
	Simon*				m_simon;				// This is the object that represents the Simon game.
	Hash_Table*			m_hashtable;			// This represents the texture hashtable.	
	float				m_widthH;				// This represents the width of the screen divided in two.
	float				m_heightH;				// This represents the height of the screen divided in two.

};