#include "CameraSystem.h"

#include "../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/ECSEvent/ECSEvent.h"
#include "../Events/InputEvent/InputEvent.h"
#include "../Events/InteractionEvent/InteractionEvent.h"

#include "../../ECS/Component/Component.h"
#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Components/CameraComponent/CameraComponent.h"


CameraSystem::CameraSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::CAMERA_SYSTEM)
{
	activeCameraEntity = -1;
}


CameraSystem::~CameraSystem()
{

}

//	Initialize the Camera System.
void CameraSystem::initializeSystem()
{


}


//	Update the Camera System.
void CameraSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime,  currentFrameTime, lastFrameTime);

}


//	Process the Events.
void CameraSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	while (getReceiver()->getNumberOfEvents() > 0)
	{

		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		//	Check if the Event was not sent out by the Camera System.
		if (nextEvent->getModuleOrigin() != ModuleType::CAMERA_SYSTEM)
		{
			if (nextEvent->getEventType() == EventType::INTERACTION_EVENT)
			{
				std::shared_ptr<const InteractionEvent> interactionEvent = std::dynamic_pointer_cast<const InteractionEvent>(nextEvent);

				//	Interaction Event Type - Check if it is a No Camera.
				if (interactionEvent->getInteractionEventType() == InteractionEventType::NO_CAMERA)
				{
					std::cout << "No Camera Set" << std::endl;
					setNoCamera();


				}	//	Interaction Event Type - Check if it is a Next Camera.
				else if (interactionEvent->getInteractionEventType() == InteractionEventType::NEXT_CAMERA)
				{
					std::cout << "Next Camera Set" << std::endl;
					setNextCamera();

				}	//	Interaction Event Type - Check if it is a Previous Camera.
				else if (interactionEvent->getInteractionEventType() == InteractionEventType::PREVIOUS_CAMERA)
				{
					std::cout << "Previous Camera Set" << std::endl;
					setPreviousCamera();
				}
			}

			if (nextEvent->getEventType() == EventType::COMPONENT_CHANGED)
			{
				//	Check whether the Camera Component has been changed.
				if (nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT)
				{
					updateCamera(nextEvent->getEntityID());
				}	//	Check whether the Transform Component has been changed.
				else if (nextEvent->getComponentType() == ComponentType::TRANSFORM_COMPONENT)
				{
					updateCamera(nextEvent->getEntityID());
				}
			}
		}

		//	Respond to the System shutdown.
		if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
		{
			shutDownSystem();
		}
	}
}



void CameraSystem::updateCamera(long int entity)
{
	//	Get the Transform component.
	std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entity, ComponentType::TRANSFORM_COMPONENT));

	//	Get the Camera Component.
	std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(getEntityManager()->getComponentOfEntity(entity, ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));


}


//	Shut Down the System.
void CameraSystem::shutDownSystem()
{


}

//	Clean up the CameraSystem.
void CameraSystem::destroySystem()
{


}

//	Set the Active Camera to be the Next Camera.
void CameraSystem::setNextCamera()
{
	
	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::CAMERA_COMPONENT);

	//	Check if there is no Active Camera.
	if (activeCameraEntity == -1 && entities != NULL)
	{
		//	Get the Camera Component.
		std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[0], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

		//	Set this to be the Active Camera Component.
		cameraComponent->setActive();

		//	Set the Active Camera Entity.
		activeCameraEntity = (*entities)[0];
	}
	else
	{
		if (entities != NULL)
		{
			//	Find the Entity Location.
			int entityLocation = -1;

			//	Iterate over the entites.
			for (int i = 0; i < entities->size(); i++)
			{
				if (activeCameraEntity == (*entities)[i])
				{
					entityLocation = i;
					break;
				}
			}

			//	
			if (entityLocation == -1)
			{
				//	Get the Camera Component.
				std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[0], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

				//	Set this to be the Active Camera Component.
				cameraComponent->setActive();

				//	Remember the ActiveCameraEntity.
				activeCameraEntity = (*entities)[0];

			}
			else
			{
				//	Get the Camera Component.
				std::shared_ptr<CameraComponent> activeCameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[entityLocation], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

				//	Set it to be Inactive.
				activeCameraComponent->setInactive();

				//	
				if (entityLocation == (entities->size() - 1))
				{
					activeCameraEntity = -1;
				}
				else
				{
					//	Get the Next Active Camera Component.
					std::shared_ptr<CameraComponent> nextActiveCameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[entityLocation], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

					//	Set it to be the Active Camera Component.
					nextActiveCameraComponent->setActive();
				}
			}
		}
		else
		{
			activeCameraEntity = -1;
		}
	}
}

//	Set the Active Camera to be the Previous Camera.
void CameraSystem::setPreviousCamera()
{
	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::CAMERA_COMPONENT);

	//	Check if there is no Active Camera.
	if (activeCameraEntity == -1 && entities != NULL)
	{
		//	Get the Camera Component.
		std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[0], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

		//	Set this to be the Active Camera Component.
		cameraComponent->setActive();

		//	Set the Active Camera Entity.
		activeCameraEntity = (*entities)[entities->size() - 1];
	}
	else
	{
		if (entities != NULL)
		{
			//	Find the Entity Location.
			int entityLocation = -1;

			//	Iterate over the entites.
			for (int i = 0; i < entities->size(); i++)
			{
				if (activeCameraEntity == (*entities)[i])
				{
					entityLocation = i;
					break;
				}
			}

			//	
			if (entityLocation == -1)
			{
				//	Get the Camera Component.
				std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[0], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

				//	Set this to be the Active Camera Component.
				cameraComponent->setActive();

				//	Set the Active Camera Entity.
				activeCameraEntity = (*entities)[entities->size() - 1];
			}
			else
			{
				//	Get the Camera Component.
				std::shared_ptr<CameraComponent> activeCameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[entityLocation], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

				//	Set it to be Inactive.
				activeCameraComponent->setInactive();

				//	
				if (entityLocation == 0)
				{
					activeCameraEntity = -1;
				}
				else
				{
					//	Get the Next Active Camera Component.
					std::shared_ptr<CameraComponent> nextActiveCameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[entityLocation], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

					//	Set it to be the Active Camera Component.
					nextActiveCameraComponent->setActive();
				}

			}
		}
		else
		{
			activeCameraEntity = -1;
		}
	}

}

//	Set the Active Camera to be No Camera.
void CameraSystem::setNoCamera()
{
		//	Get the EntityManager.
		std::shared_ptr<EntityManager> entityManager = getEntityManager();

		//	Get the entities with a Transform Component.
		std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::CAMERA_COMPONENT);

		if (entities != NULL)
		{
			//	
			for (int i = 0; i < entities->size(); i++)
			{
				//	Get the Camera Component.
				std::shared_ptr<CameraComponent> cameraComponent = std::dynamic_pointer_cast<CameraComponent>(entityManager->getComponentOfEntity((*entities)[i], ComponentType::CAMERA_COMPONENT, ModuleType::CAMERA_SYSTEM));

				//	Set this to be the Active Camera Component.
				cameraComponent->setInactive();
			}
		}

		//	Active Camera Entity
		activeCameraEntity = -1;
}
