#pragma once
#include <memory>
#include <string>


class ShaderTypeBatch;
class GeometryTypeBatch;
class RenderablesOfType;
struct RenderableMetaData;
struct MaterialTypeMetaData;

class MaterialTypeBatch : public std::enable_shared_from_this<MaterialTypeBatch>
{


public:
	
	//	Default MaterialTypeBatch Constructor.
	MaterialTypeBatch(std::shared_ptr<GeometryTypeBatch> newGeometryTypeBatch, const std::string & newMaterialType);

	//	Default MaterialTypeBatch Destructor.
	virtual ~MaterialTypeBatch();

	//	Add Renderable to Renderables.
	virtual void addRenderable(std::shared_ptr<RenderableMetaData> newRenderableMetaData);

	//	Update the Transform Matrix of the Renderable.
	virtual void updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable);

	//	Return the Renderables that this MaterialTypeBatch holds.
	std::shared_ptr<RenderablesOfType> getRenderablesOfType();

	//	Remove Renderable From Renderables.
	virtual void removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderableMetaData);

private:

	//	Material Type Batch.
	std::string materialType;

	//	The Geometry Type Batch this is a part of.
	std::weak_ptr<GeometryTypeBatch> geometryTypeBatch;

	//	The Type of Renderables this stores.
	std::shared_ptr<RenderablesOfType> renderablesOfType;

	//	The Material Type Meta Data.
	std::shared_ptr<MaterialTypeMetaData> materialTypeMetaData;
};

