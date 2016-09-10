#pragma once

#include <vector>
#include <memory>

class EntityManager;
class EventQueue;
class EventDispatcher;
class EventReceiver;

class System;


class ECS
{

public:

	//	Default ECS Constructor
	ECS();

	
	//	Default ECS Destructor
	virtual ~ECS();

	//	Register a System, for the update cycle.
	virtual int registerSystem(std::shared_ptr<System> newSystem);

	//	Remove a System from the update cycle.
	virtual void deregisterSystem(const int & systemIndex);

	//	Update the ECS, and all associated systems.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);


protected:

	//	Initialization of the ECS.
	void initializeECS();

	//	Shut Down the ECS.
	void shutDownECS();

	//	Destroy the ECS.
	void destroyECS();


	//	Return a pointer to the asssociated EntityManager.
	virtual std::shared_ptr<EntityManager> getEntityManager() const;

	//	Return a pointer to the associated EventQueue.
	virtual std::shared_ptr<EventQueue> getEventQueue() const;

	//	Return a pointer to the associated EventDispatcher.
	virtual std::shared_ptr<EventDispatcher> getDispatcher() const;

	//	Return a pointer to the associated EventReceiver.
	virtual std::shared_ptr<EventReceiver> getReceiver() const;


private:

	//	The Associated Entity Manager
	std::shared_ptr<EntityManager> entityManager;

	//	The Associated Event Queue.
	std::shared_ptr<EventQueue> eventQueue;

	//	The Associated Dispatcher.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	The Associated Receiver.
	std::shared_ptr<EventReceiver> eventReceiver;

	//	The Associated List of Systems.
	std::vector<std::shared_ptr<System>> systems;

};

