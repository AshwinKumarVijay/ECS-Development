#pragma once

#include "../Renderer/Renderer.h"
#include "../RenderableManager/RenderableManager.h"
#include "../VAOManager/VAOManager.h"
#include "../Sampler/Sampler.h"
#include "../RNGs/RNGs.h"


class BackgroundData;


class DeferredRenderer : public Renderer
{
public:

	//	Default Deferred Constructor.
	DeferredRenderer();

	//	Default Deferred Destructor.
	virtual ~DeferredRenderer();

	//	Initialize the Deferred Renderer.
	virtual void initializeRenderer();

	//	Create the Renderable and return the RenderableID.
	virtual long int createRenderable();

	//	Return the const Renderable.
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const;

	//	Update the Renderable Shader Type.
	virtual void updateShaderType(const long int & renderableID, const std::string & newShaderType);
	//	Update the Renderable Geometry Type.
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometryName);
	//	Update the Renderable Material Type.
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterialName);
	//	Update the Renderable Transform Matrix.
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix);

	//	Update the Camera.
	void updateCamera(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Remove the Renderable.
	virtual void removeRenderable(const long int & renderableID);

	//	Clean Up the Renderer.
	virtual void cleanUpRenderer();


	//	Set the Active Camera.
	virtual void setActiveCamera(std::shared_ptr<const Camera> activeCamera);

	//	Return the Active Camera.
	virtual std::shared_ptr<Camera> getActiveCamera();

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
	virtual void addShader(std::shared_ptr<ShaderData> newShaderData);
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


private:

	//	Initialize the Rendering Hints.
	virtual void initializeRenderingHints();

	//	Initialize the Background Data.
	virtual void initializeBackgroundEnvironment();

	//	Initialize the Deferred Rendering Textures.
	virtual void initializeDeferredRenderingTextures();

	//	Initialize the Deferred Rendering Framebuffers.
	virtual void initializeDeferredRenderingFramebuffers();

	//	Initialize the Deferred Rendering G Buffers.
	virtual void initializeDeferredRenderingGBufferTextures();

	//	Initialize the Deferred Rendering G Buffer Framebuffer.
	virtual void initializeDeferredRenderingGBufferFramebuffer();

	//	Initialize the Sampling Values.
	virtual void initializeSamplingValues();

	//	Initialize the Noise Textures.
	virtual void initializeNoiseTextures();

	//	Initialize the Lights.
	virtual void initializeLights();

	//	Render the Renderables that have to go through the Deferred Rendering Pipeline.
	virtual void renderDeferredRenderingPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Renderables that have to go through the Forward Rendering pipeline.
	virtual void renderForwardRenderingPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Post Process Pipeline.
	virtual void renderPostProcessPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Background.
	virtual void renderBackgroundEnvironment(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Renderables of the Shader Type.
	virtual void renderRenderablesOfShaderType(const RendererShaderData & rendererShaderData, const glm::mat4 & currentViewMatrix, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Shadow Maps.
	virtual void renderShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Bind the Environment Maps.
	virtual void uploadBackgroundEnviroment(const RendererShaderData & rendererShaderData);
	//	Upload the Camera Data to the Shader Pipeline.
	virtual void uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance);
	//	Upload the Model Data to the Shader Pipeline.
	virtual void uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix);
	//	Upload the Material Data to the Shading Pipeline.
	virtual void uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity);
	//	Upload the Material Texture Data to the Shading Pipeline.
	virtual void uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap);
	//	Upload the Shader Lights Data to the Shader Pipeline.
	virtual void uploadLightsData(const RendererShaderData & rendererShaderData);
	//	Upload the Sampling Data.
	virtual void uploadSamplingData(const RendererShaderData & rendererShaderData);
	//	Upload the Noise Textures.
	virtual void uploadNoiseTextures(const RendererShaderData & rendererShaderData);
	//	Upload the Post Process Textures.
	virtual void uploadPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureOneID, GLuint postProcessTextureTwoID, GLuint postProcessTextureThreeID, GLuint postProcessTextureFourID);

	//	Check the Framebuffer Status.
	virtual void checkFramebufferStatus();

	//	Destroy the associated Background Data.
	virtual void destroyBackgroundEnvironment();

	//	Destroy the Noise Textures.
	virtual void destroyNoiseTextures();

	//	The Names of the Active Lights.
	std::vector<std::string> activeLightNames;
	std::vector<std::shared_ptr<const RendererLightData>> activeLights;

	//	
	std::vector<GLuint> pointLightShadowMaps;
	std::vector<GLuint> lightShadowMaps;

	//	The Camera used for Rendering.
	std::shared_ptr<Camera> activeCamera;

	//	The Renderable Storage associated with the Renderer.
	RenderableManager renderableManager;

	//	The VAOManager.
	VAOManager vaoManager;
	
	//	The Sampler.
	std::shared_ptr<Sampler> sampler;

	//	The Environment Cube Map Data.
	BackgroundEnvironmentData backgroundEnvironmentData;

	//	The Noise Textures.
	RendererNoiseTextures rendererNoiseTextures;

	//	Renderer Framebuffers.
	std::map<std::string, std::shared_ptr<RendererPipelineFramebuffer>> rendererPipelineFramebuffers;

	//	Deferred Renderer Textures.
	std::map<std::string, std::shared_ptr<RendererPipelineTexture>> rendererPipelineTextures;

	//	The Width of the Window we are Rendering to.
	int windowScreenWidth;

	//	The Hieght of the Window we are Rendering to.
	int windowScreenHeight;

};

