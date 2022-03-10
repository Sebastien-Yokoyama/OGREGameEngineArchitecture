// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: Aspect.cpp
/* FILE DESCRIPTION: Contains the implementation of the Aspect Class and its Subclasses. */

#include "Aspect.h"
#include "Entity381.h"	// Forward Reference in Header

// Aspect Class
// Constructor
Aspect::Aspect(Entity381* newEntity381) : entity381(newEntity381){}

// Destructor
Aspect::~Aspect(){}

/* Tick Method
 * Expects a float value
 * Does nothing, but is overwritten in subclasses. */
void Aspect::Tick(float dt){}


// Physics2D Subclass
// Constructor
Physics2D::Physics2D(Entity381* newEntity381) : Aspect(newEntity381){}

// Destructor
Physics2D::~Physics2D(){}

/* Tick Method
 * Expects a float value
 * Manages the Entity381's desired speed, desired heading, and position. */
void Physics2D::Tick(float dt){
	/* Manage desired speed.
	 * If desired speed is not the actual speed, change the Entity381's speed using the Entity381's acceleration. */
	if(entity381->desiredSpeed > entity381->speed){
		entity381->speed += (entity381->acceleration * dt);
	}
	if(entity381->desiredSpeed < entity381->speed){
		entity381->speed -= (entity381->acceleration * dt);
	}

	// Use clamp operation to set ensure minSpeed < speed < maxSpeed
	entity381->speed = clamp(entity381->minSpeed, entity381->maxSpeed, entity381->speed);


	// Adjust heading
	if(entity381->desiredHeading > entity381->heading){
		// If difference between desired heading and heading is greater than 180, rotate opposite direction
		if((entity381->desiredHeading - entity381->heading) > 180){
			entity381->heading -= entity381->turningRate * dt;
		}
		else{
			entity381->heading += entity381->turningRate * dt;
		}
	}
	else if(entity381->desiredHeading < entity381->heading){
		// If difference between desired heading and heading is greater than 180, rotate opposite direction
		if((entity381->desiredHeading - entity381->heading) < -180){
			entity381->heading += entity381->turningRate * dt;
		}
		else{
			entity381->heading -= entity381->turningRate * dt;
		}
	}

	/* Manage desired heading.
	 * If the desired heading is not the actual heading, change the Entity381's heading using the Entity381's turningRate.
	 * Flip turn direction when difference between desired heading and actual heading is >180
	 * Fix heading angles and desired heading angles between 0-360 */
	// If heading angle is <0, add 360 until within 0-360
	if(entity381->heading < 0){
		while(entity381->heading < 0){
			entity381->heading += 360;
		}
	}
	// If heading angle is >360, subtract 360 until within 0-360
	else if(entity381->heading > 360){
		while(entity381->heading > 360){
			entity381->heading -= 360;
		}
	}
	// If desired heading angle is <0, add 360 until within 0-360
	if(entity381->desiredHeading < 0){
		while(entity381->desiredHeading < 0){
			entity381->desiredHeading += 360;
		}
	}
	// If desired heading angle is >360, subtract 360 until within 0-360
	else if(entity381->desiredHeading > 360){
		while(entity381->desiredHeading > 360){
			entity381->desiredHeading -= 360;
		}
	}


	/* Update velocity.
	 * Since the speed and heading variables may update, we must recalculate the velocity accordingly.
	 * velocity.x = cos(h) * speed, velocity.z = sin(h) * speed, where h is heading (Ogre::Radian value).
	 * Ogre::Math::Cos(Real fValue) can be used in place of cos(h)
	 * Ogre::Math::Sin(Real fValue) can be used in place of sin(h)
	 * Both Ogre::Math Methods return an Ogre::Real value, which is a Software floating point type */
	entity381->velocity.x = Ogre::Math::Cos(Ogre::Degree(entity381->heading)) * entity381->speed;
	entity381->velocity.z = Ogre::Math::Sin(Ogre::Degree(entity381->heading)) * -entity381->speed;


	/* Update position.
	 * Use the formula: (pos = pos + vel * dt)
	 * (pos += vel * dt) */
	entity381->position += (entity381->velocity * dt);
}

float Physics2D::clamp(float lo, float hi, float v){
	if(v < lo){ return lo; }
	else if(v > hi){ return hi; }
	else{ return v; }
}


// Renderable Subclass
// Constructor
Renderable::Renderable(Entity381* newEntity381) : Aspect(newEntity381){}

// Destructor
Renderable::~Renderable(){}

/* Tick Method
 * Expects a float value
 * Adjusts the scene node's position, yaw, and AABB visibility. */
void Renderable::Tick(float dt){
	// Copy the Entity381's position to its SceneNode
	entity381->ogreSceneNode->setPosition(entity381->position);

	// Set the SceneNode's yaw using Entity381's heading
	entity381->ogreSceneNode->resetOrientation();	// Set yaw to 0
	entity381->ogreSceneNode->yaw(Ogre::Degree(entity381->heading));	// Increase yaw by arg

	// Adjust the visibility of the SceneNode's AABB depening on Entity381's selection state
	entity381->ogreSceneNode->showBoundingBox(entity381->isSelected);
}
