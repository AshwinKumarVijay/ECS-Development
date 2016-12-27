#include "ModuleRenderer.h"
#include "../RenderableManager/RenderableManager.h"
#include "../RendererModules/RendererModule.h"
#include "../RendererModules/GBufferModule/GBufferModule.h"
#include "../RendererModules/LightsModule/LightsModule.h"
#include "../RendererModules/ShadowsModule/ShadowsModule.h"

//	Default ModuleRenderer Constructor.
ModuleRenderer::ModuleRenderer()
{
	defaultSceneQuality.screenWidth = 1920;
	defaultSceneQuality.screenHeight = 1080;

	defaultSceneQuality.bloomBlur = 1;
	defaultSceneQuality.bloomThreshold = 1;

	defaultSceneQuality.ssaoQuality = 1;
	defaultSceneQuality.shadowSize = 2048;
}

//	Default ModuleRenderer Destructor.
ModuleRenderer::~ModuleRenderer()
{

}

//	Initialize the ModuleRenderer.
void ModuleRenderer::initializeRenderer()
{
	//	initialize the Modeule Renderer.
	initializeModuleRenderer();
}

//	Create the Renderable and return the RenderableID.
long int ModuleRenderer::createRenderable()
{
	return renderableManager->createRenderable();
}

//	View the Renderable associated.
std::shared_ptr<const Renderable> ModuleRenderer::viewRenderable(const long int & renderableID) const
{
	return renderableManager->viewRenderable(renderableID);
}


//	Update the Renderable Shader Type.
void ModuleRenderer::updateShadingType(const long int & renderableID, const std::string & newShaderType)
{
	renderableManager->updateShadingType(renderableID, newShaderType);
}

//	Update the Renderable Geometry Type.
void ModuleRenderer::updateGeometryType(const long int & renderableID, const std::string & newGeometryName)
{
	renderableManager->updateGeometryType(renderableID, newGeometryName);
}

//	Update the Renderable Material Type.
void ModuleRenderer::updateMaterialType(const long int & renderableID, const std::string & newMaterialName)
{
	renderableManager->updateMaterialType(renderableID, newMaterialName);
}

//	Update the Renderable Transform Matrix.
void ModuleRenderer::updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix)
{
	renderableManager->updateTransformMatrix(renderableID, newModelMatrix);
}

//	Render the Scene.
void ModuleRenderer::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	gBufferModule->renderToGBuffer();
}

//	Remove the Renderable.
void ModuleRenderer::removeRenderable(const long int & renderableID)
{
	renderableManager->removeRenderable(renderableID);
}

//	Clean Up the Renderer.
void ModuleRenderer::cleanUpRenderer()
{


}

//	Add the Material to the Renderer for use, under the Material Name.
void ModuleRenderer::addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::addMaterial(newMaterialName, newMaterialData);
	renderableManager->addMaterialType(newMaterialName);
}

//	Update the Material in the Renderer, specified by the Material Name.
void ModuleRenderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void ModuleRenderer::deleteMaterial(std::string deadMaterialName)
{
	renderableManager->removeMaterialType(deadMaterialName);
	Renderer::deleteMaterial(deadMaterialName);
}

//	Add the Geometry to the Renderer for use, under the Geometry Name.
void ModuleRenderer::addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::addGeometry(newGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Adding Geometry Data Error -> " << err << std::endl;
	}

	renderableManager->addGeometryType(getGeometryManager()->getGeometry(newGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Adding Geometry Data Error -> " << err2 << std::endl;
	}

}

//	Update the Geometry in the Renderer, specified by the Geometry Name.
void ModuleRenderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::updateGeometry(currentGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Updating Geometry Data Error -> " << err << std::endl;
	}


	renderableManager->updateGeometryType(getGeometryManager()->getGeometry(currentGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Updating Geometry Data Error -> " << err2 << std::endl;
	}
}

//	Delete the Geometry.
void ModuleRenderer::deleteGeometry(std::string deadGeometryName)
{
	renderableManager->removeGeometryType(getGeometryManager()->getGeometry(deadGeometryName));

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Deleting Geometry Data Error -> " << err << std::endl;
	}


	Renderer::deleteGeometry(deadGeometryName);

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Deleting Geometry Data Error -> " << err2 << std::endl;
	}
}

//	Add Shader to the Renderer.
void ModuleRenderer::addShader(std::shared_ptr<const ShaderData> newShaderData)
{
	Renderer::addShader(newShaderData);
	std::string shaderType;
	newShaderData->findProperty("Shader Name", shaderType);
	renderableManager->addShaderType("OPAQUE_BASIC");

}

//	Delete the Shader in the Renderer.
void ModuleRenderer::deleteShader(std::string deadShaderName)
{
	renderableManager->removeShaderType(getShaderManager()->viewShaderData(deadShaderName)->shaderType);
	Renderer::deleteShader(deadShaderName);
}

//	Add a Light.
void ModuleRenderer::addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData)
{
	//	Add the LightData under the specified name.
	Renderer::addLight(newLightName, newLightData);
	lightsModule->addLight(newLightName, getLightManager()->viewLight(newLightName));

}

//	Update the Light.
void ModuleRenderer::updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData)
{
	Renderer::updateLight(currentLightName, newLightData);
	lightsModule->updateLight(currentLightName, getLightManager()->viewLight(currentLightName));
}

//	Delete the Light.
void ModuleRenderer::deleteLight(std::string deadLightName)
{
	//	Delete the Light from the Lights.
	Renderer::deleteLight(deadLightName);
	lightsModule->deleteLight(deadLightName);
}

//	Add the Texture to the Renderer, under the name.
void ModuleRenderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::addTexture(newTextureName, newTextureData);
}

//	Update the Texture in the Renderer, specified by name.
void ModuleRenderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::updateTexture(currentTextureName, newTextureData);
}

//	Delete the Texture in the Renderer.
void ModuleRenderer::deleteTexture(std::string deadTextureName)
{
	Renderer::deleteTexture(deadTextureName);
}

//	Return the Scene Quality.
const SceneQuality & ModuleRenderer::getSceneQuality()
{
	return defaultSceneQuality;
}

//	Initialize the Module Renderer.
void ModuleRenderer::initializeModuleRenderer()
{

}

//	Initialize the Modules.
void ModuleRenderer::initializeModules()
{
	//	Create the GBuffer Module.
	gBufferModule = std::make_shared<GBufferModule>(this->shared_from_this());

	//	Create the Lights Module.
	lightsModule = std::make_shared<LightsModule>(this->shared_from_this());

	shadowsModule = std::make_shared<ShadowsModule>(this->shared_from_this(), lightsModule);

	////	SSAO Module.
	//ssaoModule = std::make_shared<SSAOModule>(renderableManager);

	////	Create the Deferred Pass Lighting Module.
	//dPassLightingModule = std::make_shared<DPassLightingModule>(lightsModule, ssaoModule);

	////	Create the Forward Pass Lighting Module.
	//fPassLightingModule = std::make_shared<FPassLightingModule>(renderableManager, dPassLightingModule);

	////	Bloom Module
	//bloomModule = std::make_shared<BloomModule>();

	////	HDR Module.
	//hdrModule = std::make_shared<HDRModule>();

}

//	Render the G Buffer Module.
void ModuleRenderer::renderGBufferModule()
{
	gBufferModule->renderToGBuffer();
}

//	Render the Lights Module.
void ModuleRenderer::renderLightsModule()
{
}

//	Render the Shadows Module.
void ModuleRenderer::renderShadowsModule()
{

}

//	Render the Deferred Lighting Module.
void ModuleRenderer::renderDeferredLightingModule()
{

}

//	Render the Forward Lighting Module.
void ModuleRenderer::renderForwardLightingModule()
{

}


