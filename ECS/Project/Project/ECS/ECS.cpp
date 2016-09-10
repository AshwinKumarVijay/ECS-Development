#include "ECS.h"

#include "EventQueue\EventQueue.h"
#include "DispatcherReceiver\EventDispatcher\EventDispatcher.h"
#include "DispatcherReceiver\EventReceiver\EventReceiver.h"
#include "EntityManager\EntityManager.h"
#include "System\System.h"



//	Default Entity Constructor
ECS::ECS()
{


}

//	Default Entity Destructor
ECS::~ECS()
{
	//	Set the associated Event Queue to NULL.
	eventQueue = NULL;

	//	Set the Dispatcher Receiver to NULL.
	eventDispatcher = NULL;
	eventReceiver = NULL;

	//	Set the EntityManager to NULL.
	entityManager = NULL;
}

//	Register a System, and return its place in the update order.
int ECS::registerSystem(std::shared_ptr<System> newSystem)
{
	//	Get the new system index.
	int index = (int)systems.size();

	//	Add the system.
	systems.push_back(newSystem);
	
	//	Return the index of the added system.
	return index;
}


//	Deregister the System.
void ECS::deregisterSystem(const int & systemOrder)
{
	//	
	if((systems.begin() + systemOrder) < systems.end())
	{ 
		//	Erase the system.
		systems.erase(systems.begin() + systemOrder);
	}
}

//	Update the ECS, and the Systems, with the provided timestamps.
void ECS::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Updating the Entity Manager does not do anything.
	entityManager->update(deltaTime, currentFrameTime, lastFrameTime);

	//	Update all the Systems.
	for (int i = 0; i < systems.size(); i++)
	{
		systems[i]->update(deltaTime, currentFrameTime, lastFrameTime);
	}

	getReceiver()->clearEvents();
}

//	Return the Entity Manager.
std::shared_ptr<EntityManager> ECS::getEntityManager() const
{
	return entityManager;
}

//	Return the Event Queue.
std::shared_ptr<EventQueue> ECS::getEventQueue() const
{
	return eventQueue;
}

//	Return the Event Dispatcher.
std::shared_ptr<EventDispatcher> ECS::getDispatcher() const
{
	return eventDispatcher;
}

//	Return the Event Receiver.
std::shared_ptr<EventReceiver> ECS::getReceiver() const
{
	return eventReceiver;
}


//	Initialize the Systems.
void ECS::initializeECS()
{
	//	Create the EventQueue.
	eventQueue = std::make_shared<EventQueue>();

	//	Create the DispatcherReceiver associated with the overall EntityComponentSystem.
	eventDispatcher = std::make_shared<EventDispatcher>(eventQueue);
	eventReceiver = std::make_shared<EventReceiver>();

	//	Add the ECS DispatchReceiver to the EventQueue.
	eventQueue->addReceiver(eventReceiver);

	//	Create the EntityManager.
	entityManager = std::make_shared<EntityManager>(eventQueue);
}



//	Shut Down the Systems.
void ECS::shutDownECS()
{

}

//	Destroy the ECS.
void ECS::destroyECS()
{


}
