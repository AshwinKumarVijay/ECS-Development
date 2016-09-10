#include "MovementSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"

#include "../../ECS/Component/Component.h"

#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Transform/Transform.h"
#include "../Components/SpeedComponent/SpeedComponent.h"


//	Default MovementSystem Constructor.
MovementSystem::MovementSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	: System(newEntityManager, newEventQueue, ModuleType::MOVEMENT_SYSTEM)
{


}


//	Default MovementSystem Destructor.
MovementSystem::~MovementSystem()
{


}


//	Initialize the Movement System.
void MovementSystem::initializeSystem()
{


}



//	Update the Movement System.
void MovementSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);

	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::SPEED_COMPONENT);

	//	If there are no entities, we do not really have to do anything.
	if (entities != NULL)
	{
		//	Iterate over the entities, and process them.
		for (auto currentEntity : *entities)
		{
			//	Get the Hierarchy Component.
			std::shared_ptr<const SpeedComponent> speedComponent = std::dynamic_pointer_cast<const SpeedComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::SPEED_COMPONENT));
			
			//	Get the transform component.
			std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::MOVEMENT_SYSTEM));

			//	Get the Transform Component Direction.
			glm::vec3 direction = transformComponent->getTransform()->getFowardDirection();

			//	Compute the move step of the direction.
			glm::vec3 moveStep = speedComponent->getSpeed() * direction * deltaTime;

			//	Translate the Transfrom Component.
			transformComponent->getTransform()->translateBy(moveStep);

		}
	}
}

//	Process the Events for the Movement System.
void MovementSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are any Events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		//	Respond to the System shutdown.
		if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
		{
			shutDownSystem();
		}
	}
}

//	Shut Down the Movement System.
void MovementSystem::shutDownSystem()
{

}


//	Clean up the Movement System.
void MovementSystem::destroySystem()
{

}