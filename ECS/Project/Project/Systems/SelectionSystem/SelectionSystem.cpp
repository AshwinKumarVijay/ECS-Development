#include "SelectionSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"

#include "../../ECS/Component/Component.h"

//	Default SelectionSystem Constructor.
SelectionSystem::SelectionSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, ModuleType::SELECTION_SYSTEM)
{
	currentlySelectedEntity = -1;
}


//	Default SelectionSystem Destructor.
SelectionSystem::~SelectionSystem()
{

}

//	Initialize the Selection System.
void SelectionSystem::initializeSystem()
{
	currentlySelectedEntity = -1;
}


//	Update the Selection System.
void SelectionSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Process the Events.
	processEvents(deltaTime, currentFrameTime, lastFrameTime);
}

//	Process the Events.
void SelectionSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
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

//	Shut down the Selection System.
void SelectionSystem::shutDownSystem()
{
	currentlySelectedEntity = -1;
}

//	Clean up the Selection System.
void SelectionSystem::destroySystem()
{

}
