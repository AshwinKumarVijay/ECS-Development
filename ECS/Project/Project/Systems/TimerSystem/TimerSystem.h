#pragma once

#include <memory>

#include "../ECS/System/System.h"

class TimerSystem : public System
{
public:

	//	Default TimedEventSystem Constructor.
	TimerSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue, const ModuleType & newSystemTypeSignature);

	//	Default TimedEventSystem Destructor.
	virtual ~TimerSystem();

	//	Initialize the System.
	virtual void initializeSystem();

	//	Update the System.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut Down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();

protected:

	//	Process the Events.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

private:

};

