#pragma once

#include <map>
#include <memory>

#include "glm\glm.hpp"
#include "../ResourceData.h"

class LightData : public ResourceData
{
public:
	
	//	Default LightData Constructor.
	LightData();

	//	Default LightData Destructor.
	virtual ~LightData();

	//	
	void setEnabled(bool newIsEnabled);
	bool getEnabled() const;

	void setLocal(bool newIsLocal);
	bool getLocal() const;

	int getLightType() const;
	void setLightType(int newLightType);

	glm::vec3 getLightColor() const;
	void setLightColor(glm::vec3 newLightColor);

	float getLightIntensity() const;
	void setLightIntensity(float newLightIntensity);

	glm::vec4 getLightPosition() const;
	void setLightPosition(glm::vec4 newLightPosition);

	glm::vec4 getDistanceAttenuation() const;
	void setDistanceAttenuation(glm::vec4 newDistanceAttenuation);

	void setSpotCosCutOffAndExponent(glm::vec4 newSpotCosCutOffAndExponent);
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
