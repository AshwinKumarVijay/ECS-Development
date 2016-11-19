#pragma once
#include <memory>
#include <set>
#include <map>

class RendererBackend;
class GeometryTypeBatch;

#include "../../RenderablesMetaData.h"


class ShaderTypeBatch : public std::enable_shared_from_this<ShaderTypeBatch>
{
public:
	
	//	Default ShaderTypeBatch Constructor.
	ShaderTypeBatch(std::shared_ptr<RendererBackend> newRendererBackend, const std::string & newShaderType);
	
	//	Default ShaderTypeBatch Destructor.
	virtual ~ShaderTypeBatch();

	//	Return the number of Geometry Type Batches this has.
	virtual int getGeometryTypeBatchesCount();

	//	Return the specified Geometry Type Meta Data, that is associated with this Shader Data, in a const form.
	virtual std::shared_ptr<const GeometryTypeBatch> viewGeometryTypeMetaData(const std::string & requestedGeometryType) const;

	//	Return the specified Geometry Type Meta Data, that is associated with this Shader Data.
	virtual std::shared_ptr<GeometryTypeBatch> getGeometryTypeBatch(const std::string & requestedGeometryType);

	//	Create and Return the GeometryTypeBatch.
	virtual std::shared_ptr<GeometryTypeBatch>  createGeometryTypeBatch(const std::string & requestedGeometryType);

	//	Erase the GeometryTypeBatch if it is empty.
	virtual void  eraseGeometryTypeBatch(const std::string & deadGeometryTypeBatch);
	
	//	Return the Map of VAOIDs and Geometry Keys to the Geometry Types.
	virtual const std::map<VAOIDGeometryTypeKey, std::shared_ptr<GeometryTypeBatch>>& getMapOfVAOIDsAndGeometryKeysToGeometryTypes();

	//	Return the ShaderType associated with this ShaderTypeBatch.
	virtual std::string getShaderType() const;

private :

	//	Return the string associated with this ShaderTypeBatch.
	std::string shaderType;

	//	The Renderable Types of this Shader.
	std::set<RenderableType> renderableTypes;

	//	The list of the Geometry Meta Datas that the Shader uses, ordered by VAO ID, and then by Name.
	std::map<VAOIDGeometryTypeKey, std::shared_ptr<GeometryTypeBatch>> mapVAOIDsAndGeometryKeysToGeometryTypeBatches;
	std::map<std::string, VAOIDGeometryTypeKey> mapNamesToVaoIDGeometryTypeKeys;

	//	The Renderer Backed this Batch is a part of.
	std::weak_ptr<RendererBackend> rendererBackend;
};