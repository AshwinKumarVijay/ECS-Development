#include "LightData.h"


//	Default LightData Constructor
LightData::LightData()
{
	//	Set whether the Light has been enabled.
	isEnabled = false;

	//	Set whether the Light is Local.
	isLocal = false;

	//	Set the Type of the Light.
	lightType = 1;

	//	Set the Color of the Light.
	lightColor = glm::vec3(1.0);

	//	
	lightPosition = glm::vec4(0.0, 25.0, 0.0, 1.0);

	//	Set the Intensity of the Light.
	lightIntensity = 1.0f;

	//	Set the Attenuation of the distance.
	distanceAttenuation = glm::vec4(0.0, 0.0, 0.0, 0.0);

	//	Set the Cutoffs for the SpotLight.
	spotCosCutOffAndExponent = glm::vec4(0.0, 0.0, 0.0, 0.0);
}


//	Default LightData Destructor
LightData::~LightData()
{


}

void LightData::setEnabled(bool newIsEnabled)
{
	isEnabled = newIsEnabled;
}

bool LightData::getEnabled() const
{
	return isEnabled;
}

void LightData::setLocal(bool newIsLocal)
{
	isLocal = newIsLocal;
}

bool LightData::getLocal() const
{
	return isLocal;
}

int LightData::getLightType() const
{
	return lightType;
}

void LightData::setLightType(int newLightType)
{
	 lightType = newLightType;
}

glm::vec3 LightData::getLightColor() const
{
	return lightColor;
}

void LightData::setLightColor(glm::vec3 newLightColor)
{
	lightColor = newLightColor;
}

float LightData::getLightIntensity() const
{
	return lightIntensity;
}

void LightData::setLightIntensity(float newLightIntensity)
{
	lightIntensity = newLightIntensity;
}

glm::vec4 LightData::getLightPosition() const
{
	return lightPosition;
}

void LightData::setLightPosition(glm::vec4 newLightPosition)
{
	lightPosition = newLightPosition;
}

glm::vec4 LightData::getDistanceAttenuation() const
{
	return distanceAttenuation;
}

void LightData::setDistanceAttenuation(glm::vec4 newDistanceAttenuation)
{
	distanceAttenuation = newDistanceAttenuation;
}

void LightData::setSpotCosCutOffAndExponent(glm::vec4 newSpotCosCutOffAndExponent)
{
	spotCosCutOffAndExponent = newSpotCosCutOffAndExponent;
}

glm::vec4 LightData::getSpotCosCutOffAndExponent() const
{
	return spotCosCutOffAndExponent;
}
