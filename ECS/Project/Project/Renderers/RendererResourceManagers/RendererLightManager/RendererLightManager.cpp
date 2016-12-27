#include "RendererLightManager.h"
#include "../../../Resources/ResourceData/LightData/LightData.h"

//	Default RendererLightManager Constructor
RendererLightManager::RendererLightManager()
{

}


//	Default RendererLightManager Destructor
RendererLightManager::~RendererLightManager()
{

}

//	Add a Light.
void RendererLightManager::addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData)
{
	//	Find the Light.
	auto lightIterator = mapNameToLightData.find(newLightName);

	//	Check if the Light Already Exists.
	if (lightIterator != mapNameToLightData.end())
	{
		//	TO DO
		//	Throw Already Exists Error.
	}
	else
	{
		//	Construct the RendererLightData
		std::shared_ptr<RendererLightData> newRendererLightData = std::make_shared<RendererLightData>();

		//	Check if the Light is actually active.
		if (newLightData->getEnabled())
			newRendererLightData->lightEnabledShadowLightType[0] = 1.0f;

		//	Check if the Light is local.
		if (newLightData->getLocal())
			newRendererLightData->lightEnabledShadowLightType[1] = 1.0f;

		//	Get the Light Type.
		newRendererLightData->lightEnabledShadowLightType[2] = (float)newLightData->getLightType();
		
		//	Get the Distance Attenuation.
		newRendererLightData->lightDistanceAttenuation = newLightData->getDistanceAttenuation();
	
		//	Get the Light Position.
		newRendererLightData->lightPosition = newLightData->getLightPosition();

		//	Get the Color and the Light Intensity.
		newRendererLightData->lightColorAndLightIntensity = glm::vec4(newLightData->getLightColor(), newLightData->getLightIntensity());

		//	Add the new RendererLightData.
		mapNameToLightData[newLightName] = newRendererLightData;
	}
}

//	Update the Light.
void RendererLightManager::updateLight(std::string requestedLightName, std::shared_ptr<const LightData> newLightData)
{
	//	Find the Light.
	auto lightIterator = mapNameToLightData.find(requestedLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapNameToLightData.end())
	{
		//	Construct the RendererLightData
		std::shared_ptr<RendererLightData> newRendererLightData = std::make_shared<RendererLightData>();

		//	Check if the Light is actually active.
		if (newLightData->getEnabled())
			newRendererLightData->lightEnabledShadowLightType[0] = 1.0;

		//	Check if the Light is local.
		if (newLightData->getLocal())
			newRendererLightData->lightEnabledShadowLightType[1] = 1.0;

		//	Get the Light Type.
		newRendererLightData->lightEnabledShadowLightType[2] = (float)newLightData->getLightType();

		//	Get the Distance Attenuation.
		newRendererLightData->lightDistanceAttenuation = newLightData->getDistanceAttenuation();

		//	Get the Light Position.
		newRendererLightData->lightPosition = newLightData->getLightPosition();

		//	Get the Color and the Light Intensity.
		newRendererLightData->lightColorAndLightIntensity = glm::vec4(newLightData->getLightColor(), newLightData->getLightIntensity());

		//	Add the new RendererLightData.
		mapNameToLightData[requestedLightName] = newRendererLightData;
	}
	else
	{
		//	TO DO
		//	Throw does not exist error.
	}
}

//	View the Names and Lights Associated with the Data.
const std::map<std::string, std::shared_ptr<RendererLightData>>& RendererLightManager::viewMapNameToLightData()
{
	return mapNameToLightData;
}

//	Return a const pointer to the light.
std::shared_ptr<const RendererLightData> RendererLightManager::viewLight(std::string requestedLightName)
{
	//	Find the Light.
	auto lightIterator = mapNameToLightData.find(requestedLightName);

	//	Check if the Light actually exists.
	if (lightIterator != mapNameToLightData.end())
	{
		//	Return the Light.
		return lightIterator->second;
	}
	else
	{
		//	Throw does not exist error.
		return NULL;
	}
}

//	Delete the Light specified by Name.
void RendererLightManager::deleteLight(std::string deadLightName)
{
	//	Find the Light by name.
	auto lightIterator = mapNameToLightData.find(deadLightName);

	//	Check if the Light exists.
	if (lightIterator != mapNameToLightData.end())
	{
		//	Erase the Light.
		mapNameToLightData.erase(lightIterator);
	}
	else
	{
		//	TO DO
		//	Throw does not exist error.
	}
}
