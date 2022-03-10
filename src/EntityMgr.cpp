// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: EntityMgr.cpp
/* FILE DESCRIPTION: Contains the implementation of the EntityMgr Class. */

#include "EntityMgr.h"
#include "Engine.h"	// Forward Reference in Header

#include <iostream>	// Test Output

// Constructor
EntityMgr::EntityMgr(Engine *engine) : Mgr(engine){
	std::cout << "EntityMgr Constructor" << std::endl;

	selectedEntity = nullptr;
	selectedEntityIndex = 0;
}


// Destructor
EntityMgr::~EntityMgr(){}


/* Init Method
 * Do nothing. */
void EntityMgr::Init(){
	std::cout << "EntityMgr Init Method" << std::endl;
}


/* LoadLevel Method
 * Create entities */
void EntityMgr::LoadLevel(){
	std::cout << "EntityMgr LoadLevel Method" << std::endl;

	// Create ships
	for(int i = 1; i < 6; i++){
		CreateEntityFromTypeAndPosition((EntityType)i, Ogre::Vector3((250 * (i - 1)), 0, 0));

		// Increase scale of Cigarette-V2 and TUG because they're so small
		if(i == 2){ entities[i - 1]->ogreSceneNode->scale(3, 3, 3); }
		if(i == 5){ entities[i - 1]->ogreSceneNode->scale(1.5, 1.5, 1.5); }
	}

	// Create Airplanes
	for(int i = 0; i < 5; i++){
		CreateEntityFromTypeAndPosition(PolyPlaneEntity, Ogre::Vector3((250 * i), 100, 0));
	}
}


/* Tick Method
 * Calls the Entity381::Tick Method for all Entity381 instances in the entities vector. */
void EntityMgr::Tick(float dt){
	for(std::vector<Entity381*>::const_iterator entPtr = entities.begin(); entPtr != entities.end(); entPtr++){
		(*entPtr)->Tick(dt);
	}
}


/* Stop Method
 * Does nothing */
void EntityMgr::Stop(){
	std::cout << "EntityMgr Stop Method" << std::endl;
}


/* CreateEntityFromTypeAndPosition
 * Expects EntityType value and an Ogre::Vector3 value
 * Depending on the EntityType value, an Entity381 will be created at the position of the Ogre::Vector3 value.
 * After creating the Entity381, it will be stored in the entities vector of the class.
 * The function returns the Entity381 that was created. */
Entity381* EntityMgr::CreateEntityFromTypeAndPosition(EntityType entype, Ogre::Vector3 pos){
	Entity381* entPtr;

	// Check entityType and proceed accordingly
	switch(entype){
	case CUBEEntity:
		entPtr = new Cube(engine, pos, entities.size());
		break;
	case CG47Entity:
		entPtr = new CG47(engine, pos, entities.size());
		break;
	case CIGARETTEV2Entity:
		entPtr = new CigaretteV2(engine, pos, entities.size());
		break;
	case CVN75Entity:
		entPtr = new CVN75(engine, pos, entities.size());
		break;
	case DDG51V2Entity:
		entPtr = new DDG51V2(engine, pos, entities.size());
		break;
	case TUGEntity:
		entPtr = new TUG(engine, pos, entities.size());
		break;
	case PolyPlaneEntity:
		entPtr = new PolyPlane(engine, pos, entities.size());
		break;
	default:
		entPtr = new Cube(engine, pos, entities.size());
		break;
	}

	// Store Entity381
	entities.push_back(entPtr);

	return entPtr;
}


/* SelectNextEntity Method
 * Selects the next entity in the entities vector.
 * If current selected entity is the last in the vector, go back to the front of the vector. */
void EntityMgr::SelectNextEntity(){
	if(entities.size() > 0){
		if(this->selectedEntity == nullptr){ selectedEntityIndex = 0; }
		else{
			this->selectedEntity->isSelected = false;
			selectedEntityIndex = (selectedEntityIndex >= entities.size() - 1 ? 0 : selectedEntityIndex + 1);
		}

		this->selectedEntity = entities[selectedEntityIndex];
		this->selectedEntity->isSelected = true;
	}
	else{ std::cerr << "Create a game entity first." << std::endl; }
}
