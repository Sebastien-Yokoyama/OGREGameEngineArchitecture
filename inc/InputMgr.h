// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: InputMgr.h
/* FILE DESCRIPTION: Contains the definition of the InputMgr Class that inherits from the Mgr Class. */

#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include "Mgr.h"	// Inherits from Mgr Class
#include "GfxMgr.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


// Engine Class Forward Reference
class Engine;

// InputMgr Class
class InputMgr : public Mgr, public OIS::KeyListener, public OIS::MouseListener{

public:
	// Constructor
	InputMgr(Engine *engine);

	// Destructor
	~InputMgr();

	// Members
	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

	// Members for Continuous Buffered Input
	bool wDown, aDown, sDown, dDown, eDown, fDown;
	bool lShiftDown;
	bool upDown, downDown, leftDown, rightDown;

	// Methods
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mb);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mb);
};


#endif	// #ifndef INPUT_MGR_H
