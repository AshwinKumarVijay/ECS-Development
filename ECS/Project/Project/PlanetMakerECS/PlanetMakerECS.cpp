#include "PlanetMakerECS.h"

#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/EntityManager/EntityManager.h"

#include "../ECS/System/System.h"
#include "../Systems/TransformSystem/TransformSystem.h"
#include "../Systems/RenderingSystem/RenderingSystem.h"
#include "../Systems/CameraSystem/CameraSystem.h"
#include "../Systems/MovementSystem/MovementSystem.h"
#include "../Systems/InputSystem/InputSystem.h"
#include "../Systems/InteractionMovementResponseSystem/InteractionMovementResponseSystem.h"
#include "../Systems/DebugSystem/DebugSystem.h"

#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include "../Transform/Transform.h"

#include "../GeometryGeneratorSelector/GeometryGeneratorSelector.h"
#include "../TextureGeneratorSelector/TextureGeneratorSelector.h"

#include "../Resources/ResourceManager/GeometryResourceManager/GeometryResourceManager.h"
#include "../Resources/ResourceManager/MaterialResourceManager/MaterialResourceManager.h"
#include "../Resources/ResourceManager/LightResourceManager/LightResourceManager.h"
#include "../Resources/ResourceManager/TextureResourceManager/TextureResourceManager.h"
#include "../Resources/ResourceManager/ShaderResourceManager/ShaderResourceManager.h"

#include "../Resources/ResourceData/MaterialData/MaterialData.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../Resources/ResourceData/LightData/LightData.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"

#include "../Renderers/BasicRenderer/BasicRenderer.h"

//	Default PlanetMakerECS Constructor
PlanetMakerECS::PlanetMakerECS()
{


}

//	Default PlanetMakerECS Destructor
PlanetMakerECS::~PlanetMakerECS()
{

}

//	Initialize the Demo ECS.
void PlanetMakerECS::initializePlanetMakerECS()
{
	//	Initialize the underlying ECS.
	ECS::initializeECS();

	//	Initialize the InteractionGenerationSystem.
	inputSystem = std::make_shared<InputSystem>(getEntityManager(), getEventQueue());
	inputSystem->initializeSystem();

	interactionMovementResponseSystem = std::make_shared<InteractionMovementResponseSystem>(getEntityManager(), getEventQueue());
	interactionMovementResponseSystem->initializeSystem();

	//	Initialize the Movement System.
	movementSystem = std::make_shared<MovementSystem>(getEntityManager(), getEventQueue());
	movementSystem->initializeSystem();

	//	Initialize the Transform System.
	transformSystem = std::make_shared<TransformSystem>(getEntityManager(), getEventQueue());
	transformSystem->initializeSystem();

	//	Initialize the Camera System.
	cameraSystem = std::make_shared<CameraSystem>(getEntityManager(), getEventQueue());
	cameraSystem->initializeSystem();

	//	Initialize the Rendering System.
	renderingSystem = std::make_shared<RenderingSystem>(getEntityManager(), getEventQueue());
	renderingSystem->initializeSystem();

	//	
	debugSystem = std::make_shared<DebugSystem>(getEntityManager(), getEventQueue());
	debugSystem->initializeSystem();

	//	Create the Geometry, Material, Light, Texture and Shader Resource Manager.
	geometryResourceManager = std::make_shared<GeometryResourceManager>(getEventQueue());
	materialResourceManager = std::make_shared<MaterialResourceManager>(getEventQueue());
	lightResourceManager = std::make_shared<LightResourceManager>(getEventQueue());
	textureResourceManager = std::make_shared<TextureResourceManager>(getEventQueue());
	shaderResourceManager = std::make_shared<ShaderResourceManager>(getEventQueue());

	//	Initialize the VR Scene.
	initializeScene();

	//	Register the Systems.
	ECS::registerSystem(inputSystem);
	ECS::registerSystem(interactionMovementResponseSystem);
	ECS::registerSystem(movementSystem);
	ECS::registerSystem(transformSystem);
	ECS::registerSystem(cameraSystem);
	ECS::registerSystem(renderingSystem);
	ECS::registerSystem(debugSystem);

	//	Dispatch the ECS_START_EVENT to the Event Queue.
	getDispatcher()->dispatchToEventQueue(EventType::ECS_START_EVENT, ModuleType::GLOBAL, ComponentType::NO_COMPONENT, 0);
}

//	Initialize the VR Scene.
void PlanetMakerECS::initializeScene()
{
	////	Create the Sphere Entity.
	//planetEntity = getEntityManager()->createEntity();

	////	Add the Hierarcy, Transform, Geometry and Rendering Component.
	//getEntityManager()->addComponentToEntity(planetEntity, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT);
	//getEntityManager()->addComponentToEntity(planetEntity, ComponentType::RENDERING_COMPONENT);


	//std::shared_ptr<GeometryComponent> planetGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	//planetGeometryComponent->setGeometryType("GEN-Icosphere");

	//std::shared_ptr<RenderingComponent> planetRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	//planetRenderingComponent->setMaterialType("Material-Default-2");
	//planetRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

	//std::shared_ptr<TransformComponent> planetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	//planetTransformComponent->getTransform()->setScale(glm::vec3(10.0, 10.0, 10.0));

	//ringEntity = getEntityManager()->createEntity();

	////	Add the Hierarcy, Transform, Geometry and Rendering Component.
	//getEntityManager()->addComponentToEntity(ringEntity, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(ringEntity, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(ringEntity, ComponentType::GEOMETRY_COMPONENT);
	//getEntityManager()->addComponentToEntity(ringEntity, ComponentType::RENDERING_COMPONENT);

	//std::shared_ptr<GeometryComponent> planetRingGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	//planetRingGeometryComponent->setGeometryType("GEN-PlanetRing");

	//std::shared_ptr<RenderingComponent> planetRingRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	//planetRingRenderingComponent->setMaterialType("Material-Default-1");
	//planetRingRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

	//std::shared_ptr<TransformComponent> planetRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	//planetRingTransformComponent->getTransform()->setScale(glm::vec3(2.0, 2.0, 2.0));

	//std::shared_ptr<HierarchyComponent> planetHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent >(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
	//planetHierarchyComponent->addChild(ringEntity);

	//std::shared_ptr<HierarchyComponent> ringHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent >(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
	//ringHierarchyComponent->setParent(planetEntity);

	createPlanet();

}

//	Load the Resources From File.
void PlanetMakerECS::loadResourcesFromFile(const std::string & resourceFile)
{
	//	Parse the Resource Description File.
	rdfp.parseResourceDescriptionFile(resourceFile, resources);

	//	Iterate over all the resources.
	for (auto resourcesItr = resources.begin(); resourcesItr != resources.end(); resourcesItr++)
	{
		processResource(resourcesItr->second);
	}
}

//	Process Resource.
void PlanetMakerECS::processResource(const ResourceDescription & currentResourceDescription)
{
	//	Get the appropriate Resource Type.
	std::string resourceType = "None";
	bool hasType = currentResourceDescription.findProperty("Resource Type", resourceType);

	//	Check if we actually have the type, and can use it to appropriately process the data.
	if (hasType)
	{

		//	Light Resource.
		if (resourceType == "Light")
		{
			lightResourceManager->processResource(currentResourceDescription);
		}

		//	Material Resource.
		if (resourceType == "Material")
		{
			materialResourceManager->processResource(currentResourceDescription);
		}

		//	Geometry Resource.
		if (resourceType == "Geometry")
		{
			geometryResourceManager->processResource(currentResourceDescription);
		}

		//	OpenGL Shader Resource.
		if (resourceType == "OpenGL Shader")
		{
			shaderResourceManager->processResource(currentResourceDescription);
		}

		//	Texture Resource.
		if (resourceType == "Texture")
		{
			textureResourceManager->processResource(currentResourceDescription);
		}

	}
	else
	{
		std::cout << "Error! Resource Has No Type! " << std::endl;
	}
}

//	Process the provided input.
void PlanetMakerECS::processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType)
{
	inputSystem->processInput(ecsKey, inputEventType, eventType);
}

//	Update the PlanetMakerECS
void PlanetMakerECS::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	
	std::shared_ptr<TransformComponent> planetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	planetTransformComponent->getTransform()->rotateBy(glm::pi<float>() * 0.2f * deltaTime, glm::vec3(0.0, 1.0, 0.0));

	//	
	std::shared_ptr<TransformComponent> ringTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(ringsVesselEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
//	ringTransformComponent->getTransform()->rotateBy(glm::pi<float>() * 0.3f * deltaTime, glm::vec3(0.0, 1.0, 0.0));

	//
	ECS::update(deltaTime, currentFrameTime, lastFrameTime);
}

//	Create the Planet.
void PlanetMakerECS::createPlanet()
{

	//	Create the Planet Entity.
	planetVesselEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy and the Transform
	getEntityManager()->addComponentToEntity(planetVesselEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(planetVesselEntity, ComponentType::TRANSFORM_COMPONENT);

	std::shared_ptr<HierarchyComponent> planetVesselHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(planetVesselEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));

	std::shared_ptr<TransformComponent> planetVesselTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetVesselEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	planetVesselTransformComponent->getTransform()->setScale(glm::vec3(10.0, 10.0, 10.0));

	//	Create the Planet Entity.
	planetEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy and the Transform
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::RENDERING_COMPONENT);

	planetVesselHierarchyComponent->addChild(planetEntity);

	std::shared_ptr<HierarchyComponent> planetHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
	planetHierarchyComponent->setParent(planetVesselEntity);


	std::shared_ptr<TransformComponent> planetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));

	std::shared_ptr<GeometryComponent> planetGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	planetGeometryComponent->setGeometryType("GEN-Icosphere");

	std::shared_ptr<RenderingComponent> planetRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	planetRenderingComponent->setMaterialType("Material-Default-2");
	planetRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);


	float planetSize = RNGs::doubleRand(0.4, 1.0);

	ringsVesselEntity = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(ringsVesselEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(ringsVesselEntity, ComponentType::TRANSFORM_COMPONENT);

	planetVesselHierarchyComponent->addChild(ringsVesselEntity);

	std::shared_ptr<HierarchyComponent> ringVesselsEntityHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(ringsVesselEntity, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
	ringVesselsEntityHierarchyComponent->setParent(planetVesselEntity);



	//	Check if we want rings and what type of rings.
	if (true)
	{
		std::vector<long int> rings;

		int ringCount = RNGs::intRand(0, 4);

		for (int i = 0; i < ringCount; i++)
		{

			long int newRingVessel = getEntityManager()->createEntity();

			getEntityManager()->addComponentToEntity(newRingVessel, ComponentType::HIERARCHY_COMPONENT);
			getEntityManager()->addComponentToEntity(newRingVessel, ComponentType::TRANSFORM_COMPONENT);

			ringVesselsEntityHierarchyComponent->addChild(newRingVessel);

			std::shared_ptr<HierarchyComponent> newRingVesselHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newRingVessel, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
			newRingVesselHierarchyComponent->setParent(ringsVesselEntity);

			float ringRotate = RNGs::doubleRand(2.25, 4.00);

			std::shared_ptr<TransformComponent> newRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newRingVessel, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
			newRingTransformComponent->getTransform()->rotateBy(ringRotate * glm::pi<float>() / 4.0f, glm::vec3(1.0, 0.0, 0.0));


			bool isOrbitRing = (RNGs::intRand(0, 1) == 1) ? true : false;

			if (isOrbitRing)
			{
				float ringWidth = RNGs::doubleRand(2.25, 4.00);

				long int newRing = getEntityManager()->createEntity();

				getEntityManager()->addComponentToEntity(newRing, ComponentType::HIERARCHY_COMPONENT);
				getEntityManager()->addComponentToEntity(newRing, ComponentType::TRANSFORM_COMPONENT);
				getEntityManager()->addComponentToEntity(newRing, ComponentType::GEOMETRY_COMPONENT);
				getEntityManager()->addComponentToEntity(newRing, ComponentType::RENDERING_COMPONENT);

				newRingVesselHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newRingVessel, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
				newRingVesselHierarchyComponent->addChild(newRing);

				std::shared_ptr<HierarchyComponent> newRingHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newRing, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
				newRingHierarchyComponent->setParent(newRingVessel);

				std::shared_ptr<TransformComponent> newRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newRing, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
				newRingTransformComponent->getTransform()->setScale(glm::vec3(1.0, 1.0, 1.0) * ringWidth);

				std::shared_ptr<GeometryComponent> newRingGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(newRing, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
				newRingGeometryComponent->setGeometryType("GEN-PlanetRing");

				std::shared_ptr<RenderingComponent> newRingRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(newRing, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
				newRingRenderingComponent->setMaterialType("Material-Default-1");
				newRingRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);
		
				long int newPlanet = getEntityManager()->createEntity();

				getEntityManager()->addComponentToEntity(newPlanet, ComponentType::HIERARCHY_COMPONENT);
				getEntityManager()->addComponentToEntity(newPlanet, ComponentType::TRANSFORM_COMPONENT);
				getEntityManager()->addComponentToEntity(newPlanet, ComponentType::GEOMETRY_COMPONENT);
				getEntityManager()->addComponentToEntity(newPlanet, ComponentType::RENDERING_COMPONENT);

				newRingVesselHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newRingVessel, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
				newRingVesselHierarchyComponent->addChild(newPlanet);

				std::shared_ptr<HierarchyComponent> newPlanetHierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(getEntityManager()->getComponentOfEntity(newPlanet, ComponentType::HIERARCHY_COMPONENT, ModuleType::NO_MODULE));
				newPlanetHierarchyComponent->setParent(newRingVessel);

				std::shared_ptr<TransformComponent> newPlanetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(newPlanet, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
				newPlanetTransformComponent->getTransform()->translateBy(glm::vec3(0.0, 0.0, 1.0) * ringWidth);
				newPlanetTransformComponent->getTransform()->scaleBy(glm::vec3(0.1, 0.1, 0.1));

				std::shared_ptr<GeometryComponent> newPlanetGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(newPlanet, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
				newPlanetGeometryComponent->setGeometryType("GEN-Asteroid");

				std::shared_ptr<RenderingComponent> newPlanetRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(newPlanet, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
				newPlanetRenderingComponent->setMaterialType("Material-Default-2");
				newPlanetRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

			}
			else
			{


			}

		}
	}


	//	Check if we want some terrain.
}

//	Shut down the Demo ECS
void PlanetMakerECS::shutDownPlanetMakerECS()
{
	//	Shut down the underlying ECS.
	ECS::shutDownECS();

	//	Destroy the Input System.
	inputSystem->shutDownSystem();

	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->shutDownSystem();

	//	Destroy the Movement System.
	movementSystem->shutDownSystem();

	//	Destroy the CameraSystem.
	cameraSystem->shutDownSystem();

	//	Destroy the Transform System.
	transformSystem->shutDownSystem();

	//	Destroy the Rendering System.
	renderingSystem->shutDownSystem();
}

//	Clean Up the Demo ECS.
void PlanetMakerECS::destroyPlanetMakerECS()
{
	//	Clean up the underlying ECS.
	ECS::destroyECS();

	//	Destroy the Input System.
	inputSystem->destroySystem();

	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->destroySystem();

	//	Destroy the Movement System.
	movementSystem->destroySystem();

	//	Destroy the CameraSystem.
	cameraSystem->destroySystem();

	//	Destroy the Transform System.
	transformSystem->destroySystem();

	//	Destroy the Rendering System.
	renderingSystem->destroySystem();

}