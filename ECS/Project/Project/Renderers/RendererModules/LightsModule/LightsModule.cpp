#include "LightsModule.h"
#include "../../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"
#include "../../RenderableManager/RenderableManager.h"
#include "../../Renderer/SceneMetaData.h"

//	Default LightsModule Constructor.
LightsModule::LightsModule(std::shared_ptr<Renderer> newModuleRenderer) : RendererModule(newModuleRenderer)
{
	//	Copy over the Screen Width and Screen Height Textures.
	screenWidth = getModuleRenderer().lock()->getSceneQuality().screenWidth;
	screenHeight = getModuleRenderer().lock()->getSceneQuality().screenHeight;

	//	Copy over the Shadow Map Textures.
	shadowMapSize = getModuleRenderer().lock()->getSceneQuality().shadowSize;

	//	Copy over the Max Light Count.
	maxLightCount = 16;
	currentLightCount = 0;

	//	Create the Light Textures And Framebuffers.
	createLightTexturesAndFramebuffers();

}

//	Default LightsModule Destructor.
LightsModule::~LightsModule()
{

}

//	Add a Light.
void LightsModule::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(newLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{
		throw "Light Module Error: Add Light. Light with specified name already exists!";
	}
	else
	{
		if (currentLightCount >= maxLightCount)
		{
			throw "Light Module Error: Add Light. Maximum Number of Lights Exceeded!";
		}
		else
		{
			//	Add the Light Module Meta Data.
			mapNameToLightModuleMetaDataIndex[newLightName] = currentLightCount;

			lightModuleMetaDatas[currentLightCount].lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
			lightModuleMetaDatas[currentLightCount].lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
			lightModuleMetaDatas[currentLightCount].lightPosition = newLightData->lightPosition;
			lightModuleMetaDatas[currentLightCount].lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
			lightModuleMetaDatas[currentLightCount].lightConeDirection = newLightData->lightConeDirection;
			lightModuleMetaDatas[currentLightCount].spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;

			currentLightCount++;
		}
	}
}

//	Update a Light.
void LightsModule::updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(currentLightName);

	//	Check for an existing light.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{

		//	Get the Index of the Light.
		unsigned int lightIndex = lightModulei->second;

		lightModuleMetaDatas[lightIndex].lightEnabledShadowLightType = newLightData->lightEnabledShadowLightType;
		lightModuleMetaDatas[lightIndex].lightColorAndLightIntensity = newLightData->lightColorAndLightIntensity;
		lightModuleMetaDatas[lightIndex].lightPosition = newLightData->lightPosition;
		lightModuleMetaDatas[lightIndex].lightDistanceAttenuation = newLightData->lightDistanceAttenuation;
		lightModuleMetaDatas[lightIndex].lightConeDirection = newLightData->lightConeDirection;
		lightModuleMetaDatas[lightIndex].spotCosCutOffAndExponent = newLightData->spotCosCutOffAndExponent;

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

	//	Find the Index of the Light Module Meta Data.
	auto lightModulei = mapNameToLightModuleMetaDataIndex.find(deadLightName);

	//	Check if the Light exists.
	if (lightModulei != mapNameToLightModuleMetaDataIndex.end())
	{
		unsigned int lightIndex = lightModulei->second;
		lightModuleMetaDatas[lightIndex].lightEnabledShadowLightType = glm::vec4(0.0);

		mapNameToLightModuleMetaDataIndex.erase(lightModulei);
	}
	else
	{
		//	Throw an Error.
		throw "Light Module Error: Delete Light. Light with specified name does not exist!";
	}
}


//	Create the Light Textures and Framebuffers
void LightsModule::createLightTexturesAndFramebuffers()
{
	for (unsigned int i = 0; i < maxLightCount; i++)
	{

		//	Create the new Light Module Meta Data, and add it to the array.
		LightModuleMetaData newLightModuleMetaData;

		//	Generate the Color and Depth Textures.
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


		//	Add the Light Module Meta Data.
		lightModuleMetaDatas.push_back(newLightModuleMetaData);

	}
}
