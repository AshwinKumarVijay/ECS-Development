#pragma once

#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\matrix_inverse.hpp"

#include "../Renderer/Renderer.h"
#include "../RenderableManager/RenderableManager.h"
#include "../VAOManager/VAOManager.h"


class BasicRenderer : public Renderer
{

public:
	
	//	Default BasicRenderer Constructor.
	BasicRenderer();

	//	Default BasicRenderer Destructor.
	virtual ~BasicRenderer();

	//	Initialize the Renderer.
	virtual void initializeRenderer();

	//	Create a Renderable and Return the associated RenderableID.
	virtual long int createRenderable();
	
	//	View the associated Renderable.
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const;

	//	Update the Shader Type associated with the specified RenderableID.
	virtual void updateShadingType(const long int & renderableID, ShadingTypes::ShadingType newShadingType);
	//	Update the Geometry Type associated with the specified RenderableID.
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometryType);	
	//	Update the Material Type associated with the specified RenderableID.
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterialType);
	//	Update the Transform Matrix associated with the specified RenderableID.
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix);

	//	Render the BasicRenderer!
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Remove the specified Renderable.
	virtual void removeRenderable(const long int & renderableID);

	//	Clean Up the Renderer.
	virtual void cleanUpRenderer();

	//	Set the Active Camera.
	virtual void setActiveCamera(std::shared_ptr<const Camera> activeCamera);

	//	Return the Active Camera.
	virtual std::shared_ptr<Camera> getActiveCamera();

	//	Add Material to the Renderer.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	//	Update a Material in the Renderer.
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	//	Delete the Material in the Renderer.
	virtual void deleteMaterial(std::string deadMaterialName);

	//	Add Geometry to the Renderer.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	//	Update Geometry in the Renderer.
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	//	Delete Geometry in the Renderer.
	virtual void deleteGeometry(std::string deadGeometryName);

	//	Add a Shader to the Renderer.
	virtual void addShader(std::shared_ptr<ShaderData> newShaderData);
	//	Delete a Shader in the Renderer.
	virtual void deleteShader(std::string deadShaderName);

	//	Add a Light to the Renderer.
	virtual void addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData);
	//	Update the Light in the Renderer.
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData);
	//	Delete the Light in the Renderer.
	virtual void deleteLight(std::string deadLightName);

	//	Add a Texture to the Renderer.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Update the Texture in the Renderer.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);
	//	Delete the Texture in the Renderer.
	virtual void deleteTexture(std::string deadTextureName);


private:

	//	Initialize the Rendering Hints.
	virtual void initializeRenderingHints();

	//	Initialize the Environment Maps.
	virtual void initializeBackgroundEnvironment();

	//	Update the Camera.
	virtual void updateCamera(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Scene.
	virtual void renderScene(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render the Background Environment.
	virtual void renderBackgroundEnvironment(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Render all the Renderables Using the Specified Shader Type.
	virtual void renderRenderablesOfShaderType(const RendererShaderData & rendererShaderData, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut Down the Environment Maps.
	virtual void destroyBackgroundEnvironment();

	//	Bind the Environment Maps.
	virtual void uploadBackgroundEnviroment(const RendererShaderData & rendererShaderData);
	//	Upload the Camera Data to the Shading Pipeline.
	virtual void uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance);
	//	Upload the Model Data to the Shading Pipeline.
	virtual void uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix);
	//	Upload the Material Data to the Shading Pipeline.
	virtual void uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity);
	//	Upload the Material Texture Data to the Shading Pipeline.
	virtual void uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap);
	//	Upload the Shader Light Data to the Shading Pipeline.
	virtual void uploadLightsData(const RendererShaderData & rendererShaderData);



	//	The list of Active Lights.
	std::vector<std::string> activeLights;

	//	The Renderable Storage associated with the Renderer.
	RenderableManager renderableManager;

	//	The Environment Cube Map Data.
	BackgroundEnvironmentData backgroundEnvironmentData;

	//	VAOManager.
	VAOManager vaoManager;

	//	The Camera used for Rendering.
	std::shared_ptr<Camera> activeCamera;

	//	The Width of the Window we are Rendering to.
	int windowScreenWidth;

	//	The Hieght of the Window we are Rendering to.
	int windowScreenHeight;
};

