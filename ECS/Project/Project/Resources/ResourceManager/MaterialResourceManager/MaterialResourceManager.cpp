#include "MaterialResourceManager.h"
#include "../../ResourceData/ResourceData.h"
#include "../../ResourceData/MaterialData/MaterialData.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"


//	Default MaterialResourceManager Constructor
MaterialResourceManager::MaterialResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, ModuleType::MATERIAL_MANAGER)
{


}

//	Default MaterialResourceManager Destructor
MaterialResourceManager::~MaterialResourceManager()
{


}

//	Add a Material to the Material Resource Manager, specified by name.
void MaterialResourceManager::addMaterial(std::string newMaterialName, std::shared_ptr<MaterialData> newMaterialData)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(newMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		//	TO DO
		//	Throw Material already present error.
	}
	else
	{
		//	Insert the MaterialData, under the appropriate name.
		mapNameToMaterialData.insert(std::make_pair(newMaterialName, newMaterialData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::MATERIAL_MANAGER, newMaterialName, std::dynamic_pointer_cast<const ResourceData>(newMaterialData));
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Material in the Material Resource Manager, specified by name.
void MaterialResourceManager::updateMaterial(std::string currentMaterialName, std::shared_ptr<MaterialData> newMaterialData)
{

	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		materialIterator->second = newMaterialData;
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_UPDATED, ModuleType::MATERIAL_MANAGER, currentMaterialName, newMaterialData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
	}

}

//	Return the Material in the Material Resource Manager, specified by name.
std::shared_ptr<MaterialData> MaterialResourceManager::getMaterial(std::string currentMaterialName)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		return materialIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
		return NULL;
	}
}

//	Return the Material in the Material Resource Manager, specified by name. Return a const pointer.
std::shared_ptr<const MaterialData> MaterialResourceManager::viewMaterial(std::string currentMaterialName) const
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		return materialIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
		return NULL;
	}
}

//	Delete the Material in the MaterialResourceManager.
void MaterialResourceManager::deleteMaterial(std::string deadMaterialName)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(deadMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		mapNameToMaterialData.erase(deadMaterialName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::MATERIAL_MANAGER, deadMaterialName, nullptr);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
	}
}
