#pragma once

#include <map>
#include <memory>

#include "glm\glm.hpp"
#include "../ResourceData.h"

class LightData : public ResourceData
{
public:
	
	//	Add Comments - TO DO
	LightData(
		bool setEnabled,
		bool setLocal,
		int newLightType,
		glm::vec3 newLightColor,
		float newLightIntensity,
		glm::vec4 newLightPosition,
		glm::vec4 newDistanceAttenuation,
		glm::vec4 newSpotCosCutOffAndExponent);
	
	//	Add Comments - TO DO
	virtual ~LightData();


	bool getEnabled() const;
	bool getLocal() const;
	int getLightType() const;
	glm::vec3 getLightColor() const;
	float getLightIntensity() const;
	glm::vec4 getLightPosition() const;
	glm::vec4 getDistanceAttenuation() const;
	glm::vec4 getSpotCosCutOffAndExponent() const;

private:

	//	Add Comments - TO DO
	bool isEnabled;

	//	Add Comments - TO DO
	bool isLocal;

	//	Add Comments - TO DO
	int lightType;

	//	Add Comments - TO DO
	glm::vec3 lightColor;

	//	Add Comments - TO DO
	float lightIntensity;

	//	Add Comments - TO DO
	glm::vec4 lightPosition;

	//	Add Comments - TO DO
	glm::vec4 distanceAttenuation;

	//	Add Comments - TO DO
	glm::vec4 spotCosCutOffAndExponent;

};
