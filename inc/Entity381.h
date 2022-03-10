// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: Entity381.h
/* FILE DESCRIPTION: Contains the definition of an Entity381 Class and its various Subclasses. */

#ifndef ENTITY381_H
#define ENTITY381_H

#include <OgreVector3.h>	// Ogre::Vector3 Class
#include <OgreSceneNode.h>	// Ogre::SceneNode Class
#include <OgreEntity.h>	// Ogre::Entity Class

#include <list>
#include <string>


// Enum for entity type
enum EntityType{
	CUBEEntity = 0,
	CG47Entity = 1,
	CIGARETTEV2Entity = 2,
	CVN75Entity = 3,
	DDG51V2Entity = 4,
	TUGEntity = 5,
	PolyPlaneEntity = 6
};


// Aspect Class Forward Reference
class Aspect;

// Engine Class Forward Reference
class Engine;


// Entity381 Class
class Entity381{

public:
	// Constructor
	Entity381(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	virtual ~Entity381();

	// Members
	Engine* engine;

	long int entityId;
	std::string meshFilename;
	std::string materialName;
	EntityType entityType;
	std::string entityName;

	float minSpeed;
	float maxSpeed;
	float speed;
	float desiredSpeed;
	float acceleration;

	float heading;
	float desiredHeading;
	float turningRate;

	Ogre::Vector3 velocity;
	Ogre::Vector3 position;

	bool isSelected;

	Ogre::SceneNode* ogreSceneNode;
	Ogre::Entity* ogreEntity;

	std::list<Aspect*> aspects;

	// Methods
	void Tick(float dt);
};


// Cube Subclass
class Cube : public Entity381{

public:
	// Constructor
	Cube(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~Cube();
};


// CG47 Subclass
class CG47 : public Entity381{

public:
	// Constructor
	CG47(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~CG47();
};


// CIGARETTE-V2 Subclass
class CigaretteV2 : public Entity381{

public:
	// Constructor
	CigaretteV2(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~CigaretteV2();
};


// CVN75 Subclass
class CVN75 : public Entity381{

public:
	// Constructor
	CVN75(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~CVN75();
};


// DDG51V2 Subclass
class DDG51V2 : public Entity381{

public:
	// Constructor
	DDG51V2(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~DDG51V2();
};


// TUG Subclass
class TUG : public Entity381{

public:
	// Constructor
	TUG(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~TUG();
};


// PolyPlane Subclass
class PolyPlane : public Entity381{

public:
	// Constructor
	PolyPlane(Engine *engine, Ogre::Vector3 pos, int ident);

	// Destructor
	~PolyPlane();
};


#endif	// #ifndef ENTITY381_H
