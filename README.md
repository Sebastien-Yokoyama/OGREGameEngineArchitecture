#OgreGameEngineArchitecture

Contains my implementation of a video game engine architecture using OGRE as a framework.
The game engine is composed of four different components: GfxMgr, InputMgr, GameMgr, and EntityMgr.

The GfxMgr is responsible for graphics rendering and creating the application window.
The InputMgr is responsible for capturing and handling user input through the mouse and keyboard. Joystick support is available in the Ogre Library.
The GameMgr handles the in-game camera as well as the game environment (skybox, ground plane, other static entities).
The EntityMgr manages entities that have special properties. In this implementation, the special entity is known as 'Entity381' to distinguish it from Ogre::Entity.

The Entity381 Object stores an Ogre::Entity Object and an Ogre::SceneNode Object and contains additional attributes and functionality.
The additional attributes contained in Entity381 are represented as 'Aspects', which handle different parts of an entity.
The 2 main aspects are 'Physics2D' and 'Renderable'.
The Physics2D Aspect handles the 2D physics of an object, such as calculating velocity and position.
The Renderable Aspect updates the Entity381's Ogre::SceneNode member, such as updating its position or updating the rendering of the Axis-Aligned Bounding Box (AABB).
