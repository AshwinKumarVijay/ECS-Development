#include "TransformSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"

#include "../../ECS/Component/Component.h"

#include "../Transform/Transform.h"
#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"

//	Default TransformSystem Constructor
TransformSystem::TransformSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::TRANSFORM_SYSTEM)
{


}

//	Default TransformSystem Destructor
TransformSystem::~TransformSystem()
{


}

//	Initialize System.
void TransformSystem::initializeSystem()
{


}

//	Update the Transform System.
void TransformSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);

	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::HIERARCHY_COMPONENT);

	//	If there are no entities, we do not really have to do anything.
	if (entities != NULL)
	{
		//	Iterate over the entities, and process them.
		for (auto currentEntity : *entities)
		{
			//	Get the Hierarchy Component.
			std::shared_ptr<const HierarchyComponent> hierarchyComponent = std::dynamic_pointer_cast<const HierarchyComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::HIERARCHY_COMPONENT));

			//	Check if this entity has a parent. 
			if (hierarchyComponent->getParent() == -1)
			{
				//	Get the transform component.
				std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::TRANSFORM_SYSTEM));

				//	Compute the transform.
				transformComponent->getTransform()->computeTransformMatrix();

				//	TO DO
				//	Here, compute the transform matrix recursively down the tree. 
			}
		}

	}
}

//	Process the Events.
void TransformSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
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

//	Shut Down the System.
void TransformSystem::shutDownSystem()
{

}

//	Miscellaneous clean up the system.
void TransformSystem::destroySystem()
{


}
