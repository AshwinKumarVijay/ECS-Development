#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GL\glew.h"
#include "glm\glm.hpp"

#include "../RenderablesMetaData.h"


class ShaderTypeBatch;
class GeometryTypeBatch;
class MaterialTypeBatch;

//	
class RendererBackend : public std::enable_shared_from_this<RendererBackend>
{

public:
	
	//	Default RendererBackend Constructor.
	RendererBackend();

	//	Default RendererBackend Destructor.
	virtual ~RendererBackend();

	//	Return the ID of the newly created renderable.
	virtual long int createRenderable();

	//	Return the const Renderable associated with the specified RenderableID
	std::shared_ptr<const Renderable> viewRenderable(const long int & currentRenderableID) const;

	//	Return the Renderables that use this Renderable Type Keys.
	std::shared_ptr<const RenderablesOfType> viewRenderablesOfType(const RenderableType & renderableTypeKeys) const;

	//	Return the Shader Type Batch associated with the specified ShaderType.
	std::shared_ptr<const ShaderTypeBatch> viewShaderTypeBatch(const std::string & requestedShaderTypeBatch) const;

	//	Update the Shading Type associated with the specified Renderable ID.
	virtual void updateShadingType(const long int & currentRenderableID, const std::string & newShadingType);

	//	Update the Geometry Type associated with the specified Renderable ID.
	virtual void updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType);

	//	Update the Material Type associated with the specified Renderable ID.
	virtual void updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType);

	//	Update the Transform Matrix associated with the specified Renderable ID.
	virtual void updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix);

	//	Remove the Renderable specified by the Renderable ID.
	virtual void removeRenderable(const long int & deadRenderable);

		//	Add the Geometry Type.
	virtual void addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryData);

	//	Update the Geometry Type.
	virtual void updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData);

	//	Remove the Geometry Type.
	virtual void removeGeometryType(std::string deadGeometryType);

	//	Get the VAOID asssociated with the requested Geometry Type.
	virtual int getGeometryTypeVAOID(const std::string& requestedGeometryType) const;

	//	Get the MetaData, and the VAOID.
	virtual std::shared_ptr<GeometryTypeMetaData> getGeometryTypeVAOIDAndGeometryTypeMetaData(const std::string& requestedGeometryType, int & VAOID) const;

private:

	//	Add a new renderable to the list of renderables.
	virtual void addRenderable(const long int & currentRenderableID);

	//	Add the RenderableMetaData.
	virtual void addRenderableMetaData(const std::shared_ptr<RenderableMetaData> newRenderableInfo);

	//	Remove the RenderableMetaData.
	virtual void removeRenderableMetaData(const long int & currentRenderableID);

	//	Return the Shader Type Batch.
	virtual std::shared_ptr<ShaderTypeBatch> getShaderTypeBatch(const std::string & requestShaderType);

	//	Map of the Shaders to the Associated Geometry Meta Data.
	std::map<std::string, std::shared_ptr<ShaderTypeBatch>> mapShaderTypesToShaderTypeBatch;

	//	The Map of the Renderable Type to the Renderables of that Type.
	std::map<RenderableType, std::shared_ptr<RenderablesOfType>> mapRenderableTypeToRenderables;

	//	The Map of the Renderable IDs to the Renderable Type and its position in that list.
	std::map<long int, std::shared_ptr<RenderableMetaData>> mapRenderableIDToRenderableMetaData;

	//	Map Geometry Type to the Geometry Meta Data.
	std::map<std::string, std::shared_ptr<GeometryTypeMetaData>> mapGeometryTypeToGeometryMetaData;

	//	The list of active renderable IDs.
	std::vector<long int> activeRenderables;

	//	The list of inactive renderable IDs.
	std::vector<long int> inactiveRenderables;

	//	The default initialization values for the Shader, Geometry and Material Types.
	std::string defaultShaderType;
	std::string defaultGeometryType;
	std::string defaultMaterialType;

};

