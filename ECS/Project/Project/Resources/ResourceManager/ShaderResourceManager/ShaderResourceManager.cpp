#include "ShaderResourceManager.h"
#include "../../ResourceData/ShaderData/ShaderData.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default ShaderResourceManager Constructor
ShaderResourceManager::ShaderResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, ModuleType::SHADER_MANAGER)

{

}


//	Default ShaderResourceManager Destructor
ShaderResourceManager::~ShaderResourceManager()
{

}

//	Add the ShaderData, specified by name.
void ShaderResourceManager::addShader(std::string newShaderName, std::shared_ptr<ShaderData> newShaderData)
{
	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(newShaderName);

	if (shaderIterator != mapNameToShaderData.end())
	{
		//	TO DO
		//	Throw Shader already present error.
	}
	else
	{
		//	Insert the Shader, under the appropriate name.
		mapNameToShaderData.insert(std::make_pair(newShaderName, newShaderData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::SHADER_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::SHADER_MANAGER, newShaderName, newShaderData);
		getDispatcher()->dispatchToEventQueue(newEvent);

	}
}

//	Return the ShaderData, specified by name.
std::shared_ptr<const ShaderData> ShaderResourceManager::viewShader(std::string requestedShaderData) const
{
	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(requestedShaderData);

	if (shaderIterator != mapNameToShaderData.end())
	{
		return shaderIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find Shader error.
		return NULL;
	}
}

//	Delete the Shader, specified by the name.
void ShaderResourceManager::deleteShader(std::string deadShaderName)
{

	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(deadShaderName);

	if (shaderIterator != mapNameToShaderData.end())
	{
		mapNameToShaderData.erase(deadShaderName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::SHADER_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::SHADER_MANAGER, deadShaderName, nullptr);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find Shader error.
	}
}
