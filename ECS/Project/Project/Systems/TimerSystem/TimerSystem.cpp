#include "TimerSystem.h"

#include "../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/ECSEvent/ECSEvent.h"



//	Default TimedEventSystem Constructor.
TimerSystem::TimerSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue, const ModuleType & newSystemTypeSignature)
	: System(newEntityManager, newEventQueue, ModuleType::TIMER_SYSTEM)
{

}


//	Default TimedEventSystem Destructor.
TimerSystem::~TimerSystem()
{

}

//	Initialize the System.
void TimerSystem::initializeSystem()
{

}

//	Update the System.
void TimerSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{

}

//	Shut Down the System.
void TimerSystem::shutDownSystem()
{

}

//	Clean up the System.
void TimerSystem::destroySystem()
{

}

//	Process the Events.
void TimerSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{

}
