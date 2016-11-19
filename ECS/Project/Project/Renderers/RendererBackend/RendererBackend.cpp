#include "RendererBackend.h"
#include "../Renderable/Renderable.h"
#include "ShaderTypeBatch\ShaderTypeBatch.h"
#include "GeometryTypeBatch\GeometryTypeBatch.h"
#include "MaterialTypeBatch\MaterialTypeBatch.h"
#include "RenderablesOfType\RenderablesOfType.h"

//	Default RendererBackend Constructor.
RendererBackend::RendererBackend()
{

}

//	Default RendererBackend Destructor.
RendererBackend::~RendererBackend()
{

}

//	Return the ID of the newly created renderable.
long int RendererBackend::createRenderable()
{
	//	Check if we can reuse Renderable IDs.
	if (inactiveRenderables.size() == 0)
	{
		//	Get the next possible ID.
		long int newRenderableID = activeRenderables.size();

		//	Add it to the list of IDs.
		activeRenderables.push_back(newRenderableID);

		//	Add the Renderable.
		addRenderable(newRenderableID);

		//	Return the Renderable.
		return newRenderableID;
	}
	else
	{
		//	Get the RenderableID.
		long int newRenderableID = inactiveRenderables[inactiveRenderables.size() - 1];

		//	Remove the Renderable.
		inactiveRenderables.pop_back();

		//	Add the Renderable.
		addRenderable(newRenderableID);

		//	Return the Renderable.
		return newRenderableID;
	}
}



//	Add the Renderable.
void RendererBackend::addRenderable(const long int & currentRenderableID)
{
	std::shared_ptr<Renderable> newRenderable = std::make_shared<Renderable>(currentRenderableID);

	//	Set the Default ShaderType.
	newRenderable->setShaderType(defaultShaderType);

	//	Set the Default Geometry Type.
	newRenderable->setGeometryType(defaultGeometryType);

	//	Set the Default Material Type.
	newRenderable->setMaterialType(defaultMaterialType);

	//	Create the new RenderableMetaData from the provided Renderable..
	std::shared_ptr<RenderableMetaData> newRenderableMetaData = std::make_shared<RenderableMetaData>();

	//	Assign the Renderable pointer.
	newRenderableMetaData->renderable = newRenderable;

	//	Assign the Renderable type.
	newRenderableMetaData->renderableType = std::make_shared<RenderableType>(newRenderable->getShaderType(), newRenderable->getGeometryType(), newRenderable->getMaterialType());

	//	
	addRenderableMetaData(newRenderableMetaData);
}

//	Return the const Renderable associated with the specified RenderableID
std::shared_ptr<const Renderable> RendererBackend::viewRenderable(const long int & currentRenderableID) const
{
	//	Get the RenderableMetaData.
	auto renderableMetaData = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	//	Check if the Renderable exists.
	if (renderableMetaData != mapRenderableIDToRenderableMetaData.end())
	{
		//	Return the Renderable.
		return renderableMetaData->second->renderable;
	}
	else
	{
		//	Return NULL.
		return NULL;
	}
}

std::shared_ptr<const RenderablesOfType> RendererBackend::viewRenderablesOfType(const RenderableType & renderableTypeKeys) const
{
	//	Get the RenderableMetaData.
	auto renderablesOfType = mapRenderableTypeToRenderables.find(renderableTypeKeys);

	//	Check if the Renderable exists.
	if (renderablesOfType != mapRenderableTypeToRenderables.end())
	{
		//	Return the Renderable.
		return renderablesOfType->second;
	}
	else
	{
		//	Return NULL.
		return NULL;
	}
}

//	Return the Shader Type Batch associated with the requested ShaderType.
std::shared_ptr<const ShaderTypeBatch> RendererBackend::viewShaderTypeBatch(const std::string & requestedShaderType) const
{
	//	Get the ShaderTypeBatch.
	auto shaderTypeBatch = mapShaderTypesToShaderTypeBatch.find(requestedShaderType);

	//	Check if the ShaderTypeBatch exists.
	if (shaderTypeBatch != mapShaderTypesToShaderTypeBatch.end())
	{
		//	Return the ShaderTypeBatch.
		return shaderTypeBatch->second;
	}
	else
	{
		//	Return NULL.
		return NULL;
	}
}

//	Update the Shading Type associated with the specified Renderable ID.
void RendererBackend::updateShadingType(const long int & currentRenderableID, const std::string & newShadingType)
{
}

//	Update the Geometry Type associated with the specified Renderable ID.
void RendererBackend::updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType)
{
}

//	Update the Material Type associated with the specified Renderable ID.
void RendererBackend::updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType)
{
}

//	Update the Transform Matrix associated with the specified Renderable ID.
void RendererBackend::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
}

//	Add the RenderableMetaData.
void RendererBackend::addRenderableMetaData(std::shared_ptr<RenderableMetaData> newRenderableMetaData)
{
	//	Get the appropriate Shader Type Batch (We can create it here if it does not exist).
	std::string newShaderType = newRenderableMetaData->renderableType->shaderType;

	//	Identify a new combination of Shader, Geometry and Material.
	bool newRenderableType = false;

	//	Find the Shader Type Batch.
	auto shaderTypeBatchX = mapShaderTypesToShaderTypeBatch.find(newShaderType);
	std::shared_ptr<ShaderTypeBatch> shaderTypeBatch = NULL;

	//	Check if we found a Shader Type of that Batch.
	if (shaderTypeBatchX != mapShaderTypesToShaderTypeBatch.end())
	{
		//	Check if that Shader Type Batch is not NULL.
		if (shaderTypeBatchX->second != NULL)
		{
			//	Return the Shader Type Batch.
			shaderTypeBatch = shaderTypeBatchX->second;
		}
		else
		{
			//	Create the Shader Type Batch.
			shaderTypeBatch = std::make_shared<ShaderTypeBatch>(this->shared_from_this(), newShaderType);

			//	Assign it back.
			shaderTypeBatchX->second = shaderTypeBatch;

			//	Indicate that we have a new Renderable Type.
			newRenderableType = true;
		}
	}
	else
	{
		//	Create the new Shader Type Batch.
		shaderTypeBatch = std::make_shared<ShaderTypeBatch>(this->shared_from_this(), newShaderType);

		//	Add the Shader Type Batch to the Map of Shader Types to the Shader Type Batch.
		mapShaderTypesToShaderTypeBatch[newShaderType] = shaderTypeBatch;

		//	Indicate that we have a new Renderable Type.
		newRenderableType = true;
	}

	//	From the Shader Type Batch, get the appropriate Geometry Type Batch (We can create it here if it does not exist).
	std::shared_ptr<GeometryTypeBatch> geometryTypeBatch = shaderTypeBatch->getGeometryTypeBatch(newRenderableMetaData->renderableType->geometryType);

	if (geometryTypeBatch == NULL)
	{
		//	Create the Geometry Type Batch.
		geometryTypeBatch = shaderTypeBatch->createGeometryTypeBatch(newRenderableMetaData->renderableType->geometryType);

		//	Indicate that we have a new Renderable Type.
		newRenderableType = true;
	}


	//	From the Geometry Type Batch, get the appropriate Material Type Batch (We can create it here if it does not exist.)
	std::shared_ptr<MaterialTypeBatch> materialTypeBatch = geometryTypeBatch->getMaterialTypeBatch(newRenderableMetaData->renderableType->materialType);

	if (materialTypeBatch == NULL)
	{
		//	Create the Material Type Batch.
		materialTypeBatch = geometryTypeBatch->createMaterialTypeBatch(newRenderableMetaData->renderableType->materialType);

		//	Indicate that we have a new Renderable Type.
		newRenderableType = true;

	}

	//	Add the Renderable to the Batch, appropriately updating the GPU buffer data.
	materialTypeBatch->addRenderable(newRenderableMetaData);

	//	Create the appropriate entry.
	if (newRenderableType == true)
	{
		mapRenderableTypeToRenderables[*(newRenderableMetaData->renderableType)] = materialTypeBatch->getRenderablesOfType();
	}

}


//	Remove the Renderable.
void RendererBackend::removeRenderable(const long int & deadRenderable)
{
	auto renderable = mapRenderableIDToRenderableMetaData.find(deadRenderable);

	if (renderable != mapRenderableIDToRenderableMetaData.end())
	{
		removeRenderableMetaData(deadRenderable);

		for (int i = 0; i < activeRenderables.size(); i++)
		{
			if (activeRenderables[i] == deadRenderable)
			{
				activeRenderables[i] = activeRenderables[activeRenderables.size() - 1];
				activeRenderables.pop_back();
				break;
			}
		}
			
		inactiveRenderables.push_back(deadRenderable);

		mapRenderableIDToRenderableMetaData.erase(renderable);
	}
}

//	Add a Geometry Type, using the provided data.
void RendererBackend::addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryData)
{

}

//	Update the Geometry Type, using the provided data.
void RendererBackend::updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData)
{

}

//	Remove the Geometry Type, using the provided data.
void RendererBackend::removeGeometryType(std::string deadGeometryType)
{

}

//	
int RendererBackend::getGeometryTypeVAOID(const std::string & requestedGeometryType) const
{
	int VAOID = 0;
	getGeometryTypeVAOIDAndGeometryTypeMetaData(requestedGeometryType, VAOID);
	return VAOID;
}

//
std::shared_ptr<GeometryTypeMetaData> RendererBackend::getGeometryTypeVAOIDAndGeometryTypeMetaData(const std::string & requestedGeometryType, int & VAOID) const
{
	auto geometryMetaData = mapGeometryTypeToGeometryMetaData.find(requestedGeometryType);

	if (geometryMetaData != mapGeometryTypeToGeometryMetaData.end())
	{
		VAOID = geometryMetaData->second->vaoMetaData.lock()->vaoID;
		return (geometryMetaData->second);
	}
	else
	{
		VAOID = 0;
		return NULL;
	}
}

//	Remove the RenderableMetaData.
void RendererBackend::removeRenderableMetaData(const long int & currentRenderableID)
{
	auto renderableMetaDataEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	if (renderableMetaDataEntry != mapRenderableIDToRenderableMetaData.end())
	{
		//	Find the appropriate Shader Type Batch.
		std::shared_ptr<ShaderTypeBatch> shaderTypeBatch = getShaderTypeBatch(renderableMetaDataEntry->second->renderableType->shaderType);

		//	From the Shader Type Batch, get the appropriate Geometry Type Batch (We can create it here if it does not exist).
		if (shaderTypeBatch != NULL)
		{
			//	From the Geometry Type Batch, get the appropriate Material Type Batch (We can create it here if it does not exist.)
			std::shared_ptr<GeometryTypeBatch> geometryTypeBatch = shaderTypeBatch->getGeometryTypeBatch(renderableMetaDataEntry->second->renderableType->geometryType);

			if (geometryTypeBatch != NULL)
			{
				std::shared_ptr<MaterialTypeBatch> materialTypeBatch = geometryTypeBatch->getMaterialTypeBatch(renderableMetaDataEntry->second->renderableType->materialType);

				if (materialTypeBatch != NULL)
				{
					//	Remove the Renderable from the Batch, appropriately updating the GPU buffer data.
					materialTypeBatch->removeRenderable(renderableMetaDataEntry->second);

					if (materialTypeBatch->getRenderablesOfType()->getRenderablesofTypeCount() == 0)
					{
						materialTypeBatch = NULL;
						geometryTypeBatch->eraseMaterialTypeBatch(renderableMetaDataEntry->second->renderableType->materialType);
						mapRenderableTypeToRenderables.erase(*(renderableMetaDataEntry->second->renderableType));
					}

					if (geometryTypeBatch->getMaterialTypeBatchesCount() == 0)
					{
						shaderTypeBatch->eraseGeometryTypeBatch(renderableMetaDataEntry->second->renderableType->geometryType);
					}

					if (shaderTypeBatch->getGeometryTypeBatchesCount() == 0)
					{
						mapShaderTypesToShaderTypeBatch.erase(renderableMetaDataEntry->second->renderableType->shaderType);
					}

					mapRenderableIDToRenderableMetaData.erase(renderableMetaDataEntry);
				}
			}
		}
	}
}

//	Return the Shader Type Batch, NULL if it is not available.
std::shared_ptr<ShaderTypeBatch> RendererBackend::getShaderTypeBatch(const std::string & requestedShaderType)
{
	//	Find the Shader Type Batch.
	auto shaderType = mapShaderTypesToShaderTypeBatch.find(requestedShaderType);

	//	Check if we found a Shader Type of that Batch.
	if (shaderType != mapShaderTypesToShaderTypeBatch.end())
	{
		//	Check if that Shader Type Batch is not NULL.
		if (shaderType->second != NULL)
		{
			//	Return the Shader Type Batch.
			return shaderType->second;
		}
		else
		{
			//	Return the Shader Type.
			return NULL;
		}
	}
	else
	{
		//	Return the Shader Type.
		return NULL;
	}
}
