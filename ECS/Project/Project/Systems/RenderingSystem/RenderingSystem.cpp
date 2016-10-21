#include "RenderingSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"
#include "../Events/ResourceEvent/ResourceEvent.h"

#include "../Renderers/Renderer/Renderer.h"
#include "../Renderers/BasicRenderer/BasicRenderer.h"
#include "../Renderers/DeferredRenderer/DeferredRenderer.h"

#include "../Renderers/Renderable/Renderable.h"

#include "../Camera/Camera.h"

#include "../../ECS/Component/Component.h"
#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/CameraComponent/CameraComponent.h"

#include "../Transform/Transform.h"

//	Default RenderingSystem Constructor
RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::TRANSFORM_SYSTEM)

{

}

//	Default RenderingSystem Destructor
RenderingSystem::~RenderingSystem()
{

}

//	Initialize the Rendering System.
void RenderingSystem::initializeSystem()
{
	//	Create the Default Renderer.
	renderer = std::make_shared<DeferredRenderer>();

	//	Initialize the Renderer.
	renderer->initializeRenderer();

	//	Create the new camera.
	defaultCamera = std::make_shared<Camera>();
	activeCamera = std::make_shared<Camera>();
}

//	Update the Rendering System this frame.
void RenderingSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Process the Events.
	processEvents(deltaTime, currentFrameTime, lastFrameTime);

	//	Render the Renderer
	activeCamera->updateCamera();
	renderer->render(deltaTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Process the Events that have occurred.
void RenderingSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are any Events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		if (nextEvent->getModuleOrigin() != ModuleType::RENDERING_SYSTEM)
		{
			//	Component Added.
			if (nextEvent->getEventType() == EventType::COMPONENT_ADDED)
			{
				//	Check if the component added was a Rendering Component.
				if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					addRenderable(nextEvent->getEntityID());
				}

			}	//	Component Changed.
			else if (nextEvent->getEventType() == EventType::COMPONENT_CHANGED)
			{
				//	Check if the component changed was the Transform Component.
				if (nextEvent->getComponentType() == ComponentType::TRANSFORM_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());

				}	//	Check if the component changed was the Geometry Component.
				else if (nextEvent->getComponentType() == ComponentType::GEOMETRY_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());

				}	//	Check if the component changed was the Rendering Component.
				else if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());

				}	//	Check if the component changed was the Camera Component.
				else if (nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT)
				{
					updateCamera();
				}
				else
				{

				}

			}	//	Component Destroyed.
			else if (nextEvent->getEventType() == EventType::COMPONENT_DESTROYED)
			{
				//	Check if the component changed destroyed was a Rendering Component.
				if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					removeRenderable(nextEvent->getEntityID());
				}
				else if (nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT)
				{
					updateCamera();
				}

			}	//	Shut Down the System.
			else if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
			{
				shutDownSystem();
			}
		}

		//	Process the Resource Events.
		processResourceEvents(nextEvent);
	}
}

//	Process the Event if it is a ResourceEvent.
void RenderingSystem::processResourceEvents(std::shared_ptr<const ECSEvent> nextEvent)
{
	//	Convert the event to a Resource ECS Event.
	std::shared_ptr<const ResourceEvent> resourceEvent = std::dynamic_pointer_cast<const ResourceEvent>(nextEvent);

	//	Check if it was a Resource ECS Event.
	if (resourceEvent != NULL)
	{
		if (resourceEvent->getEventType() == EventType::RESOURCE_EVENT)
		{
			if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_ADDED)
			{
				//	Add the Geometry resource, if the event was a Geometry resource event.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{
					renderer->addGeometry(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const GeometryData>(resourceEvent->getResourceData()));
				}	//	Add the Material resource, if the event was a Material resource event.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					renderer->addMaterial(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const MaterialData>(resourceEvent->getResourceData()));
				}	//	Add the Shader resource, if the event was a Shader resource event.
				else if (resourceEvent->getResourceType() == ResourceType::SHADER_RESOURCE)
				{
					renderer->addShader(std::dynamic_pointer_cast<const ShaderData>(resourceEvent->getResourceData()));
				}	//	Add the Light resource, if the event was a Light resource event.
				else if (resourceEvent->getResourceType() == ResourceType::LIGHT_RESOURCE)
				{
					renderer->addLight(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const LightData>(resourceEvent->getResourceData()));
				}	//	Add the Texture resource, if the event was a Texture resource event.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					renderer->addTexture(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const TextureData>(resourceEvent->getResourceData()));
				}
			}
			else if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_UPDATED)
			{
				//	Add the Geometry resource, if the event was a Geometry resource event.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{
					renderer->updateGeometry(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const GeometryData>(resourceEvent->getResourceData()));
				}	//	Add the Material resource, if the event was a Material resource event.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					renderer->updateMaterial(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const MaterialData>(resourceEvent->getResourceData()));
				}	//	Add the Light resource, if the event was a Light resource event.
				else if (resourceEvent->getResourceType() == ResourceType::LIGHT_RESOURCE)
				{
					renderer->updateLight(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const LightData>(resourceEvent->getResourceData()));
				}	//	Add the Texture resource, if the event was a Texture resource event.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					renderer->updateTexture(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const TextureData>(resourceEvent->getResourceData()));
				}
			}
			else if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_DESTROYED)
			{
				//	Delete the appropriate Geometry resource, if it is a Geometry resource.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{
					renderer->deleteGeometry(resourceEvent->getResourceName());
				}	//	Delete the appropriate Material resource, if it is a Material resource.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					renderer->deleteMaterial(resourceEvent->getResourceName());
				}	//	Delete the appropriate Shader resource, if it is a Shader resource.
				else if (resourceEvent->getResourceType() == ResourceType::SHADER_RESOURCE)
				{
					renderer->deleteShader(resourceEvent->getResourceName());
				}	//	Delete the appropriate Light resource, if it is a Light resource.
				else if (resourceEvent->getResourceType() == ResourceType::LIGHT_RESOURCE)
				{
					renderer->deleteLight(resourceEvent->getResourceName());
				}	//	Dlete the appropriate Texture resource, if it is a Texture resource.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					renderer->deleteTexture(resourceEvent->getResourceName());
				}
			}
		}
	}
}

//	Process Camera Events.
void RenderingSystem::processCameraEvents(std::shared_ptr<const ECSEvent> nextEvent)
{
	//	
	if (nextEvent != NULL)
	{

	}
}

//	Return a pointer to the Renderer associated with the Renderer.
std::shared_ptr<Renderer> RenderingSystem::getRenderer()
{
	return renderer;
}
	
//	Shut Down the System.
void RenderingSystem::shutDownSystem()
{
	renderer->cleanUpRenderer();
}

//	Clean up the Rendering System.
void RenderingSystem::destroySystem()
{

}

//	Add the Renderable to the associated Renderer.
void RenderingSystem::addRenderable(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<RenderingComponent> renderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, ModuleType::RENDERING_SYSTEM));
	
	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() == -1)
	{
		//	Get the Transform Component of the current entity.
		std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));

		//	Get the Geometry Component of the current entity.
		std::shared_ptr<const GeometryComponent> geometryComponent = std::dynamic_pointer_cast<const GeometryComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::GEOMETRY_COMPONENT));

		//	Set the RenderableID associated with the RenderingComponent.
		renderingComponent->setRenderableID(renderer->createRenderable());

		//	Update the Shader Type associated with the Renderable of this EntityID.
		updateRenderableShaderType(entityID);

		//	Update the Geometry Type associated with the Renderable of this EntityID.
		updateRenderableGeometryType(entityID);

		//	Update the Material Type associated with the Renderable of this EntityID.
		updateRenderableMaterialType(entityID);

		//	Update the Transform associated with the Renderable of this EntityID.
		updateRenderableTransformMatrix(entityID);
	}
}

//	Update the Renderable.
void RenderingSystem::updateRenderable(const long int & entityID)
{
	//	Update the Shader Type associated with the Renderable of this EntityID.
	updateRenderableShaderType(entityID);

	//	Update the Material Type associated with the Renderable of this EntityID.
	updateRenderableMaterialType(entityID);

	//	Update the Geometry Type associated with the Renderable of this EntityID.
	updateRenderableGeometryType(entityID);

	//	Update the Transform Matrix associated with the Renderable of this EntityID.
	updateRenderableTransformMatrix(entityID);
}

//	Update the Shader Type of the specified Renderable.
void RenderingSystem::updateRenderableShaderType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Update the Shader Type associated with this Renderable.
		renderer->updateShadingType(renderingComponent->getRenderableID(), renderingComponent->getShadingType());
	}
}

//	Update the Material Type of the specified Renderable.
void RenderingSystem::updateRenderableMaterialType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Update the Material Name associated with this Renderable.
		renderer->updateMaterialType(renderingComponent->getRenderableID(), renderingComponent->getMaterialType());
	}
}

//	Update the Geometry Type of the specified Renderable.
void RenderingSystem::updateRenderableGeometryType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{

		//	Get the Geometry Component of the current entity.
		std::shared_ptr<const GeometryComponent> geometryComponent = std::dynamic_pointer_cast<const GeometryComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::GEOMETRY_COMPONENT));

		//	Update the Geometry Name associated with this Renderable.
		renderer->updateGeometryType(renderingComponent->getRenderableID(), geometryComponent->getGeometryType());

	}
}

//	Update the Transform Matrix of the specified Renderable.
void RenderingSystem::updateRenderableTransformMatrix(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Get the Transform Component of the current entity.
		std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));

		//	Update the Transform associated with this Renderable.
		renderer->updateTransformMatrix(renderingComponent->getRenderableID(), *transformComponent->viewTransform()->getTransform());
	}
}

//	Update the Camera used with Renderer.
void RenderingSystem::updateCamera()
{
	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::CAMERA_COMPONENT);

	//	Check if an Active Camera Component was found.
	bool activeCameraAvailable = false;

	//	If there are no entities, we do not really have to do anything.
	if (entities != NULL)
	{
		//	Iterate over the entities, and process them.
		for (auto currentEntity : *entities)
		{

			//	Get the Camera Component.
			std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT));

			//	Get the Camera Component.
			std::shared_ptr<const CameraComponent> cameraComponent = std::dynamic_pointer_cast<const CameraComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::CAMERA_COMPONENT));

			//	Check if this is the Actice Camera.
			if (cameraComponent->getIsActive())
			{

				//	Active Camera.
				activeCameraAvailable = true;

				//	Set the Transform Related Camera Properties.
				activeCamera->setCameraPosition(transformComponent->viewTransform()->getPosition());
				activeCamera->setUpVector(transformComponent->viewTransform()->getUpVector());
				activeCamera->setLookAtDirection(transformComponent->viewTransform()->getFowardDirection());

				//	Set the Aspect Ratio and Field of View.
				activeCamera->setAspectRatio(cameraComponent->getAspectRatio());
				activeCamera->setFOV(cameraComponent->getFOV());

				//	Set the Near and Far Clip.
				activeCamera->setFarClip(cameraComponent->getFarClip());
				activeCamera->setNearClip(cameraComponent->getNearClip());
					
			}
		}
	}

	//	If an Active Camera Component was not found, use the default camera properties.
	if (activeCameraAvailable == false)
	{
		//	Set the Transform Related Camera Properties.
		activeCamera->setCameraPosition(defaultCamera->getCameraPosition());
		activeCamera->setUpVector(defaultCamera->getUpVector());
		activeCamera->setLookAtDirection(defaultCamera->getLookAtDirection());

		//	Set the Aspect Ratio and Field of View.
		activeCamera->setAspectRatio(defaultCamera->getAspectRatio());
		activeCamera->setFOV(defaultCamera->getFOV());

		//	Set the Near and Far Clip.
		activeCamera->setFarClip(defaultCamera->getFarClip());
		activeCamera->setNearClip(defaultCamera->getNearClip());
	}
}

//	Remove the Renderable.
void RenderingSystem::removeRenderable(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<RenderingComponent> renderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, ModuleType::RENDERING_SYSTEM));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Remove the Renderable from the Renderer.
		renderer->removeRenderable(entityID);

		//	Set the Renderable ID.
		renderingComponent->setRenderableID(-1);
	}
}