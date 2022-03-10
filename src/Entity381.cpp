// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: Entity381.cpp
/* FILE DESCRIPTION: Contains the implementation of the Entity381 Class and its Subclasses. */

#include "Entity381.h"
#include "Aspect.h"	// Forward Reference in Header
#include "Engine.h"	// Forward Reference in Header
#include "GfxMgr.h"	// Gain access to mSceneMgr

// Entity381 Class
// Constructor
Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident) : engine(engine), position(pos), entityId(ident) {
	entityType = (EntityType)0;
	ogreSceneNode = 0;
	velocity = Ogre::Vector3::ZERO;

	meshFilename = "";
	materialName = "";

	speed = 0;
	minSpeed = 0;
	maxSpeed = 0;
	desiredSpeed = 0;
	acceleration = 0;

	heading = 0;
	desiredHeading = 0;
	turningRate = 0;

	entityName = "Entity381";

	isSelected = false;

	ogreEntity = nullptr;

	// Initialize Aspects
	Physics2D* physicsAspect = new Physics2D(this);
	Renderable* renderableAspect = new Renderable(this);

	// Store Aspects
	aspects.push_back(physicsAspect);
	aspects.push_back(renderableAspect);
}

// Destructor
Entity381::~Entity381(){}

/* Tick Method
 * Expects a float value
 * Calls the Aspect::Tick Method for all Aspect instances in the aspects list. */
void Entity381::Tick(float dt){
	for(std::list<Aspect*>::iterator it = aspects.begin(); it != aspects.end(); it++){
		(*it)->Tick(dt);
	}
}


// Cube Subclass
// Constructor
Cube::Cube(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	this->acceleration = 100;
	this->meshFilename = "cube.mesh";
	this->entityName = "Cube: " + ident;
	this->materialName = "Examples/RustySteel";
	this->entityType = (EntityType)0;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
Cube::~Cube(){}


// CG47 Subclass
// Constructor
CG47::CG47(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Large ship, so moves and turns slow
	this->maxSpeed = 75;
	this->acceleration = 10;
	this->turningRate = 15;
	this->meshFilename = "cg47.mesh";
	this->materialName = "";
	this->entityName = "CG47: " + ident;
	this->entityType = (EntityType)1;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
CG47::~CG47(){}


// CigaretteV2 Subclass
// Constructor
CigaretteV2::CigaretteV2(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Small ship, so moves and turns fast
	this->maxSpeed = 200;
	this->acceleration = 30;
	this->turningRate = 45;
	this->meshFilename = "cigarette-V2.mesh";
	this->materialName = "";
	this->entityName = "Cigarette-V2: " + ident;
	this->entityType = (EntityType)2;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
CigaretteV2::~CigaretteV2(){}


// CVN75 Subclass
// Constructor
CVN75::CVN75(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Very large ship, so moves and turns very slow (slower than CG47)
	this->maxSpeed = 50;
	this->acceleration = 7.5;
	this->turningRate = 10;
	this->meshFilename = "cvn75.mesh";
	this->materialName = "";
	this->entityName = "CVN75: " + ident;
	this->entityType = (EntityType)3;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
CVN75::~CVN75(){}


// DDG51V2 Subclass
// Constructor
DDG51V2::DDG51V2(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Similar size to CG47
	this->maxSpeed = 75;
	this->acceleration = 10;
	this->turningRate = 15;
	this->meshFilename = "ddg51-v2.mesh";
	this->materialName = "";
	this->entityName = "DDG51-V2: " + ident;
	this->entityType = (EntityType)4;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
DDG51V2::~DDG51V2(){}


// TUG Subclass
// Constructor
TUG::TUG(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Small boat, so moves fast
	this->maxSpeed = 200;
	this->acceleration = 30;
	this->turningRate = 45;
	this->meshFilename = "tug.mesh";
	this->materialName = "";
	this->entityName = "TUG: " + ident;
	this->entityType = (EntityType)5;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
TUG::~TUG(){}


// PolyPlane Subclass
// Constructor
PolyPlane::PolyPlane(Engine *engine, Ogre::Vector3 pos, int ident) : Entity381(engine, pos, ident){
	// Small airplane, so moves fast
	this->maxSpeed = 200;
	this->acceleration = 20;
	this->turningRate = 45;
	this->meshFilename = "PolyPlane.mesh";
	this->materialName = "";
	this->entityName = "PolyPlane: " + ident;
	this->entityType = (EntityType)6;

	this->ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshFilename);
	this->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);

	this->ogreSceneNode->attachObject(ogreEntity);
}

// Destructor
PolyPlane::~PolyPlane(){}
