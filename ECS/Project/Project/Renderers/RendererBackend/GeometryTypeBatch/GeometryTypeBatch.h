#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GL\glew.h"
#include "glm\glm.hpp"

class ShaderTypeBatch;
class MaterialTypeBatch;
class RenderablesOfType;
struct RenderableMetaData;
struct GeometryTypeMetaData;




class GeometryTypeBatch : public std::enable_shared_from_this<GeometryTypeBatch>
{

public:

	//	Default GeometryTypeBatch Constructor.
	GeometryTypeBatch(std::shared_ptr<ShaderTypeBatch> newShaderTypeBatch, std::shared_ptr<GeometryTypeMetaData> newGeometryTypeMetaData);

	//	Default GeometryTypeBatch Destructor.
	virtual ~GeometryTypeBatch();

	//	Return the ShaderTypeBatch this a part of.
	std::weak_ptr<ShaderTypeBatch> getShaderTypeBatch();

	//	Return the Geometry Type Meta Data this is a part of.
	std::weak_ptr<GeometryTypeMetaData> getGeometryTypeMetaData();

	//	Create the Material Type Batch for the provided Material Type.
	std::shared_ptr<MaterialTypeBatch> createMaterialTypeBatch(const std::string & newMaterialType);

	//	Return the Number of Material Type Batches.
	virtual int getMaterialTypeBatchesCount();

	//	Return the Material Type Batch corresponding to the requested Material Type.
	std::shared_ptr<MaterialTypeBatch> getMaterialTypeBatch(const std::string & requestedMaterialType);

	//	Update the Transform Matrix of the Renderable.
	virtual void updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable);

	//	Erase the Material Type Batch.
	virtual void eraseMaterialTypeBatch(const std::string & deadMaterialType);

private:

	//	Name of the Geometry Type, and the Meta Data it represents.
	std::string geometryType;

	//	The Shader Type Batch this is a part of.
	std::weak_ptr<ShaderTypeBatch> shaderTypeBatch;

	//	The Geometry Type Meta Data.
	std::weak_ptr<GeometryTypeMetaData> geometryTypeMetaData;

	//	Map the Material Type that are used with this Shader and Geometry, to the Renderables that use all three types.
	std::map<std::string, std::shared_ptr<MaterialTypeBatch>> mapMaterialTypeToMaterialTypeBatch;

};

