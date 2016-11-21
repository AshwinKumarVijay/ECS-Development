#include "GeometryTypeBatch.h"
#include "../ShaderTypeBatch/ShaderTypeBatch.h"
#include "../MaterialTypeBatch/MaterialTypeBatch.h"
#include "../RenderablesOfType/RenderablesOfType.h"
#include "../../Renderable/Renderable.h"

//	Default GeometryTypeBatch Constructor.
GeometryTypeBatch::GeometryTypeBatch(std::shared_ptr<ShaderTypeBatch> newShaderTypeBatch, std::shared_ptr<GeometryTypeMetaData> newGeometryTypeMetaData)
{
	shaderTypeBatch = newShaderTypeBatch;
	geometryTypeMetaData = newGeometryTypeMetaData;
}

//	Default GeometryTypeBatch Destructor.
GeometryTypeBatch::~GeometryTypeBatch()
{

}

//	Update the Transform Matrix of the specified Renderable.
void GeometryTypeBatch::updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable)
{
	//	Look for an existing batch with this Material Type.
	auto materialTypeBatch = mapMaterialTypeToMaterialTypeBatch.find(updatedRenderable->renderableType->materialType);

	//	Check if it exists.
	if (materialTypeBatch != mapMaterialTypeToMaterialTypeBatch.end())
	{
		materialTypeBatch->second->updateTransformMatrix(updatedRenderable);
	}
}

//	Return the number of Material Type Batches.
int GeometryTypeBatch::getMaterialTypeBatchesCount()
{
	return mapMaterialTypeToMaterialTypeBatch.size();
}

//	Return the Shader Type Batch.
std::weak_ptr<ShaderTypeBatch> GeometryTypeBatch::getShaderTypeBatch()
{
	return shaderTypeBatch;
}

//	Return the Geometry Type Meta Data related to this .
std::weak_ptr<GeometryTypeMetaData> GeometryTypeBatch::getGeometryTypeMetaData()
{
	return geometryTypeMetaData;
}

//	Return the Material Type Batch corresponding to the requested Material Type.
std::shared_ptr<MaterialTypeBatch> GeometryTypeBatch::getMaterialTypeBatch(const std::string & requestedMaterialType)
{
	//	Look for an existing batch with this Material Type.
	auto materialType = mapMaterialTypeToMaterialTypeBatch.find(requestedMaterialType);

	//	Check if it exists.
	if (materialType != mapMaterialTypeToMaterialTypeBatch.end())
	{
		return materialType->second;
	}
	else
	{
		//	Return NULL otherwise.
		return NULL;
	}
}

//	Create the Material Type Batch for the provided Material Type, or return the existing one.
std::shared_ptr<MaterialTypeBatch> GeometryTypeBatch::createMaterialTypeBatch(const std::string & newMaterialType)
{
	//	Look for an existing batch with this Material Type.
	auto exisitingMaterialType = getMaterialTypeBatch(newMaterialType);

	//	Check if we already have an existing material type.
	if (exisitingMaterialType != NULL)
	{
		return exisitingMaterialType;
	}
	else
	{
		//	Create the new Material Type,
		std::shared_ptr<MaterialTypeBatch> newMaterialTypeBatch = std::make_shared<MaterialTypeBatch>(this->shared_from_this(), newMaterialType);
	
		//	Insert the Material Type Batch into the Map.
		mapMaterialTypeToMaterialTypeBatch[newMaterialType] = newMaterialTypeBatch;

		//	Return the new Material Type Batch.
		return newMaterialTypeBatch;
	}
}

//	Erase the Material Type Batch.
void GeometryTypeBatch::eraseMaterialTypeBatch(const std::string & deadMaterialType)
{
	//	Look for an existing batch with this Material Type.
	auto materialType = mapMaterialTypeToMaterialTypeBatch.find(deadMaterialType);

	//	Check if it exists.
	if (materialType != mapMaterialTypeToMaterialTypeBatch.end())
	{
		//	Erase the Material Type Batch.
		mapMaterialTypeToMaterialTypeBatch.erase(materialType);
	}
}
