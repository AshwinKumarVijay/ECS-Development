#include "PlanetMakerSystem.h"

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

//	Default Planet Maker System Constructor.
PlanetMakerSystem::PlanetMakerSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::PLANET_MAKER_SYSTEM)
{
	
}

//	Default Planet Maker System Destructor.
PlanetMakerSystem::~PlanetMakerSystem()
{

}

//	Initialize the System.
void PlanetMakerSystem::initializeSystem()
{
	//	Generate the commonly used Resource Types.

}

//	Create a new planet and add it to the current list of planets.
long int PlanetMakerSystem::createPlanet()
{
	PlanetEntity newPlanet;
	newPlanet.planet = getEntityManager()->createEntity();

	//	Add the Hierarcy and the Transform
	getEntityManager()->addComponentToEntity(newPlanet.planet, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(newPlanet.planet, ComponentType::TRANSFORM_COMPONENT);

	//	Get the Hierarchy Component.
	std::shared_ptr<HierarchyComponent> planetHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planet, ComponentType::HIERARCHY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));

	//	Get the Transform Component, and set the Scale.
	std::shared_ptr<TransformComponent> planetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planet, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
	planetTransformComponent->getTransform()->setScale(glm::vec3(1.0, 1.0, 1.0) * 5.0f);

	//	Create the new planetary body.
	newPlanet.planetaryBody = getEntityManager()->createEntity();

	//	Add the Hierarchy and the Transform, and the Geometry and the Rendering Components.
	getEntityManager()->addComponentToEntity(newPlanet.planetaryBody, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(newPlanet.planetaryBody, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(newPlanet.planetaryBody, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(newPlanet.planetaryBody, ComponentType::RENDERING_COMPONENT);

	//	Add this child to the Heirarchy Component of the Planet.
	planetHierarchyComponent->addChild(newPlanet.planetaryBody);

	//	Get the Hierarchy Component of the Planetary Body, and set the Parent.
	std::shared_ptr<HierarchyComponent> planetaryBodyHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planetaryBody, ComponentType::HIERARCHY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
	planetaryBodyHierarchyComponent->setParent(newPlanet.planet);

	//	Get the Transform Component of the Planetary Body.
	std::shared_ptr<TransformComponent> planetaryBodyTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planetaryBody, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));

	//	Set the Geometry Type of the Planetary Body.
	std::shared_ptr<GeometryComponent> planetaryBodyGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planetaryBody, ComponentType::GEOMETRY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
	planetaryBodyGeometryComponent->setGeometryType("GEN-Icosphere");

	//	Set the Rendering Types of the Planetary Body.
	std::shared_ptr<RenderingComponent> planetaryBodyRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(newPlanet.planetaryBody, ComponentType::RENDERING_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
	planetaryBodyRenderingComponent->setMaterialType("Material-Default-4");
	planetaryBodyRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

	//	Set the rotation of the planetary body.
	newPlanet.planetaryRotation = 0.01f;

	//	
	int ringCount = RNGs::intRand(0, 100);

	for (int i = 0; i < ringCount; i++)
	{
		PlanetRingEntity newPlanetRingEntity;
		
		//	Create the new Ring Entity.
		newPlanetRingEntity.ringEntity = getEntityManager()->createEntity();

		//	Add the Hierarchy and the Transform, and the Geometry and the Rendering Components.
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.ringEntity, ComponentType::HIERARCHY_COMPONENT);
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.ringEntity, ComponentType::TRANSFORM_COMPONENT);

		//	
		planetHierarchyComponent->addChild(newPlanetRingEntity.ringEntity);

		//
		std::shared_ptr<HierarchyComponent> planetRingHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.ringEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		planetRingHierarchyComponent->setParent(newPlanet.planet);

		//
		std::shared_ptr<TransformComponent> planetRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.ringEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		float ringRotate = (float)RNGs::doubleRand(00.0f, glm::pi<float>() * 2.0f);
		planetRingTransformComponent->getTransform()->rotateBy(ringRotate, glm::normalize(glm::vec3(0.0, 1.0, 0.0)));

		//	
		newPlanetRingEntity.rotation = (float)RNGs::doubleRand(0.0, 0.1);

		//	
		newPlanetRingEntity.subRingEntity = getEntityManager()->createEntity();

		//	Add the Hierarchy and the Transform, and the Geometry and the Rendering Components.
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.subRingEntity, ComponentType::HIERARCHY_COMPONENT);
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.subRingEntity, ComponentType::TRANSFORM_COMPONENT);
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.subRingEntity, ComponentType::GEOMETRY_COMPONENT);
		getEntityManager()->addComponentToEntity(newPlanetRingEntity.subRingEntity, ComponentType::RENDERING_COMPONENT);

		//	Add this child to the Heirarchy Component of the Planet.
		planetRingHierarchyComponent->addChild(newPlanetRingEntity.subRingEntity);

		//	Get the Hierarchy Component of the Planet Ring, and set the Parent.
		std::shared_ptr<HierarchyComponent> subRingHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.subRingEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		subRingHierarchyComponent->setParent(newPlanetRingEntity.ringEntity);

		//	Get the Transform Component of the Planet Ring.
		std::shared_ptr<TransformComponent> subRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.subRingEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		subRingTransformComponent->getTransform()->setScale(glm::vec3(1.0, 1.0, 1.0) * (float)RNGs::doubleRand(0.1, 0.2));
		subRingTransformComponent->getTransform()->translateBy(glm::vec3(1.0, 0.0, 0.0) * (float)RNGs::doubleRand(3.0, 5.25));
		subRingTransformComponent->getTransform()->translateBy(glm::vec3(0.0, 1.0, 0.0) * (float)RNGs::doubleRand(-1.0, 1.0));

		//	Set the Geometry Type of the Planet Ring.
		std::shared_ptr<GeometryComponent> subRingGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.subRingEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		subRingGeometryComponent->setGeometryType("GEN-Asteroid");

		//	Set the Rendering Types of the Planet Ring.
		std::shared_ptr<RenderingComponent> subRingRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(newPlanetRingEntity.subRingEntity, ComponentType::RENDERING_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		subRingRenderingComponent->setMaterialType("Material-Default-5");
		subRingRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

		//	Add the new planet ring.
		newPlanet.planetRings.push_back(newPlanetRingEntity);

	}
	
	// Add the planet to the list of planets.
	planets.push_back(newPlanet);

	//	Return the new planet.
	return newPlanet.planet;
}

//	Update the System.
void PlanetMakerSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Iterate over the planets, and rotate them by some amount.
	for (int i = 0; i < planets.size(); i++)
	{
		std::shared_ptr<TransformComponent> planetaryBodyTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planets[i].planet, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
		planetaryBodyTransformComponent->getTransform()->rotateBy(planets[i].planetaryRotation, glm::normalize(glm::vec3(0.1, 1.0, 0.0)));

		for (int j = 0; j < planets[i].planetRings.size(); j++)
		{
			std::shared_ptr<TransformComponent> planetRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planets[i].planetRings[j].subRingEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::PLANET_MAKER_SYSTEM));
			planetRingTransformComponent->getTransform()->rotateBy(planets[i].planetRings[j].rotation, glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
		}
	}
}

//	Shut down the System.
void PlanetMakerSystem::shutDownSystem()
{

}

//	Destroy the System.
void PlanetMakerSystem::destroySystem()
{

}
//	Process the Events.
void PlanetMakerSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{

}
