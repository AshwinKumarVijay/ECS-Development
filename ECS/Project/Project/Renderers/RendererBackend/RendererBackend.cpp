#include "RendererBackend.h"
#include "../Renderable/Renderable.h"
#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"
#include "ShaderTypeBatch\ShaderTypeBatch.h"
#include "GeometryTypeBatch\GeometryTypeBatch.h"
#include "MaterialTypeBatch\MaterialTypeBatch.h"
#include "RenderablesOfType\RenderablesOfType.h"

//	Default RendererBackend Constructor.
RendererBackend::RendererBackend()
{
	defaultGeometryType = "NO_GEOMETRY";
	defaultMaterialType = "NO_MATERIAL";
	defaultShaderType = "NO_SHADER";
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
	//	Create the Renderable with the Renderable ID.
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

	//	Add the Renderable Meta Data.
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

//	Return the const RenderablesOfType associated with the specified RenderableType.
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
	//	Update the Material Type.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	//	Check if it exists.
	if (renderableEntry != mapRenderableIDToRenderableMetaData.end())
	{
		//	Get the ShaderTypeBatch.
		auto shaderTypeBatch = mapShaderTypesToShaderTypeBatch.find(renderableEntry->second->renderableType->shaderType);

		//	Check if the Shader Type Batch exists.
		if (shaderTypeBatch != mapShaderTypesToShaderTypeBatch.end())
		{
			//	Get the Geometry Type Batch.
			auto geometryTypeBatch = shaderTypeBatch->second->getGeometryTypeBatch(renderableEntry->second->renderableType->geometryType);
			
			//	Check if the Geometry Type Batch exists.
			if (geometryTypeBatch != NULL)
			{
				//	Get the old Material Type Batch.
				std::shared_ptr<MaterialTypeBatch> oldMaterialTypeBatch = geometryTypeBatch->getMaterialTypeBatch(renderableEntry->second->renderableType->materialType);

				//	Check if it exists Material Type Batch.
				if (oldMaterialTypeBatch != NULL)
				{
					oldMaterialTypeBatch->removeRenderable(renderableEntry->second);

					if (oldMaterialTypeBatch->getRenderablesOfType()->getRenderablesofTypeCount() == 0)
					{
						geometryTypeBatch->eraseMaterialTypeBatch(renderableEntry->second->renderableType->materialType);
					}
				}

				//	Update the renderable and the metadata.
				renderableEntry->second->renderableType->materialType = newMaterialType;

				//	Get the new Material Type Batch.
				std::shared_ptr<MaterialTypeBatch> newMaterialTypeBatch = geometryTypeBatch->getMaterialTypeBatch(renderableEntry->second->renderableType->materialType);
				
				//	Check if the Material Type Batch.	
				if (newMaterialTypeBatch != NULL)
				{
					//	Create the Material Type Batch.
					newMaterialTypeBatch = geometryTypeBatch->createMaterialTypeBatch(renderableEntry->second->renderableType->materialType);
					mapRenderableTypeToRenderables[*(renderableEntry->second->renderableType)] = newMaterialTypeBatch->getRenderablesOfType();
				}

				//	Add the new Material Type.
				newMaterialTypeBatch->addRenderable(renderableEntry->second);
			}
		}
	}
}

//	Update the Transform Matrix associated with the specified Renderable ID.
void RendererBackend::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
	//	Find the Renderable Meta Data.
	auto renderableEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	//	Check if it exists.
	if (renderableEntry != mapRenderableIDToRenderableMetaData.end())
	{
		//	Find the Renderables.
		auto renderables = mapRenderableTypeToRenderables.find(*(renderableEntry->second->renderableType));

		//	Check if it exists.
		if (renderables != mapRenderableTypeToRenderables.end())
		{
			//	Update the Transform Matrix of the Renderable.
			renderables->second->updateTransformMatrix(renderableEntry->second);
		}
	}
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
	//	
	auto renderable = mapRenderableIDToRenderableMetaData.find(deadRenderable);

	//	
	if (renderable != mapRenderableIDToRenderableMetaData.end())
	{
		//
		removeRenderableMetaData(deadRenderable);

		//	
		for (int i = 0; i < activeRenderables.size(); i++)
		{
			if (activeRenderables[i] == deadRenderable)
			{
				activeRenderables[i] = activeRenderables[activeRenderables.size() - 1];
				activeRenderables.pop_back();
				break;
			}
		}
			
		//
		inactiveRenderables.push_back(deadRenderable);

		//
		mapRenderableIDToRenderableMetaData.erase(renderable);
	}
}

//	Add a Geometry Type, using the provided data.
void RendererBackend::addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryData)
{
	//	Create the new meta data.
	std::shared_ptr<GeometryTypeMetaData> newGeometryType = std::make_shared<GeometryTypeMetaData>();
	
	//	Associate the Meta Data with the provided Geometry Data.
	newGeometryType->rendererGeometryData = newGeometryData;
	
	//	Associate the Geometry Type.
	newGeometryType->geometryType = newGeometryData->geometryName;

	//	Add it to the VAO Backend.
	vaoBackend.addGeometryType(newGeometryType);

	//	Add it to the Map.
	mapGeometryTypeToGeometryMetaData[newGeometryType->geometryType] = newGeometryType;
}

//	Update the Geometry Type, using the provided data.
void RendererBackend::updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData)
{

}

//	Remove the Geometry Type, using the provided data.
void RendererBackend::removeGeometryType(std::shared_ptr<RendererGeometryData> deadGeometryType)
{
	//	Find the Geometry Type Entry.
	auto geometryTypeEntry = mapGeometryTypeToGeometryMetaData.find(deadGeometryType->geometryName);

	//	Remove it from the VAO.	
	vaoBackend.deleteGeometryType(geometryTypeEntry->second);

	//	Remove the Geometry Type.
	mapGeometryTypeToGeometryMetaData.erase(geometryTypeEntry);
}
//	Return the VAO associated with this Geometry Type.
int RendererBackend::getGeometryTypeVAOID(const std::string & requestedGeometryType) const
{
	//	
	int VAOID = 0;

	//
	getGeometryTypeVAOIDAndGeometryTypeMetaData(requestedGeometryType, VAOID);

	//	
	return VAOID;
}

//	Return the Geometry Type Meta Data, and the VAO ID associated with the Geometry Type.d
std::shared_ptr<GeometryTypeMetaData> RendererBackend::getGeometryTypeVAOIDAndGeometryTypeMetaData(const std::string & requestedGeometryType, int & VAOID) const
{
	//	
	auto geometryMetaData = mapGeometryTypeToGeometryMetaData.find(requestedGeometryType);

	//	
	if (geometryMetaData != mapGeometryTypeToGeometryMetaData.end())
	{
		//	
		VAOID = geometryMetaData->second->vaoMetaData.lock()->vaoID;

		//	
		return (geometryMetaData->second);
	}
	else
	{
		//
		VAOID = 0;
		
		//
		return NULL;
	}
}

//	Return the Map of the Shader Types to the Batches.
const std::map<std::string, std::shared_ptr<ShaderTypeBatch>>& RendererBackend::getShaderTypeBatches()
{
	return mapShaderTypesToShaderTypeBatch;
}

//	Remove the RenderableMetaData.
void RendererBackend::removeRenderableMetaData(const long int & currentRenderableID)
{
	//	Find the Renderable Meta Data.
	auto renderableMetaDataEntry = mapRenderableIDToRenderableMetaData.find(currentRenderableID);

	//	Check if it exists.
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

					//	Check if the number of the Renderables of Type. 
					if (materialTypeBatch->getRenderablesOfType()->getRenderablesofTypeCount() == 0)
					{
						//	
						materialTypeBatch = NULL;

						//
						geometryTypeBatch->eraseMaterialTypeBatch(renderableMetaDataEntry->second->renderableType->materialType);
						
						//
						mapRenderableTypeToRenderables.erase(*(renderableMetaDataEntry->second->renderableType));
					}

					//	Get the Number of Material Type Batches in the Geometry we just removed.
					if (geometryTypeBatch->getMaterialTypeBatchesCount() == 0)
					{
						//	Erase the Geometry Type Batch from the Shader Type Batch.
						shaderTypeBatch->eraseGeometryTypeBatch(renderableMetaDataEntry->second->renderableType->geometryType);
					}

					//	Get the Number of Geometry Type Batches.
					if (shaderTypeBatch->getGeometryTypeBatchesCount() == 0)
					{
						mapShaderTypesToShaderTypeBatch.erase(renderableMetaDataEntry->second->renderableType->shaderType);
					}

					//	Erase.
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
