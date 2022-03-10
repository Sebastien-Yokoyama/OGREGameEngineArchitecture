// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: InputMgr.cpp
/* FILE DESCRIPTION: Contains the definition of the InputMgr Class. */

#include "InputMgr.h"
#include "Engine.h"	// Forward Reference in Header
#include "GfxMgr.h"	// Get access to mWindow
#include "EntityMgr.h"	// Get access to SelectNextEntity Method
#include "GameMgr.h"	// Get access to camera

#include <OgreRenderWindow.h>	// RederWindow::getMetrics Method

#include <iostream>	// Test Output

// Constructor
InputMgr::InputMgr(Engine *engine) : Mgr(engine){
	std::cout << "InputMgr Constructor" << std::endl;

	mInputManager = nullptr;
	mMouse = nullptr;
	mKeyboard = nullptr;

	wDown = false;
	aDown = false;
	sDown = false;
	dDown = false;
	eDown = false;
	fDown = false;
	lShiftDown = false;
	upDown = false;
	downDown = false;
	leftDown = false;
	rightDown = false;
}


// Destructor
InputMgr::~InputMgr(){}


/* Init Method
 * Creates Keyboard and Mouse Callbacks. */
void InputMgr::Init(){
	// Setup input manager
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	// Create mouse and keyboard objects
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	windowResized(engine->gfxMgr->mWindow);

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

}


/* LoadLevel Method
 * Does nothing */
void InputMgr::LoadLevel(){
	std::cout << "InputMgr LoadLevel Method" << std::endl;
}


/* Tick Method
 * Capture Mouse/Keyboard Input.
 * Handle Mouse/Keyboard Input. */
void InputMgr::Tick(float dt){
	// Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	// Close program when 'Q' is pressed
	if(mKeyboard->isKeyDown(OIS::KC_Q))
		engine->keepRunning = false;
}


/* Stop Method
 * Destroys OIS through the windowClosed Method. */
void InputMgr::Stop(){
	std::cout << "InputMgr Stop Method" << std::endl;

	windowClosed(engine->gfxMgr->mWindow);
}


/* windowResized Method
 * Expects an Ogre::RenderWindow Pointer
 * Adjusts the mouse clipping area. */
void InputMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


/* windowClosed Method
 * Expects an Ogre::RenderWindow Pointer
 * Kills OIS if the given pointer is the same as the engine's gfxMgr's mWindow (Ogre::RenderWindow Pointer)*/
void InputMgr::windowClosed(Ogre::RenderWindow* rw){
	if(rw == engine->gfxMgr->mWindow){
		if(mInputManager){
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}


bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	switch(ke.key){
	case OIS::KC_TAB:
		engine->entityMgr->SelectNextEntity();
		break;
	case OIS::KC_SPACE:
		engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredSpeed = 0;
		engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
		break;
	case OIS::KC_W:
		if(lShiftDown){
			engine->gameMgr->cameraNode->pitch(Ogre::Degree(15));
		}
		else{
			engine->gameMgr->camPos.z -= engine->gameMgr->camStep;
		}

		wDown = true;
		break;
	case OIS::KC_A:
		if(lShiftDown){
			engine->gameMgr->cameraNode->yaw(Ogre::Degree(15));
		}
		else{
			engine->gameMgr->camPos.x -= engine->gameMgr->camStep;
		}

		aDown = true;
		break;
	case OIS::KC_S:
		if(lShiftDown){
			engine->gameMgr->cameraNode->pitch(Ogre::Degree(-15));
		}
		else{
			engine->gameMgr->camPos.z += engine->gameMgr->camStep;
		}

		sDown = true;
		break;
	case OIS::KC_D:
		if(lShiftDown){
			engine->gameMgr->cameraNode->yaw(Ogre::Degree(-15));
		}
		else{
			engine->gameMgr->camPos.x += engine->gameMgr->camStep;
		}

		dDown = true;
		break;
	case OIS::KC_E:
		engine->gameMgr->camPos.y += engine->gameMgr->camStep;

		eDown = true;
		break;
	case OIS::KC_F:
		engine->gameMgr->camPos.y -= engine->gameMgr->camStep;

		fDown = true;
		break;
	case OIS::KC_LSHIFT:
		lShiftDown = true;
		break;
	case OIS::KC_UP:
		engine->entityMgr->selectedEntity->desiredSpeed += engine->entityMgr->selectedEntity->acceleration;

		upDown = true;
		break;
	case OIS::KC_DOWN:
		engine->entityMgr->selectedEntity->desiredSpeed -= engine->entityMgr->selectedEntity->acceleration;

		downDown = true;
		break;
	case OIS::KC_LEFT:
		engine->entityMgr->selectedEntity->desiredHeading += engine->entityMgr->selectedEntity->turningRate;

		leftDown = true;
		break;
	case OIS::KC_RIGHT:
		engine->entityMgr->selectedEntity->desiredHeading -= engine->entityMgr->selectedEntity->turningRate;

		rightDown = true;
		break;
	default:
		break;
	}

	return true;
}


bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	switch(ke.key){
	case OIS::KC_W:
		wDown = false;
		break;
	case OIS::KC_A:
		aDown = false;
		break;
	case OIS::KC_S:
		sDown = false;
		break;
	case OIS::KC_D:
		dDown = false;
		break;
	case OIS::KC_E:
		eDown = false;
		break;
	case OIS::KC_F:
		fDown = false;
		break;
	case OIS::KC_LSHIFT:
		lShiftDown = false;
		break;
	case OIS::KC_UP:
		upDown = false;
		break;
	case OIS::KC_DOWN:
		downDown = false;
		break;
	case OIS::KC_LEFT:
		leftDown = false;
		break;
	case OIS::KC_RIGHT:
		rightDown = false;
		break;
	default:
		break;
	}

	return true;
}


bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}


bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mb){
	return true;
}


bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mb){
	return true;
}
