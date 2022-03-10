// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: GfxMgr.h
/* FILE DESCRIPTION: Contains the definition of the GfxMgr Class that inherits from the Mgr Class. */

#ifndef GFX_MGR_H
#define GFX_MGR_H

#include "Mgr.h"	// Inherits from Mgr Class

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

// Engine Class Forward Reference
class Engine;

// GfxMgr Class
class GfxMgr : public Mgr, public Ogre::WindowEventListener, public Ogre::FrameListener{

public:
	// Constructor
	GfxMgr(Engine *engine);

	// Destructor
	~GfxMgr();

	// Members
	Ogre::Root* mRoot;	// Ogre::Root Object
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	// Methods
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
};


#endif	// #ifndef GFX_MGR_H
