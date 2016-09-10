#pragma once

#include <memory>

#include "../TypesList/EventTypes.h"
#include "../TypesList/ModuleType.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"

#include "../StringModifiers/StringModifiers.h"

#include "../ECS/ECSEvent/ECSEvent.h"
#include "../Events/InputEvent/InputEvent.h"
#include "../Events/ResourceEvent/ResourceEvent.h"

class EventQueue;
class EventDispatcher;

class ResourceManager
{

public:


	/**

	Name: ResourceManager
	Parameters: -
	Purpose: Default ResourceManager Constructor
	Return Value: -
	Other Output: -

	*/
	ResourceManager(std::shared_ptr<EventQueue> newEventQueue, const ModuleType & newSystemTypeSignature);


	/**

	Name: ~ResourceManager
	Parameters: -
	Purpose: Default ResourceManager Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~ResourceManager();


	/**

	Name: getDispatcherReceiver
	Parameters: -
	Purpose: Returns the DispatcherReceiver that this system is using.
	Return Value:
	- (shared_ptr<DispatcherReceiver>) - A pointer to the DispatcherReceiver.
	Other Output: -

	*/
	std::shared_ptr<EventDispatcher> getDispatcher() const;


private:

	//	The EventQueue that this system will refer to.
	std::shared_ptr<EventQueue> eventQueue;

	//	Used to dispatch Events to the Event Queue.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	The Signature representing the Manager Type
	ModuleType managerTypeSignature;

};

