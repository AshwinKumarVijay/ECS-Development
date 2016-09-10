#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\matrix_inverse.hpp"

#include "RenderingCommands.h"

#include "../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../Resources/ResourceData/LightData/LightData.h"
#include "../Resources/ResourceData/MaterialData/MaterialData.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"

#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"
#include "../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../RendererResourceManagers/RendererMaterialManager/RendererMaterialManager.h"
#include "../RendererResourceManagers/RendererTextureManager/RendererTextureManager.h"
#include "../RendererResourceManagers/RendererShaderManager/RendererShaderManager.h"

class Configuration;
class Renderable;
class Transform;
class Camera;

class Renderer
{
public:

	/**

	Name: Renderer
	Parameters: -
	Purpose: Default Renderer Constructor
	Return Value: -
	Other Output: -

	*/
	Renderer();


	/**

	Name: Renderer
	Parameters: -
	Purpose: Default Renderer Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~Renderer();


	/**

	Name: initializeRenderer
	Parameters: -
	Purpose: Miscellaneous set up of the Renderer.
	Return Value: -
	Other Output: -

	*/
	virtual void initializeRenderer() = 0;


	/**

	Name: createRenderable
	Parameters: -
	Purpose: -
	Return Value: 
	- (long int) - The ID of the associated Renderable.
	Other Output: -

	*/
	virtual long int createRenderable() = 0;


	/**

	Name: viewRenderable
	Parameters:
	- "renderableID" - (long int) (const) (&) - The ID specifying the renderable to view.
	Purpose: -
	Return Value:
	- (shared_ptr<const Renderable>) - Return the associated Renderable
	Other Output: -

	*/
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const = 0;


	virtual void updateShaderType(const long int & renderableID, const std::string & newShaderType) = 0;
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometry) = 0;
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterial) = 0;
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix) = 0;


	/**

	Name: render
	Parameters:
	- "deltaTime" - (float) (const) (&) - The time between frames.
	- "currentFrameTime" - (float) (const) (&) - The currentFrameTime.
	- "lastFrameTime" - (float) (const) (&) - The lastFrameTime.
	Purpose: Render!
	Return Value: -
	Other Output: -

	*/
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime) = 0;


	/**

	Name: removeRenderable
	Parameters:
	- "renderableID" - (int) (const) (&) - The ID specifying the renderable to remove.
	Purpose: Removes the renderable from the renderer, meaning that it will not be rendered any more.
	Return Value: -
	Other Output: -

	*/
	virtual void removeRenderable(const long int & renderableID) = 0;


	/**

	Name: cleanUpRenderer
	Parameters: -
	Purpose: Miscellaneous clean up of the Renderer.
	Return Value: -
	Other Output: -

	*/
	virtual void cleanUpRenderer() = 0;


	/**

	Name: setActiveCamera
	Parameters:
	- "activeCamera" - (shared_ptr<Camera>) - The pointer to the new activeCamera.
	Purpose: Check whether the Framebuffer currently attached is correctly.
	Return Value: -
	Other Output: -

	*/
	virtual void setActiveCamera(std::shared_ptr<const Camera> activeCamera) = 0;


	/**

	Name: getActiveCamera
	Parameters: -
	Purpose: Return a pointer to the Camera currently being used by the renderer.
	Return Value:
	- (shared_ptr<Camera>) - Pointer to the active camera.
	Other Output: -

	*/
	virtual std::shared_ptr<Camera> getActiveCamera() = 0;

	//	Add Comments - TO DO
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData);
	virtual void deleteMaterial(std::string deadMaterialName);

	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData);
	virtual void deleteGeometry(std::string deadGeometryName);

	virtual void addShader(std::shared_ptr<const ShaderData> newShaderData);
	virtual void deleteShader(std::string deadShaderName);

	virtual void addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData);
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData);
	virtual void deleteLight(std::string deadLightName);

	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);
	virtual void deleteTexture(std::string deadTextureName);

protected:


	/**

	Name: setShaderManager
	Parameters:
	- (shared_ptr<ShaderManager>) - The new ShaderManager.
	Purpose: Set the ShaderManager of the Renderer
	Return Value: -
	Other Output: -

	*/
	void setShaderManager(std::shared_ptr<RendererShaderManager> newShaderManager);

	/**

	Name: getShaderManager
	Parameters: -
	Purpose: -
	Return Value:
	- (shared_ptr<ShaderManager>) - Return the associated ShaderManager.
	Other Output: -

	*/
	std::shared_ptr<RendererShaderManager> getShaderManager();

	

	/**

	Name: setTextureManager
	Parameters:
	- (shared_ptr<TextureManager>) - The new TextureManager.
	Purpose: Set the TextureManager of the Renderer
	Return Value: -
	Other Output: -

	*/
	void setTextureManager(std::shared_ptr<RendererTextureManager> newTextureManager);

	/**

	Name: getTextureManager
	Parameters: -
	Purpose: -
	Return Value:
	- (shared_ptr<TextureManager>) - Return the associated TextureManager.
	Other Output: -

	*/
	std::shared_ptr<RendererTextureManager> getTextureManager();

	/**

	Name: setGeometryManager
	Parameters:
	- (shared_ptr<GeometryManager>) - The new GeometryManager.
	Purpose: Set the GeometryManager of the Renderer
	Return Value: -
	Other Output: -

	*/
	void setGeometryManager(std::shared_ptr<RendererGeometryManager> newGeometryManager);

	/**

	Name: getGeometryManager
	Parameters: -
	Purpose: -
	Return Value:
	- (shared_ptr<GeometryManager>) - Return the associated GeometryManager.
	Other Output: -

	*/
	std::shared_ptr<RendererGeometryManager> getGeometryManager();



	/**

	Name: setLightManager
	Parameters:
	- (shared_ptr<LightManager>) - The new LightManager.
	Purpose: Set the LightManager of the Renderer
	Return Value: -
	Other Output: -

	*/
	void setLightManager(std::shared_ptr<RendererLightManager> newLightManager);

	/**

	Name: getLightManager
	Parameters: -
	Purpose: -
	Return Value:
	- (shared_ptr<LightManager>) - Return the associated LightManager.
	Other Output: -

	*/
	std::shared_ptr<RendererLightManager> getLightManager();


	/**

	Name: setMaterialManager
	Parameters:
	- (shared_ptr<MaterialManager>) - The new MaterialManager.
	Purpose: Set the MaterialManager of the Renderer
	Return Value: -
	Other Output: -

	*/
	void setMaterialManager(std::shared_ptr<RendererMaterialManager> newMaterialManager);

	/**

	Name: getMaterialManager
	Parameters: -
	Purpose: -
	Return Value:
	- (shared_ptr<MaterialManager>) - Return the associated MaterialManager.
	Other Output: -

	*/
	std::shared_ptr<RendererMaterialManager> getMaterialManager();


private:
	
	//	The Associated ShaderManager.
	std::shared_ptr<RendererShaderManager> rendererShaderManager;

	//	The Associated MaterialManager.
	std::shared_ptr<RendererMaterialManager> rendererMaterialManager;

	//	The Associated LightManager.
	std::shared_ptr<RendererLightManager> rendererLightManager;

	//	The Associated GeometryManager.
	std::shared_ptr<RendererGeometryManager> rendererGeometryManager;

	//	The Associated TextureManager.
	std::shared_ptr<RendererTextureManager> rendererTextureManager;

};

