#include "StarSystem.h"

#include "glm\glm.hpp"

#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/EntityManager/EntityManager.h"

#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"

#include "../Transform/Transform.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include "../RNGs/RNGs.h"
#include "../PlanetMakerSystem/PlanetMakerSystem.h"

//	Default StarSystem Constructor.
StarSystem::StarSystem(std::shared_ptr<PlanetMakerSystem> newPlanetMakerSystem, std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::STAR_SYSTEM)

{
	planetMakerSystem = newPlanetMakerSystem;

}

//	Default StarSystem Destructor.
StarSystem::~StarSystem()
{


}

//	Initialize the System.
void StarSystem::initializeSystem()
{

}

//	Create a new Star System.
long int StarSystem::createStarSystem()
{
	
	//	Create the Star System.
	starSystem.starSystemEntity = getEntityManager()->createEntity();

	//	Add the Hierarchy and the Transform Components.
	getEntityManager()->addComponentToEntity(starSystem.starSystemEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(starSystem.starSystemEntity, ComponentType::TRANSFORM_COMPONENT);

	//	Get the Star System Hierarchy Component, and the Transform Component.
	std::shared_ptr<HierarchyComponent> starSystemHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(starSystem.starSystemEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::STAR_SYSTEM));
	std::shared_ptr<TransformComponent> starSystemTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(starSystem.starSystemEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::STAR_SYSTEM));

	//	The Planet Count.
	int planetCount = 5;

	float currentDistance = 0.0;

	//	Iterate over the planets.
	for (int i = 0; i < planetCount; i++)
	{
		//	Create the new Planet Positioning Entity.
		PlanetPositionEntity newPlanetPositionEntity;
		newPlanetPositionEntity.rotation = RNGs::doubleRand(0.2, 0.7);
		//	Compute the Distance of the Planet.
		currentDistance = currentDistance + 15.0 + RNGs::doubleRand(1.0, 4.0);

		//	Create the new Planet Position Entity.
		newPlanetPositionEntity.planetPositionEntity = getEntityManager()->createEntity();

		//	Add the Hierarchy and the Transform Components.
		getEntityManager()->addComponentToEntity(newPlanetPositionEntity.planetPositionEntity, ComponentType::HIERARCHY_COMPONENT);
		getEntityManager()->addComponentToEntity(newPlanetPositionEntity.planetPositionEntity, ComponentType::TRANSFORM_COMPONENT);

		//	Get the Hierarchy and Transofmr Components.
		std::shared_ptr<HierarchyComponent> currentPlanetPositionEntityHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanetPositionEntity.planetPositionEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::STAR_SYSTEM));
		std::shared_ptr<TransformComponent> currentPlanetPositionEntityTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanetPositionEntity.planetPositionEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::STAR_SYSTEM));

		starSystemHierarchyComponent->addChild(newPlanetPositionEntity.planetPositionEntity);
		currentPlanetPositionEntityHierarchyComponent->setParent(starSystem.starSystemEntity);
		currentPlanetPositionEntityTransformComponent->getTransform()->setScale(glm::vec3(0.25, 0.25, 0.25));
		currentPlanetPositionEntityTransformComponent->getTransform()->rotateBy(RNGs::doubleRand(0.0, 3.14), glm::vec3(0.0, 1.0, 0.0));

		//	Create the Planet.
		long int currentPlanet = planetMakerSystem->createPlanet();

		std::shared_ptr<HierarchyComponent> currentPlanetHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(currentPlanet, ComponentType::HIERARCHY_COMPONENT, ModuleType::STAR_SYSTEM));
		std::shared_ptr<TransformComponent> currentPlanetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(currentPlanet, ComponentType::TRANSFORM_COMPONENT, ModuleType::STAR_SYSTEM));

		currentPlanetPositionEntityHierarchyComponent->addChild(currentPlanet);

		currentPlanetHierarchyComponent->setParent(newPlanetPositionEntity.planetPositionEntity);
		currentPlanetTransformComponent->getTransform()->translateBy(glm::normalize(glm::vec3(1.0, 0.0, 0.0)) * currentDistance * 4.0f);

		starSystem.planets.push_back(newPlanetPositionEntity);
	}

	//	Return the Star System.
	return starSystem.starSystemEntity;
}

//	Update the Star System.
void StarSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	for (int i = 0; i < starSystem.planets.size(); i++)
	{
		std::shared_ptr<TransformComponent> currentPlanetPositionEntityTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(starSystem.planets[i].planetPositionEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::STAR_SYSTEM));
		currentPlanetPositionEntityTransformComponent->getTransform()->rotateBy(starSystem.planets[i].rotation * deltaTime, glm::vec3(0.0, 1.0, 0.0));
	}
}

//	Shut Down the Star System.
void StarSystem::shutDownSystem()
{

}

//	Destroy the System.
void StarSystem::destroySystem()
{

}

//	Process the Events.
void StarSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{

}
