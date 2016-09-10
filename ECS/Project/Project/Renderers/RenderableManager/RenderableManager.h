#pragma once

#include <vector>
#include <map>
#include <memory>

#include "glm\glm.hpp"

class Renderable;


class RenderableManager
{

public:
	
	//	Default RenderableManager Constructor.
	RenderableManager();

	//	Default RenderableManager Destructor.
	virtual ~RenderableManager();

	//	Create the Renderable and return the associated RenderableID.
	long int createRenderable();

	//	Return the Renderable associated with the specified RenderableID.
	std::shared_ptr<const Renderable> viewRenderable(const long int & currentRenderableID) const;

	//	Return the Renderable associated with the specified RenderableID.
	std::shared_ptr<Renderable> getRenderable(const long int & currentRenderableID);

	//	Return the map of the Shaders to the Geometry Types.
	const std::map<std::string, std::vector<std::string>> & getShaderAndGeometryTypes();

	//	Return the number of Renderables that use the Shader Type.
	int getShaderTypeRenderableNumber(const std::string & requestedShaderType);

	//	Return the number of Renderables that use both the Shader Type and the Renderables.
	int getShaderTypeGeometryTypeRenderableNumber(const std::string & requestedShaderType, const std::string & requestedGeometryType);

	//	Update the Shader Type associated with the specified Renderable ID.
	virtual void updateShaderType(const long int & currentRenderableID, const std::string & newShaderType);

	//	Update the Geometry Type associated with the specified Renderable ID.
	virtual void updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType);

	//	Update the Material Type associated with the specified Renderable ID.
	virtual void updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType);
	
	//	Update the Transform Matrix associated with the specified Renderable Id.
	virtual void updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix);

	//	View Renderables of Shader Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> viewRenderablesOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const;
	
	//	View Materials of Shader Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<std::string>> viewMaterialsOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const;

	//	View Transforms of Shader Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<glm::mat4>> viewTransformsOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const;

	//	Remove the Renderable specified by the Renderable ID.
	virtual void removeRenderable(const long int & currentRenderableID);

	//	Return the Renderables List.
	virtual std::shared_ptr<std::vector<std::shared_ptr<Renderable>>> getRenderablesList(std::pair<std::string, std::string> shaderTypeAndGeometryType);

	//	Return the Materials List.
	virtual std::shared_ptr<std::vector<std::string>> getMaterialsList(std::pair<std::string, std::string> shaderTypeAndGeometryType);

	//	Return the Transforms List.
	virtual std::shared_ptr<std::vector<glm::mat4>> getTransformsList(std::pair<std::string, std::string> shaderTypeAndGeometryType);


private:

	//	Add a Renderable to Renderable Storage.
	virtual void addRenderableToStorage(const long int & currentRenderableID);

	//	Remove a Renderable from Renderable Storage.
	virtual void removeRenderableFromStorage(const long int & currentRenderableID);

	//	Add a Geometry Type to the Shader Type Map.
	virtual void addGeometryTypeToShaderTypeMap(const std::string & newGeometryType, const std::string & requestedShaderType);

	//	Clean the Geometry Type to the Shader Type Map.
	virtual void cleanGeometryTypeToShaderTypeMap();

	//	A reference to the list of active renderables.
	std::vector<long int> activeRenderableIDs;

	//	A reference to the list of destroyed renderables.
	std::vector<long int> destroyedRenderableIDs;

	//	The last RenderableID.
	long int lastRenderableID;

	//	Map of IDs to Renderables.
	std::map<long int, std::shared_ptr<Renderable>> mapIDToRenderable;

	//	Map of the Shader Type to the Geometry that is used by the Renderables that have that shader.
	std::map<std::string, std::vector<std::string>> mapShaderTypeToGeometryTypes;

	//	Map the Shader Type and the Geometry Type to the Renderables that use both.
	std::map<std::pair<std::string, std::string>, std::shared_ptr<std::vector<std::shared_ptr<Renderable>>>> mapShaderTypeAndGeometryTypeToRenderables;

	//	Map the Shader Type and the Geometry Type to the Materials of the Renderables that use both.
	std::map<std::pair<std::string, std::string>, std::shared_ptr<std::vector<std::string>>> mapShaderTypeAndGeometryTypeToMaterials;

	//	Map the Shader Type and the Geometry Type to the Transforms of the Renderables that use both.
	std::map<std::pair<std::string, std::string>, std::shared_ptr<std::vector<glm::mat4>>> mapShaderTypeAndGeometryTypeToTransforms;
};

