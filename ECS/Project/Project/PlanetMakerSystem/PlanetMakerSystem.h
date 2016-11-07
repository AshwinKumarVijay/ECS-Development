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

struct PlanetRingEntity
{
	float rotation;
	long int ringEntity;
	long int subRingEntity;
};

struct PlanetEntity
{
	long int planet;
	
	float planetaryRotation;
	long int planetaryBody;

	std::vector<PlanetRingEntity> planetRings;
};


class PlanetMakerSystem : public System
{

public:

	//	Default PlanetMakerSystem Constructor.
	PlanetMakerSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Default PlanetMakerSystem Destructor.
	virtual ~PlanetMakerSystem();

	//	Initialize the System.
	virtual void initializeSystem();

	//	Create a new planet and add it to the current list of planets.
	virtual long int createPlanet();

	//	Create a new planet, based on the provided specifications.
	//	virtual long int createPlanet(PlanetCreationBlueprints newPlanetCreationBlueprint);

	//	Update the System.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();


private:
	
	//	Process the Events.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Planets.
	std::vector<PlanetEntity> planets;

};

