#include "LightsModule.h"
#include "../../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"
#include "../../RenderableManager/RenderableManager.h"
#include "../../Renderer/SceneMetaData.h"

//	Default LightsModule Constructor.
LightsModule::LightsModule(std::shared_ptr<Renderer> newModuleRenderer) : RendererModule(newModuleRenderer)
{
	screenWidth = getModuleRenderer().lock()->getSceneQuality().screenWidth;
	screenHeight = getModuleRenderer().lock()->getSceneQuality().screenHeight;
	shadowMapSize = getModuleRenderer().lock()->getSceneQuality().shadowSize;
}

//	Default LightsModule Destructor.
LightsModule::~LightsModule()
{

}

//	Add a Light.
void LightsModule::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	
	auto lightModulei = mapNameToLightModuleMetaData.find(newLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaData.end())
	{
		throw "Light Module Error: Add Light. Light with specified name already exists!";
	}
	else
	{
		//	Create the new Light Module Meta Data.
		LightModuleMetaData newLightModuleMetaData;

		//	Copy over the data.
		newLightModuleMetaData.lightEnabledShadowLightType = newLightData->lightPosition;
		newLightModuleMetaData.lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		newLightModuleMetaData.lightPosition = newLightData->lightPosition;
		newLightModuleMetaData.lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
		newLightModuleMetaData.lightConeDirection = newLightData->lightConeDirection;
		newLightModuleMetaData.spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;

		//	Create the Light Textures And Framebuffers.
		createLightTexturesAndFramebuffers(newLightModuleMetaData);

		//	Add the Light Module Meta Data.
		mapNameToLightModuleMetaData[newLightName] = newLightModuleMetaData;
	}
}

//	Update a Light.
void LightsModule::updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	
	auto lightModulei = mapNameToLightModuleMetaData.find(currentLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaData.end())
	{
		//	Create the new Light Module Meta Data.
		LightModuleMetaData newLightModuleMetaData;


		//	Copy over the light data.
		newLightModuleMetaData.lightEnabledShadowLightType = newLightData->lightPosition;
		newLightModuleMetaData.lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		newLightModuleMetaData.lightPosition = newLightData->lightPosition;
		newLightModuleMetaData.lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
		newLightModuleMetaData.lightConeDirection = newLightData->lightConeDirection;
		newLightModuleMetaData.spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;


		//	Copy over the light meta data.
		newLightModuleMetaData.lightColorMap = mapNameToLightModuleMetaData[currentLightName].lightColorMap;
		newLightModuleMetaData.lightDepthMap = mapNameToLightModuleMetaData[currentLightName].lightDepthMap;


		//	Create the Light Textures And Framebuffers.
		createLightTexturesAndFramebuffers(newLightModuleMetaData);

		//	Add the Light Module Meta Data.
		mapNameToLightModuleMetaData[currentLightName] = newLightModuleMetaData;
	}
	else
	{
		//	Throw an Error.
		throw "Light Module Error: Update Light. Light with specified name does not exist!";
	}

}

//	Delete a Light.
void LightsModule::deleteLight(std::string deadLightName)
{

	//	Find the Light by name.
	auto lightModulei = mapNameToLightModuleMetaData.find(deadLightName);

	//	Check if the Light exists.
	if (lightModulei != mapNameToLightModuleMetaData.end())
	{
		//	Delete the Textures.
		glDeleteTextures(1, &lightModulei->second.lightColorMap);
		glDeleteTextures(1, &lightModulei->second.lightDepthMap);

		//	Erase the Light.
		mapNameToLightModuleMetaData.erase(lightModulei);
	}
	else
	{
		//	Throw an Error.
		throw "Light Module Error: Delete Light. Light with specified name does not exist!";
	}
}


//	Create the Light Textures and Framebuffers
void LightsModule::createLightTexturesAndFramebuffers(LightModuleMetaData & newLightModuleMetaData)
{
	//	Active Texture.
	glActiveTexture(GL_TEXTURE0 + 0);

	//	Generate the Light Color Map.
	glGenTextures(1, &newLightModuleMetaData.lightColorMap);
	glBindTexture(GL_TEXTURE_2D, newLightModuleMetaData.lightColorMap);
	glTextureImage2DEXT(newLightModuleMetaData.lightColorMap, GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTextureParameteri(newLightModuleMetaData.lightColorMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(newLightModuleMetaData.lightColorMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);


	//	Generate the Light Depth Map.
	glGenTextures(1, &newLightModuleMetaData.lightDepthMap);
	glBindTexture(GL_TEXTURE_2D, newLightModuleMetaData.lightDepthMap);

	glTextureImage2DEXT(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTextureParameteri(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(newLightModuleMetaData.lightDepthMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

}
