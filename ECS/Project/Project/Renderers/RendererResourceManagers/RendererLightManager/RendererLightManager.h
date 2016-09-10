#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "glm\glm.hpp"

class LightData;

//	The Renderer Light Data.
struct RendererLightData
{
	//	
	glm::vec4 lightEnabledLocalLightType = glm::vec4(0.0, 1.0, 1.0, 0.0);

	//	
	glm::vec4 lightColorAndLightIntensity = glm::vec4(1.0, 1.0, 0.0, 1.0);

	//	
	glm::vec4 lightPosition = glm::vec4(10, 10, 10, 1.0);

	//	
	glm::vec4 lightDistanceAttenuation = glm::vec4(0.0, 0.0, 0.0, 0.0);

	//	
	glm::vec4 lightConeDirection = glm::vec4(-1.0, -1.0, -1.0, 0.0);

	//	
	glm::vec4 spotCosCutOffAndExponent = glm::vec4();
};

class RendererLightManager
{

public:

	//	Default RendererLightManager Constructor.
	RendererLightManager();

	//	Default RendererLightManager Destructor.
	virtual ~RendererLightManager();

	//	Add a Light to the RendererLightMananger.
	virtual void addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData);

	//	View a Light in the RendererLightMananger.
	virtual std::shared_ptr<const RendererLightData> viewLight(std::string requestedLightName);

	//	Update a Light in the RendererLightManager.
	virtual void updateLight(std::string requestedLightName, std::shared_ptr<const LightData> newLightData);

	//	Delete a Light in the RendererLightManager.
	virtual void deleteLight(std::string deadLightName);


private:

	//	The Ambient Light.
	glm::vec3 ambientLightValues;

	//	The Environment Cube Map Texture Name.
	std::string environmentCubeMapTextureName;

	//	The Names of the Lights.
	std::map<std::string, std::shared_ptr<RendererLightData>> mapNameToLightData;

};

