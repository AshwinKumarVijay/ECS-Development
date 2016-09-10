#include "TextureResourceManager.h"
#include "../../ResourceData/TextureData/TextureData.h"	
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default TextureResourceManager Constructor
TextureResourceManager::TextureResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, ModuleType::TEXTURE_MANAGER)
{
}


//	Default TextureResourceManager Destructor
TextureResourceManager::~TextureResourceManager()
{

}

//	Add a Texture, specified by name.
void TextureResourceManager::addTexture(std::string newTextureName, std::shared_ptr<TextureData> newTextureData)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(newTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	TO DO
		//	Throw Geometry already present error.
	}
	else
	{
		//	Insert the Texture Data, under the appropriate name.
		mapNameToTextureData.insert(std::make_pair(newTextureName, newTextureData));

		//	Create the new Texture Resource.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::TEXTURE_MANAGER, newTextureName, newTextureData);

		//	Dispatch the creation to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Texture, specified by name.
void TextureResourceManager::updateTexture(std::string currentTextureName, std::shared_ptr<TextureData> newTextureData)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	Set the new Texture Data associated with the Texture.
		textureIterator->second = newTextureData;

		//	Create the update the Texture Resource.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_UPDATED, ModuleType::TEXTURE_MANAGER, currentTextureName, newTextureData);
		
		//	Dispatch the creation to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
	}
}

//	Return the Texture, specified by name.
std::shared_ptr<TextureData> TextureResourceManager::getTexture(std::string currentTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	//	
	if (textureIterator != mapNameToTextureData.end())
	{
		//	Return the associated the TextureData.
		return textureIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
		return NULL;
	}
}

//	Return the Texture, specified by name. Return a const pointer.
std::shared_ptr<const TextureData> TextureResourceManager::viewTexture(std::string currentTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	Return the associated the TextureData.
		return textureIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
		return NULL;
	}
}

//	Delete the Texture, specified by name.
void TextureResourceManager::deleteTexture(std::string deadTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(deadTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	
		mapNameToTextureData.erase(deadTextureName);

		//	Create the delete Texture event.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::TEXTURE_MANAGER, deadTextureName, nullptr);

		//	Dispatch the event to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
	}
}
