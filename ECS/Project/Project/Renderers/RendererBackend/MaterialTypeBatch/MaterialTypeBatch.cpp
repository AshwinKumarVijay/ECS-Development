#include "MaterialTypeBatch.h"
#include "../GeometryTypeBatch/GeometryTypeBatch.h"
#include "../ShaderTypeBatch/ShaderTypeBatch.h"
#include "../RenderablesOfType/RenderablesOfType.h"

//	Default MaterialTypeBatch Constructor.
MaterialTypeBatch::MaterialTypeBatch(std::shared_ptr<GeometryTypeBatch> newGeometryTypeBatch, const std::string & newMaterialType)
{
	//	Create the new Material Type.
	materialType = newMaterialType;

	//	Create the new Geometry Type Batch.
	geometryTypeBatch = newGeometryTypeBatch;

	//	Create the new Renderables of Type.
	renderablesOfType = std::make_shared<RenderablesOfType>(RenderableType(newGeometryTypeBatch->getShaderTypeBatch().lock()->getShaderType(), newGeometryTypeBatch->getGeometryTypeMetaData().lock()->geometryType, newMaterialType));
}

//	Default MaterialTypeBatch Destructor.
MaterialTypeBatch::~MaterialTypeBatch()
{

}


//	Add Renderable to Renderables.
void MaterialTypeBatch::addRenderable(std::shared_ptr<RenderableMetaData> newRenderableMetaData)
{
	renderablesOfType->addRenderable(newRenderableMetaData);
}

//	Update the Transform Matrix.
void MaterialTypeBatch::updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable)
{
	if (updatedRenderable->renderableType->materialType == materialType)
	{
		renderablesOfType->updateTransformMatrix(updatedRenderable);
	}
}

std::shared_ptr<RenderablesOfType> MaterialTypeBatch::getRenderablesOfType()
{
	return renderablesOfType;
}


//	Remove Renderable From Renderables.
void MaterialTypeBatch::removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderableMetaData)
{
	renderablesOfType->removeRenderable(deadRenderableMetaData);
}


