#include "LightResourceManager.h"
#include "../../ResourceData/LightData/LightData.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default LightResourceManager Constructor
LightResourceManager::LightResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	:ResourceManager(newEventQueue, ModuleType::LIGHT_MANAGER)
{
	
}

//	Default LightResourceManager Destructor
LightResourceManager::~LightResourceManager()
{

}

//	Add the Light, under the specified name.
void LightResourceManager::addLight(std::string newLightName, std::shared_ptr<LightData> newLightData)
{
	auto lightIterator = mapNameToLightData.find(newLightName);

	if (lightIterator != mapNameToLightData.end())
	{
		//	TO DO
		//	Throw Light already present error.
	}
	else
	{
		//	Insert the GeometryData, under the appropriate name.
		mapNameToLightData.insert(std::make_pair(newLightName, newLightData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::LIGHT_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::LIGHT_MANAGER, newLightName, newLightData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Light, under the specified name.
void LightResourceManager::updateLight(std::string currentLightName, std::shared_ptr<LightData> newLightData)
{
	auto lightIterator = mapNameToLightData.find(currentLightName);

	if (lightIterator != mapNameToLightData.end())
	{
		lightIterator->second = newLightData;
	}
	else
	{
		//	TO DO
		//	Throw did not find LightData error.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::LIGHT_RESOURCE, ResourceEventType::RESOURCE_UPDATED, ModuleType::LIGHT_MANAGER, currentLightName, newLightData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Return the Light, specified by name.
std::shared_ptr<LightData> LightResourceManager::getLight(std::string currentLightName)
{
	auto lightIterator = mapNameToLightData.find(currentLightName);

	if (lightIterator != mapNameToLightData.end())
	{
		return lightIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find LightData error.
		return NULL;
	}
}

//	Return the Light, specified by name. Return a const pointer.
std::shared_ptr<const LightData> LightResourceManager::viewLight(std::string currentLightName) const
{
	auto lightIterator = mapNameToLightData.find(currentLightName);

	if (lightIterator != mapNameToLightData.end())
	{
		return lightIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find LightData error.
		return NULL;
	}
}


//	Delete the Light, specified by name.
void LightResourceManager::deleteLight(std::string deadLightName)
{
	auto lightIterator = mapNameToLightData.find(deadLightName);

	if (lightIterator != mapNameToLightData.end())
	{
		mapNameToLightData.erase(deadLightName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::LIGHT_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::LIGHT_MANAGER, deadLightName, nullptr);
	}
	else
	{
		//	TO DO
		//	Throw did not find LightData error.
	}
}
