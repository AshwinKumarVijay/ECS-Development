#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../ECS/System/System.h"

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;

class PlanetMakerSystem;


struct PlanetPositionEntity
{
	//	The Planet Positioning Entity.
	long int planetPositionEntity;

	float rotation;

	//	The Planet Entity.
	long int planetEntity;
};

struct StarSystemEntity
{
	//	The Star System Entity.
	long int starSystemEntity;

	//	The Planets.
	std::vector<PlanetPositionEntity> planets;
};



class StarSystem : public System
{

public:
	
	//	Default StarSystem Constructor.
	StarSystem(std::shared_ptr<PlanetMakerSystem> planetMakerSystem, std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Default StarSystem Destructor.
	virtual ~StarSystem();

	//	Initialize the System.
	virtual void initializeSystem();

	//	Create a new planet and add it to the current list of planets.
	virtual long int createStarSystem();

	//	Update the System.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();


private:

	//	Process the Events.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Star System.
	StarSystemEntity starSystem;

	std::shared_ptr<PlanetMakerSystem> planetMakerSystem;

};

