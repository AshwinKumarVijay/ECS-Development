#include "ShaderTypeBatch.h"
#include "../../RenderablesMetaData.h"
#include "../RendererBackend.h"
#include "../GeometryTypeBatch/GeometryTypeBatch.h"

//	Default ShaderTypeBatch Constructor.
ShaderTypeBatch::ShaderTypeBatch(std::shared_ptr<RendererBackend> newRendererBackend, const std::string & newShaderType)
{
	rendererBackend = newRendererBackend;
	shaderType = newShaderType;
}

//	Default ShaderTypeBatch Destructor.
ShaderTypeBatch::~ShaderTypeBatch()
{

}

//	Return the number of Geometry Types this Shader has.
int ShaderTypeBatch::getGeometryTypeBatchesCount()
{
	return mapNamesToVaoIDGeometryTypeKeys.size();
}

//	Return the specified Geometry Type Meta Data, that is associated with this Shader Data, in a const form.
std::shared_ptr<const GeometryTypeBatch> ShaderTypeBatch::viewGeometryTypeMetaData(const std::string & requestedGeometryType) const
{
	//	Find the Key with this Geometry Type.
	auto currentVAOIDGeometryTypeKey = mapNamesToVaoIDGeometryTypeKeys.find(requestedGeometryType);

	//	Check if it exists.
	if (currentVAOIDGeometryTypeKey != mapNamesToVaoIDGeometryTypeKeys.end())
	{
		//	Find the Shader Type Sub Geometry Type Meta Data.
		auto currentGeometryTypeBatch = mapVAOIDsAndGeometryKeysToGeometryTypeBatches.find(currentVAOIDGeometryTypeKey->second);

		//	Check if it exists.
		if (currentGeometryTypeBatch != mapVAOIDsAndGeometryKeysToGeometryTypeBatches.end())
		{
			//	Return the Current Shader Type and Geometry Type Meta Data.
			return currentGeometryTypeBatch->second;
		}
		else
		{
			//	Return NULL.
			return NULL;
		}
	}
	else
	{
		//	Return NULL otherwise.
		return NULL;
	}
}

//	Return the specified Geometry Type Meta Data, that is associated with this Shader Data.
std::shared_ptr<GeometryTypeBatch> ShaderTypeBatch::getGeometryTypeBatch(const std::string & requestedGeometryType)
{
	//	Find the Key with this Geometry Type.
	auto currentVAOIDGeometryTypeKey = mapNamesToVaoIDGeometryTypeKeys.find(requestedGeometryType);

	//	Check if it exists.
	if (currentVAOIDGeometryTypeKey != mapNamesToVaoIDGeometryTypeKeys.end())
	{
		//	Find the Shader Type Sub Geometry Type Meta Data.
		auto currentGeometryTypeBatch = mapVAOIDsAndGeometryKeysToGeometryTypeBatches.find(currentVAOIDGeometryTypeKey->second);
		
		//	Check if it exists.
		if (currentGeometryTypeBatch != mapVAOIDsAndGeometryKeysToGeometryTypeBatches.end())
		{
			//	Return the Current Shader Type and Geometry Type Meta Data.
			return currentGeometryTypeBatch->second;
		}
		else
		{
			//	Return NULL.
			return NULL;
		}
	}
	else
	{
		//	Return NULL.
		return NULL;
	}
}

//	Return an exisiting ShaderTypeSubGeometryMetaData if available, or create one and return it.
std::shared_ptr<GeometryTypeBatch> ShaderTypeBatch::createGeometryTypeBatch(const std::string & requestedGeometryType)
{
	//	Check for an existing ShaderTypeSubGeometryTypeData
	auto existingShaderTypeSubGeometryTypeData = getGeometryTypeBatch(requestedGeometryType);

	//	
	if(existingShaderTypeSubGeometryTypeData != NULL)
	{
		//	Return it if it exists.
		return existingShaderTypeSubGeometryTypeData;
	}
	else
	{
		//	Get the Geometry VAO ID, and the Meta Data of the Requested Geometry.
		auto activeRendererBackend = rendererBackend.lock();

		int VAOID = -1;
		std::shared_ptr<GeometryTypeMetaData> geometryTypeMetaData = activeRendererBackend->getGeometryTypeVAOIDAndGeometryTypeMetaData(requestedGeometryType, VAOID);

		//	Check if this is a valid VAOID.
		if (geometryTypeMetaData != NULL)
		{
			//	Construct the VAOIDGeometryType Key.
			VAOIDGeometryTypeKey newKey;
			newKey.geometryType = requestedGeometryType;
			newKey.vaoID = VAOID;

			//	Construct the New GeometryTypeBatch.
			auto newGeometryTypeBatch = std::make_shared<GeometryTypeBatch>(this->shared_from_this(), geometryTypeMetaData);

			//	Create the entries for the ShaderTypeSubGeometryType Data.
			mapVAOIDsAndGeometryKeysToGeometryTypeBatches[newKey] = newGeometryTypeBatch;
			
			//	
			mapNamesToVaoIDGeometryTypeKeys[requestedGeometryType] = newKey;

			//	
			return newGeometryTypeBatch;
		}
		else
		{
			//	Error!
			return NULL;
		}
	}
}

//	Erase the GeometryTypeBatch if it is empty.
void ShaderTypeBatch::eraseGeometryTypeBatch(const std::string & deadGeometryTypeBatch)
{
	//	Find the Key with this Geometry Type.
	auto currentVAOIDGeometryTypeKey = mapNamesToVaoIDGeometryTypeKeys.find(deadGeometryTypeBatch);

	//	Check if it exists.
	if (currentVAOIDGeometryTypeKey != mapNamesToVaoIDGeometryTypeKeys.end())
	{
		//	Find the Shader Type Sub Geometry Type Meta Data.
		auto currentGeometryTypeBatch = mapVAOIDsAndGeometryKeysToGeometryTypeBatches.find(currentVAOIDGeometryTypeKey->second);

		//	Check if it exists.
		if (currentGeometryTypeBatch != mapVAOIDsAndGeometryKeysToGeometryTypeBatches.end())
		{
			if (currentGeometryTypeBatch->second->getMaterialTypeBatchesCount() == 0)
			{
				mapVAOIDsAndGeometryKeysToGeometryTypeBatches.erase(currentGeometryTypeBatch);
				mapNamesToVaoIDGeometryTypeKeys.erase(currentVAOIDGeometryTypeKey);
			}
		}
	}
}

//	Return the Map Of VAOIDsAnd GeometryKeys To GeometryTypes.
const std::map<VAOIDGeometryTypeKey, std::shared_ptr<GeometryTypeBatch>>& ShaderTypeBatch::getMapOfVAOIDsAndGeometryKeysToGeometryTypes()
{
	return mapVAOIDsAndGeometryKeysToGeometryTypeBatches;
}

//	Return the ShaderType associated with this ShaderTypeBatch.
std::string ShaderTypeBatch::getShaderType() const
{
	return shaderType;
}



