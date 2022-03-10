// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: EntityMgr.h
/* FILE DESCRIPTION: Contains the definition of the EntityMgr Class that inherits from the Mgr Class. */

#ifndef ENTITY_MGR_H
#define ENTITY_MGR_H

#include "Mgr.h"	// Inherits from Mgr Class
#include "Entity381.h"

// Engine Class Forward Reference
class Engine;

// EntityMgr Class
class EntityMgr : public Mgr{

public:
	// Constructor
	EntityMgr(Engine *engine);

	// Destructor
	~EntityMgr();

	// Members
	std::vector<Entity381*> entities;
	Entity381* selectedEntity;
	long int selectedEntityIndex;

	// Methods
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	Entity381* CreateEntityFromTypeAndPosition(EntityType entype, Ogre::Vector3 pos);

	void SelectNextEntity();
};

#endif	// #ifndef ENTITY_MGR_H
