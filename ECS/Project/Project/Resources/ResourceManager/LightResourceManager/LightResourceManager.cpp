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

//	Process the provided resource.
void LightResourceManager::processResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";

	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "Light")
		{
			std::shared_ptr<LightData> newLightData = std::make_shared<LightData>();

			newResourceDescription.findProperty("Resource Name", resourceName);
			
			//	Get whether the Light is enabled.
			std::string lightEnabledLine = "False";
			newResourceDescription.findProperty("Light Enabled", lightEnabledLine);
			newLightData->setEnabled(lightEnabledLine == "True");

			std::string lightLocalLine = "True";
			newResourceDescription.findProperty("Light Local", lightLocalLine);
			newLightData->setLocal(lightLocalLine == "True");

			//	Get the Light Type.
			std::string lightTypeLine = "1.0";
			newResourceDescription.findProperty("Light Type", lightTypeLine);
			newLightData->setLightType(std::stoi(lightTypeLine));

			//	Get the Light color.
			std::string lightColorLine = "1.0, 1.0, 1.0";
			newResourceDescription.findProperty("Light Color", lightColorLine);
			std::vector<std::string> lightColorValues = StringModifiers::split_string(lightColorLine, ",");
			newLightData->setLightColor(glm::vec3(std::stof(lightColorValues[0]), std::stof(lightColorValues[1]), std::stof(lightColorValues[2])));

			//	Get the Light Intensity.
			std::string lightIntenstiyLine = "1.0";
			newResourceDescription.findProperty("Light Intensity", lightIntenstiyLine);
			newLightData->setLightIntensity(std::stof(lightIntenstiyLine));

			//	Get the Light Position.
			std::string lightPositionLine = "0.0, 25.0, 0.0, 1.0";
			newResourceDescription.findProperty("Light Position", lightPositionLine);
			std::vector<std::string> lightPositionValues = StringModifiers::split_string(lightPositionLine, ",");
			newLightData->setLightPosition(glm::vec4(std::stof(lightPositionValues[0]), std::stof(lightPositionValues[1]), std::stof(lightPositionValues[2]), std::stof(lightPositionValues[3])));

			//	Get the Light Attenuation.
			std::string lightAttenuationLine = "0.0, 0.0, 0.0, 0.0";
			newResourceDescription.findProperty("Light Attenuation and Distance", lightPositionLine);
			std::vector<std::string> lightAttenuationValues = StringModifiers::split_string(lightAttenuationLine, ",");
			newLightData->setDistanceAttenuation(glm::vec4(std::stof(lightAttenuationValues[0]), std::stof(lightAttenuationValues[1]), std::stof(lightAttenuationValues[2]), std::stof(lightAttenuationValues[3])));


			//	Get the Light SpotCosCutOffAndExponent.
			std::string lightSpotCosCutOffAndExponentLine = "0.0, 0.0, 0.0, 0.0";
			newResourceDescription.findProperty("Light SpotLight Cosine and Cutoff", lightSpotCosCutOffAndExponentLine);
			std::vector<std::string> lightSpotCosCutOffAndExponentValues = StringModifiers::split_string(lightSpotCosCutOffAndExponentLine, ",");
			glm::vec4 lightSpotCosCutOffAndExponent = glm::vec4(std::stof(lightSpotCosCutOffAndExponentValues[0]), std::stof(lightSpotCosCutOffAndExponentValues[1]), std::stof(lightSpotCosCutOffAndExponentValues[2]), std::stof(lightSpotCosCutOffAndExponentValues[3]));

			
			//	Add the Light!
			addLight(resourceName, newLightData);
		}
	}
	else
	{

	}

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
