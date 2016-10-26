#include "UniverseECS.h"

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

#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/SpeedComponent/SpeedComponent.h"
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

//	Default UniverseECS Constructor
UniverseECS::UniverseECS()
{


}

//	Default UniverseECS Destructor
UniverseECS::~UniverseECS()
{

}

//	Initialize the Demo ECS.
void UniverseECS::initializeUniverseECS()
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

	//	Dispatch the ECS_START_EVENT to the Event Queue.
	getDispatcher()->dispatchToEventQueue(EventType::ECS_START_EVENT, ModuleType::GLOBAL, ComponentType::NO_COMPONENT, 0);
}

//	Initialize the VR Scene.
void UniverseECS::initializeScene()
{
	//	Create the Sphere Entity.
	planetEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy, Transform, Geometry and Rendering Component.
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(planetEntity, ComponentType::RENDERING_COMPONENT);

	std::shared_ptr<GeometryComponent> planetGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	planetGeometryComponent->setGeometryType("GEN-Icosphere");

	std::shared_ptr<RenderingComponent> planetRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	planetRenderingComponent->setMaterialType("Material-Default-2");
	planetRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

	std::shared_ptr<TransformComponent> planetTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	planetTransformComponent->getTransform()->setScale(glm::vec3(10.0, 10.0, 10.0));


	ringEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy, Transform, Geometry and Rendering Component.
	getEntityManager()->addComponentToEntity(ringEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(ringEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(ringEntity, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(ringEntity, ComponentType::RENDERING_COMPONENT);

	std::shared_ptr<GeometryComponent> planetRingGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	planetRingGeometryComponent->setGeometryType("GEN-PlanetRing");

	std::shared_ptr<RenderingComponent> planetRingRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	planetRingRenderingComponent->setMaterialType("Material-Default-1");
	planetRingRenderingComponent->setShadingType(ShadingTypes::OPAQUE_BASIC);

	std::shared_ptr<TransformComponent> planetRingTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(ringEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	planetRingTransformComponent->getTransform()->setScale(glm::vec3(20.0, 20.0, 20.0));


}

//	Initialize the Camera Views.
void UniverseECS::initializeCameraViews()
{
	//	Create the Camera Entity.
	cameraEntity1 = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::CAMERA_COMPONENT);

	std::shared_ptr<TransformComponent> cameraTransformComponent1 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity1, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	cameraTransformComponent1->getTransform()->setPosition(glm::vec3(50.0, 50.0, 50.0));
	cameraTransformComponent1->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));

	//	Create the Camera Entity.
	cameraEntity2 = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::CAMERA_COMPONENT);

	std::shared_ptr<TransformComponent> cameraTransformComponent2 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity2, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	cameraTransformComponent2->getTransform()->setPosition(glm::vec3(-50.0, 50.0, 50.0));
	cameraTransformComponent2->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));


	//	Create the Camera Entity.
	cameraEntity3 = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::CAMERA_COMPONENT);

	std::shared_ptr<TransformComponent> cameraTransformComponent3 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity3, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	cameraTransformComponent3->getTransform()->setPosition(glm::vec3(-50.0, 50.0, -50.0));
	cameraTransformComponent3->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));

	//	Create the Camera Entity.
	cameraEntity4 = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::CAMERA_COMPONENT);

	std::shared_ptr<TransformComponent> cameraTransformComponent4 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity4, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	cameraTransformComponent4->getTransform()->setPosition(glm::vec3(50.0, 50.0, -50.0));
	cameraTransformComponent4->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));
}

//	Load the Resources From File.
void UniverseECS::loadResourcesFromFile(const std::string & resourceFile)
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
void UniverseECS::processResource(const ResourceDescription & currentResourceDescription)
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
void UniverseECS::processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType)
{
	inputSystem->processInput(ecsKey, inputEventType, eventType);
}

//	Update the UniverseECS
void UniverseECS::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	
	std::shared_ptr<TransformComponent> baseTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(planetEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	baseTransformComponent->getTransform()->rotateBy(glm::pi<float>() * 0.1f * deltaTime, glm::vec3(0.0, 1.0, 0.0));

	//
	ECS::update(deltaTime, currentFrameTime, lastFrameTime);
}

//	Shut down the Demo ECS
void UniverseECS::shutDownUniverseECS()
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
void UniverseECS::destroyUniverseECS()
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