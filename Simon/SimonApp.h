#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Controller.h"
#include "Simon.h"

class SimonApp : public aie::Application {
public:

	SimonApp();
	virtual ~SimonApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Controller*			controller;
	Simon*				simon = nullptr;
	float widthH;
	float heightH;

};