// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: GfxMgr.cpp
/* FILE DESCRIPTION: Contains the implementation of the GfxMgr Class. */

#include "GfxMgr.h"
#include "Engine.h"	// Forward Reference in Header

#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>

#include <iostream>	// Test Output

// Constructor
GfxMgr::GfxMgr(Engine *engine) : Mgr(engine){
	std::cout << "GfxMgr Constructor" << std::endl;

	mRoot = nullptr;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg = Ogre::StringUtil::BLANK;

	mWindow = nullptr;
	mSceneMgr = nullptr;
	mCamera = nullptr;
}


// Destructor
GfxMgr::~GfxMgr(){
	std::cout << "GfxMgr Destructor" << std::endl;

	// Remove ourself as a Window Listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	// Shutdown and delete Root Object
	Stop();
	delete mRoot;
}


/* Init Method
 * Creates and stores an Ogre::Root Object
 * Creates and stores an Ogre::SceneManager Object
 * Creates and stores an Ogre::RenderWindow Object
 * Creates and stores an Ogre::Camera Object
 * Creates a Window Listener */
void GfxMgr::Init(){
	std::cout << "GfxMgr Init Method" << std::endl;


	// Create Ogre::Root Object
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);


	// Set up Resources
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while(secIt.hasMoreElements()){
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for(it = settings->begin(); it != settings->end(); it++){
			locType = it->first;
			name = it->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}


	// Configure the RenderSystem and Create Ogre::RenderWindow Object
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog())){ return; }

	mWindow = mRoot->initialise(true, "CS381 as4");


	// Initialize Resources
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


	// Create the Ogre::SceneManager Object
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);


	// Create the Ogre::Camera Object and set it up
	mCamera = mSceneMgr->createCamera("MainCam");

	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);


	// Add a viewport
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));


	// Set initial mouse clipping size
	windowResized(mWindow);


	// Register as a Window Listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}


/* LoadLevel Method
 * Does nothing */
void GfxMgr::LoadLevel(){
	std::cout << "GfxMgr LoadLevel Method" << std::endl;
}


/* Tick Method
 * Renders One Frame
 * Does a Message Pump */
void GfxMgr::Tick(float dt){
	Ogre::WindowEventUtilities::messagePump();

	if(mWindow->isClosed()){ return; }

	if(!mRoot->renderOneFrame(dt)){ return; }
}


/* Stop Method
 * Shutdown the Root Object.
 * End program. */
void GfxMgr::Stop(){
	std::cout << "GfxMgr Stop Method" << std::endl;

	mRoot->shutdown();
	engine->keepRunning = false;
}


/* frameRenderingQueued Method */
bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe){
	if(mWindow->isClosed()){ return false; }

	return true;
}
