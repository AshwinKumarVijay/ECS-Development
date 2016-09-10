#include "LightData.h"


//	Default LightData Constructor
LightData::LightData(bool setEnabled, bool setLocal, int newLightType, glm::vec3 newLightColor, float newLightIntensity, glm::vec4 newLightPosition, glm::vec4 newDistanceAttenuation, glm::vec4 newSpotCosCutOffAndExponent)
{
	//	Set whether the Light has been enabled.
	isEnabled = setEnabled;

	//	Set whether the Light is Local.
	isLocal = setLocal;

	//	Set the Type of the Light.
	lightType = newLightType;

	//	Set the Color of the Light.
	lightColor = newLightColor;

	//	
	lightPosition = newLightPosition;

	//	Set the Intensity of the Light.
	lightIntensity = newLightIntensity;

	//	Set the Attenuation of the distance.
	distanceAttenuation = newDistanceAttenuation;

	//	Set the Cutoffs for the SpotLight.
	spotCosCutOffAndExponent = newSpotCosCutOffAndExponent;
}


//	Default LightData Destructor
LightData::~LightData()
{


}

bool LightData::getEnabled() const
{
	return isEnabled;
}

bool LightData::getLocal() const
{
	return isLocal;
}

int LightData::getLightType() const
{
	return lightType;
}

glm::vec3 LightData::getLightColor() const
{
	return lightColor;
}

float LightData::getLightIntensity() const
{
	return lightIntensity;
}

glm::vec4 LightData::getLightPosition() const
{
	return lightPosition;
}

glm::vec4 LightData::getDistanceAttenuation() const
{
	return distanceAttenuation;
}

glm::vec4 LightData::getSpotCosCutOffAndExponent() const
{
	return spotCosCutOffAndExponent;
}
