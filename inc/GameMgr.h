// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: GameMgr.h
/* FILE DESCRIPTION: Contains the definition of the GameMgr Class that inherits from the Mgr Class. */

#ifndef GAME_MGR_H
#define GAME_MGR_H

#include "Mgr.h"	// Inherits from Mgr Class

#include <OgreSceneNode.h>	// Ogre::SceneNode* cameraNode

// Engine Class Forward Reference
class Engine;

// GameMgr Class
class GameMgr : public Mgr{

public:
	// Constructor
	GameMgr(Engine *engine);

	// Destructor
	~GameMgr();

	// Members
	Ogre::SceneNode* cameraNode;

	Ogre::Vector3 camPos;
	float camStep;

	// Methods
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();
};

#endif	// #ifndef GAME_MGR_H
