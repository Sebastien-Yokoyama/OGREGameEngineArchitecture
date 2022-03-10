// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: GameMgr.cpp
/* FILE DESCRIPTION: Contains the implementation of the GameMgr Class. */

#include "GameMgr.h"
#include "Engine.h"	// Forward Reference in Header
#include "GfxMgr.h"	// Gain access to mSceneMgr

#include <OgrePlane.h>	// Ogre::Plane Object
#include <OgreMeshManager.h>	// Ogre::MeshManager Object
#include <OgreEntity.h>	// Ogre::Entity Object

#include <string>
#include <iostream>	// Test Output

// Constructor
GameMgr::GameMgr(Engine *engine) : Mgr(engine){
	std::cout << "GameMgr Constructor" << std::endl;

	cameraNode = nullptr;

	camStep = 10;
}


// Destructor
GameMgr::~GameMgr(){}


/* Init Method
 * Does nothing */
void GameMgr::Init(){
	std::cout << "GameMgr Init Method" << std::endl;
}


/* LoadLevel Method
 * Scene Setup: Sky, Ground, Lighting, Shadows */
void GameMgr::LoadLevel(){
	std::cout << "GameMgr LoadLevel Method" << std::endl;

	// Create surface plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
				"ocean",
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				plane, 10000, 10000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ocean");
	engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Ocean2_Cg");

	// Create sky
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	// Setup lighting and shadows
	engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	light->setPosition(0, 200, 500);

	// Setup camera node
	cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	cameraNode->setPosition(0, 200, 800);
	cameraNode->attachObject(engine->gfxMgr->mCamera);

	camPos = cameraNode->getPosition();
}


/* Tick Method
 * Update camera */
void GameMgr::Tick(float dt){
	cameraNode->setPosition(camPos);
}


/* Stop Method
 * Does nothing */
void GameMgr::Stop(){
	std::cout << "GameMgr Stop Method" << std::endl;
}


/* updateCamera Method
 *  */
