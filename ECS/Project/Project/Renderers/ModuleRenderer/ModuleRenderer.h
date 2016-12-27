#pragma once
#include <memory>
#include <vector>

#include "../Renderer/Renderer.h"
#include "../Renderer/SceneMetaData.h"

class RenderableManager;
class RendererModule;


class GBufferModule;

class LightsModule;
class ShadowsModule;


//class DPassLightingModule;
//class FPassLightingModule;
//
//class SSAOModule;
//
//class GaussianBlurModule;
//class BloomModule;
//class HDRModule;


class ModuleRenderer : public Renderer
{

public:

	//	Default ModuleRenderer Constructor.
	ModuleRenderer();

	//	Default ModuleRenderer Destructor.
	virtual ~ModuleRenderer();

	//	Initialize the ModuleRenderer.
	virtual void initializeRenderer();

	//	Create the Renderable and return the RenderableID.
	virtual long int createRenderable();

	//	Return the const Renderable.
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const;

	//	Update the Renderable Shader Type.
	virtual void updateShadingType(const long int & renderableID, const std::string & newShaderType);
	//	Update the Renderable Geometry Type.
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometryName);
	//	Update the Renderable Material Type.
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterialName);
	//	Update the Renderable Transform Matrix.
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix);

	//	Render.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);


	//	Remove the Renderable.
	virtual void removeRenderable(const long int & renderableID);

	//	Clean Up the Renderer.
	virtual void cleanUpRenderer();

	//	Add the Material to the Renderer for use, under the Material Name.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	//	Update the Material in the Renderer, specified by the Material Name.
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	//	Delete the Material in the Renderer.
	virtual void deleteMaterial(std::string deadMaterialName);

	//	Add the Geometry to the Renderer for use, under the Geometry Name.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	//	Update the Geometry in the Renderer, specified by the Geometry Name.
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	//	Delete the Geometry.
	virtual void deleteGeometry(std::string deadGeometryName);

	//	Add Shader to the Renderer.
	virtual void addShader(std::shared_ptr<const ShaderData> newShaderData);
	//	Delete the Shader in the Renderer.
	virtual void deleteShader(std::string deadShaderName);

	//	Add the Light to the Renderer, under the name.
	virtual void addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData);
	//	Update the Light, as specified by the LightData.
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData);
	//	Delete the Light.
	virtual void deleteLight(std::string deadLightName);

	//	Add the Texture to the Renderer, under the name.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Update the Texture in the Renderer, specified by name.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Delete the Texture in the Renderer.
	virtual void deleteTexture(std::string deadTextureName);

	//	Return the Scene Quality.
	virtual const SceneQuality & getSceneQuality();

private:

	
	//	Initialize the Module Renderer.
	virtual void initializeModuleRenderer();

	//	Initialize the Modules.
	virtual void initializeModules();

	//	Render the G Buffer Module.
	virtual void renderGBufferModule();

	//	Render the Lights Module.
	virtual void renderLightsModule();

	//	Render the Shadows Module.
	virtual void renderShadowsModule();

	//	Render the Deferred Lighting Module.
	virtual void renderDeferredLightingModule();

	//	Render the Foward Lighting Module.
	virtual void renderForwardLightingModule();

	//	Renderer Framebuffers.
	std::map<std::string, std::shared_ptr<RendererPipelineFramebuffer>> rendererPipelineFramebuffers;

	//	Renderer Textures.
	std::map<std::string, std::shared_ptr<RendererPipelineTexture>> rendererPipelineTextures;

	//	Map Name to Renderables,
	std::map<std::string, std::shared_ptr<RendererModule>> mapNameToRendererModules;


	SceneQuality defaultSceneQuality;


	//	The Renderalbe Manager.
	std::shared_ptr<RenderableManager> renderableManager;

	//	The Renderer Noise Textures.
	std::shared_ptr<RendererNoiseTextures> rendererNoiseTextures;


	//	G-Buffer Module.
	std::shared_ptr<GBufferModule> gBufferModule;

	//	Lights Module.
	std::shared_ptr<LightsModule> lightsModule;

	//	Shadows Module.
	std::shared_ptr<ShadowsModule> shadowsModule;

	////	Deferred Pass Lighting Module.
	//std::shared_ptr<DPassLightingModule> dPassLightingModule;
	//
	////	Forward Pass Lighting Module.
	//std::shared_ptr<FPassLightingModule> fPassLightingModule;

	////	SSAO Module.
	//std::shared_ptr<SSAOModule> ssaoModule;
	//
	////	HDR Module.
	//std::shared_ptr<HDRModule> hdrModule;

	////	Bloom Module.
	//std::shared_ptr<BloomModule> bloomModule;
};

