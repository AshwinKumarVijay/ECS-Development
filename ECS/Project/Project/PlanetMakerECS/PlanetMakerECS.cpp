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

#include "../PlanetMakerSystem/PlanetMakerSystem.h"

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

	//	Initialize the Debug System.
	debugSystem = std::make_shared<DebugSystem>(getEntityManager(), getEventQueue());
	debugSystem->initializeSystem();

	//	Initialize the Input System.
	inputSystem = std::make_shared<InputSystem>(getEntityManager(), getEventQueue());
	inputSystem->initializeSystem();

	//	Initialize the InteractionMovementResponse System.
	interactionMovementResponseSystem = std::make_shared<InteractionMovementResponseSystem>(getEntityManager(), getEventQueue());
	interactionMovementResponseSystem->initializeSystem();

	//	Initialize the PlanetMaker System.
	planetMakerSystem = std::make_shared<PlanetMakerSystem>(getEntityManager(), getEventQueue());
	planetMakerSystem->initializeSystem();

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

	//	Register the Systems.
	ECS::registerSystem(debugSystem);
	ECS::registerSystem(inputSystem);
	ECS::registerSystem(interactionMovementResponseSystem);
	ECS::registerSystem(planetMakerSystem);
	ECS::registerSystem(transformSystem);
	ECS::registerSystem(cameraSystem);
	ECS::registerSystem(renderingSystem);

	//	Dispatch the ECS_START_EVENT to the Event Queue.
	getDispatcher()->dispatchToEventQueue(EventType::ECS_START_EVENT, ModuleType::GLOBAL, ComponentType::NO_COMPONENT, 0);

	//	Initialize the Scene.
	initializeScene();
}

//	Initialize the VR Scene.
void PlanetMakerECS::initializeScene()
{
	//	Generate the Camera Entity.
	cameraEntity = getEntityManager()->createEntity();

	//	Attach the Components to the Camera Entity.
	getEntityManager()->addComponentToEntity(cameraEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity, ComponentType::CAMERA_COMPONENT);
	getEntityManager()->addComponentToEntity(cameraEntity, ComponentType::MOVEMENT_RESPONSE_COMPONENT);

	//	
	planetMakerSystem->createPlanet();

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
	ECS::update(deltaTime, currentFrameTime, lastFrameTime);
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

	//	Destroy the PlanetMakerSystem.
	planetMakerSystem->shutDownSystem();

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

	//	Destroy the PlanetMakerSystem.
	planetMakerSystem->destroySystem();

	//	Destroy the CameraSystem.
	cameraSystem->destroySystem();

	//	Destroy the Transform System.
	transformSystem->destroySystem();

	//	Destroy the Rendering System.
	renderingSystem->destroySystem();

}