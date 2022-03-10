// NAME: Sebastien Yokoyama
// EMAIL: syokoyama2001@nevada.unr.edu
// COURSE: CS 381.1001
// ASSIGNMENT: as4
// FILE NAME: Aspect.h
/* FILE DESCRIPTION: Contains the definition of the Aspect Class and its Subclasses. */

#ifndef ASPECT_H
#define ASPECT_H

// Entity381 Class Forward Reference
class Entity381;


// Aspect Class
class Aspect{

public:
	// Constructor
	Aspect(Entity381* newEntity381);

	// Destructor
	virtual ~Aspect();

	// Members
	Entity381* entity381;

	// Methods
	virtual void Tick(float dt);
};


// Physics2D Subclass
class Physics2D : public Aspect{

public:
	// Constructor
	Physics2D(Entity381* newEntity381);

	// Destructor
	~Physics2D();

	// Methods
	void Tick(float dt);
	float clamp(float lo, float hi, float v);
};


// Renderable Subclass
class Renderable : public Aspect{

public:
	// Constructor
	Renderable(Entity381* newEntity381);

	// Destructor
	~Renderable();

	// Methods
	void Tick(float dt);
};


#endif	// #ifndef ASPECT_H
