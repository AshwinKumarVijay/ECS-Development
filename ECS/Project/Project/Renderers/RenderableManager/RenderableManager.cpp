#include "RenderableManager.h"
#include "../Renderable/Renderable.h"

//	Default RenderableManager Constructor
RenderableManager::RenderableManager()
{
	lastRenderableID = 0;
}

//	Default RenderableManager Destructor
RenderableManager::~RenderableManager()
{

}

//	Create the Renderable and return the RenderableID.
long int RenderableManager::createRenderable()
{
	//	Check if there are any available inactive renderables.
	if (destroyedRenderableIDs.size() == 0)
	{
		//	Get a new ID if there are not new renderables.
		long int newRenderableID = lastRenderableID;

		//	Create a new Renderable with the ID.
		mapIDToRenderable[newRenderableID] = std::make_shared<Renderable>(newRenderableID);

		//	Add the ID to the list of the newRenderableIDs.
		activeRenderableIDs.push_back(newRenderableID);

		//	Add Renderable to the appropriate location.
		addRenderableToStorage(newRenderableID);

		//	Increment the last used ID.
		lastRenderableID++;

		//	Return the RenderableID.
		return newRenderableID;
	}
	else
	{
		//	Get a new ID from the list of inactive renderables.
		long int newRenderableID = destroyedRenderableIDs.back();

		//	Remove the renderable.
		destroyedRenderableIDs.pop_back();

		//	Create a new Renderable with the new ID.
		mapIDToRenderable[newRenderableID] = std::make_shared<Renderable>(newRenderableID);

		//	Add Renderable to the appropriate location.
		addRenderableToStorage(newRenderableID);

		//	Add the ID to the list of the newRenderableIDs.
		activeRenderableIDs.push_back(newRenderableID);

		//	Return the new RenderableID.
		return newRenderableID;
	}
}

//	View the Renderable.
std::shared_ptr<const Renderable> RenderableManager::viewRenderable(const long int & currentRenderableID) const
{
	//	Try and find the Renderable.
	auto itr = mapIDToRenderable.find(currentRenderableID);

	//	Return the pointer if it was found, and NULL otherwise.
	if (itr != mapIDToRenderable.end())
	{
		return itr->second;
	}
	else
	{
		//	TO DO
		//	Throw Exception if Renderable is not found.
		return NULL;
	}
}

//	Return the Renderable.
std::shared_ptr<Renderable> RenderableManager::getRenderable(const long int & currentRenderableID)
{
	//	Try and find the Renderable.
	auto itr = mapIDToRenderable.find(currentRenderableID);

	//	Return the pointer if it was found, and NULL otherwise.
	if (itr != mapIDToRenderable.end())
	{
		return itr->second;
	}
	else
	{
		//	TO DO
		//	Throw Exception if Renderable is not found.
		return NULL;
	}
}

//	Return the Map of ShaderType to Geometry Types.
const std::map<ShadingTypes::ShadingType, std::vector<std::string>> & RenderableManager::getShadingTypesAndGeometryTypes()
{
	return mapShadingTypeToGeometryTypes;
}

//	Return the number of Renderables that use the Shader Type.
int RenderableManager::getShadingTypeRenderableNumber(const ShadingTypes::ShadingType requestedShaderType)
{
	//	The Number of Renderables that use this Shader.
	int shaderTypeRenderableCount = 0;

	//	Iterate over the Renderables.
	for (auto shaderTypeIterator = mapShadingTypeAndGeometryTypeToRenderables.begin(); shaderTypeIterator != mapShadingTypeAndGeometryTypeToRenderables.end(); shaderTypeIterator++)
	{
		//	Check the shader type.
		if (shaderTypeIterator->first.first == requestedShaderType)
		{
			//	Add the Renderables up.
			shaderTypeRenderableCount += (int)shaderTypeIterator->second->size();
		}
	}

	//	Return the Renderables.
	return shaderTypeRenderableCount;
}

//	Return the number of Renderables that use the ShaderType and the Geometry Type.
int RenderableManager::getShadingTypeGeometryTypeRenderableNumber(const ShadingTypes::ShadingType requestedShadingType, const std::string & requestedGeometryType)
{
	//	Find the Renderables that use both the Renderables and the Geometry Type.
	std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> renderables = viewRenderablesOfShadingTypeAndGeometryType(requestedShadingType, requestedGeometryType);

	//	Check if there were any, and if there were, return the number of them, or return 0.
	if (renderables != NULL)
	{
		return (int)renderables->size();
	}
	else
	{
		return 0;
	}
}

//	Update the ShaderType of the renderable specified by ID.
void RenderableManager::updateShadingType(const long int & currentRenderableID, ShadingTypes::ShadingType newShadingType)
{
	std::shared_ptr<Renderable> currentRenderable = getRenderable(currentRenderableID);

	if (currentRenderable != NULL)
	{
		if (currentRenderable->getShadingType() != newShadingType)
		{
			//	Remove the Renderable from storage.
			removeRenderableFromStorage(currentRenderableID);

			//	Change the Shader Type.
			mapIDToRenderable[currentRenderableID]->setShadingType(newShadingType);

			//	Add it back in.
			addRenderableToStorage(currentRenderableID);
		}
	}
}

//	Update the Geometry of the renderable specified by ID.
void RenderableManager::updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType)
{
	std::shared_ptr<Renderable> currentRenderable = getRenderable(currentRenderableID);

	if (currentRenderable != NULL)
	{
		if (currentRenderable->getGeometryType() != newGeometryType)
		{
			//	Remove the Renderable from Storage.
			removeRenderableFromStorage(currentRenderableID);

			//	Change the Geometry Type.
			mapIDToRenderable[currentRenderableID]->setGeometryType(newGeometryType);

			//	Add the Renderable Back in.
			addRenderableToStorage(currentRenderableID);
		}
	}
}

//	Update the Material of the renderable specified by ID.
void RenderableManager::updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType)
{
	for (auto itr = mapShadingTypeAndGeometryTypeToRenderables.begin(); itr != mapShadingTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		for (int i = 0; i < itr->second->size(); i++)
		{
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				(*itr->second)[i]->setMaterialType(newMaterialType);
				(*(getMaterialsList(itr->first)))[i] = newMaterialType;
			}
		}
	}
}

//	Update the Transform of the renderable specified by ID.
void RenderableManager::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
	for (auto itr = mapShadingTypeAndGeometryTypeToRenderables.begin(); itr != mapShadingTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		for (int i = 0; i < itr->second->size(); i++)
		{
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				(*itr->second)[i]->setTransformMatrix(newTransformMatrix);
				(*(getTransformsList(itr->first)))[i] = newTransformMatrix;
			}
		}
	}
}

//	Return a pointer to the renderables that use the both the geometry and the shader type.
std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> RenderableManager::viewRenderablesOfShadingTypeAndGeometryType(ShadingTypes::ShadingType requestedShadingType, const std::string & requestedGeometryType) const
{
	//	Find the Renderables with the specified Shader Type and Geometry Type.
	auto renderableGeometryShaderIterator = mapShadingTypeAndGeometryTypeToRenderables.find(std::make_pair(requestedShadingType, requestedGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (renderableGeometryShaderIterator != mapShadingTypeAndGeometryTypeToRenderables.end())
	{
		return renderableGeometryShaderIterator->second;
	}
	else
	{
		return NULL;
	}

}

//	Return a pointer to the vector of materials that use both the shader type and the geometry type.
std::shared_ptr<const std::vector<std::string>> RenderableManager::viewMaterialsOfShadingTypeAndGeometryType(ShadingTypes::ShadingType newShadingType, const std::string & requestedGeometryType) const
{
	//	Find the Materials used by the Renderables with the specified Shader Type and Geometry Type.
	auto materialGeometryShaderIterator = mapShadingTypeAndGeometryTypeToMaterials.find(std::make_pair(newShadingType, requestedGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (materialGeometryShaderIterator != mapShadingTypeAndGeometryTypeToMaterials.end())
	{
		return materialGeometryShaderIterator->second;
	}
	else
	{
		return NULL;
	}
}

//	Return a pointer to the vector of transforms that use both the shader type and the geometry type.
std::shared_ptr<const std::vector<glm::mat4>> RenderableManager::viewTransformsOfShadingTypeAndGeometryType(ShadingTypes::ShadingType newShadingType, const std::string & requestedGeometryType) const
{
	//	Find the Transform Matrices used by the Renderables with the specified Shader Type and Geometry Type.
	auto transformGeometryShaderIterator = mapShadingTypeAndGeometryTypeToTransforms.find(std::make_pair(newShadingType, requestedGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (transformGeometryShaderIterator != mapShadingTypeAndGeometryTypeToTransforms.end())
	{
		return transformGeometryShaderIterator->second;
	}
	else
	{
		//	Return NULL if there are no renderables using the specified Shading Type and Geometry Type.
		return NULL;
	}
}

//	Remove the Renderable specified by ID.
void RenderableManager::removeRenderable(const long int & currentRenderableID)
{
	//	Remove the Renderable from Storage.
	removeRenderableFromStorage(currentRenderableID);
}

//	Return the list of renderables that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<std::shared_ptr<Renderable>>> RenderableManager::getRenderablesList(std::pair<ShadingTypes::ShadingType, std::string> shaderTypeAndGeometryType)
{
	if (mapShadingTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShadingTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShadingTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType] = std::make_shared<std::vector<std::shared_ptr<Renderable>>>();
	}
}

//	Return the list of materials that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<std::string>> RenderableManager::getMaterialsList(std::pair<ShadingTypes::ShadingType, std::string> shaderTypeAndGeometryType)
{
	if (mapShadingTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShadingTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShadingTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType] = std::make_shared<std::vector<std::string>>();
	}
}

//	Return the list of transforms that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<glm::mat4>> RenderableManager::getTransformsList(std::pair<ShadingTypes::ShadingType, std::string> shaderTypeAndGeometryType)
{
	if (mapShadingTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShadingTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShadingTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType] = std::make_shared<std::vector<glm::mat4>>();
	}
}

//	Add a Renderable to the Storage.
void RenderableManager::addRenderableToStorage(const long int & currentRenderableID)
{
	//	Current Geometry Type.
	std::string currentGeometryType = mapIDToRenderable[currentRenderableID]->getGeometryType();
	
	//	Current Shader Type.
	ShadingTypes::ShadingType currentShaderType = mapIDToRenderable[currentRenderableID]->getShadingType();

	//	Construct the pair of the Shader Type and the Geometry Type.
	std::pair<ShadingTypes::ShadingType, std::string> shaderTypeAndGeometryType = std::make_pair(currentShaderType, currentGeometryType);

	//	Return the Renderables associated with this combination of the Shader Type and Geometry Type.
	getRenderablesList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]);

	//	Return the Transforms associated withthis combination of the Shader Type and Geometry Type.
	getTransformsList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]->getTransformMatrix());

	//	Return the Materials associated with this combination of the Shader Type and Geometry Type.
	getMaterialsList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]->getMaterialType());

	//	Add this Geometry Type and Shading Type.
	addGeometryTypeToShadingTypeMap(currentShaderType, currentGeometryType);
}

//	Remove the Renderable from Storage.
void RenderableManager::removeRenderableFromStorage(const long int & currentRenderableID)
{
	//	Iterate over the Shading Types and Geometry Types.
	for (auto itr = mapShadingTypeAndGeometryTypeToRenderables.begin(); itr != mapShadingTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		//	Iterate over the Renderables, within the Shading Types and Geometry Types.
		for (int i = 0; i < itr->second->size(); i++)
		{
			//	Check if we have found the current Renderable.
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				//	Erase the current Renderable.
				itr->second->erase(itr->second->begin() + i);

				//	Erase the Material entry in the Materials.
				mapShadingTypeAndGeometryTypeToMaterials[itr->first]->erase(mapShadingTypeAndGeometryTypeToMaterials[itr->first]->begin() + i);

				//	Erase the Geometry entry in the Transforms.
				mapShadingTypeAndGeometryTypeToTransforms[itr->first]->erase(mapShadingTypeAndGeometryTypeToTransforms[itr->first]->begin() + i);
			}
		}
	}

	//	
	cleanGeometryTypeToShadingTypeMap();

	//	
	cleanMaterialTypeToShadingTypeMap();
}

//	Add the Geometry Type to Shader Type.
void RenderableManager::addGeometryTypeToShadingTypeMap(ShadingTypes::ShadingType requestedShaderType, const std::string & newGeometryType)
{
	//	Check if there is an entry for the Geometry Type.
	bool existingGeometryType = false;
	
	//	
	for (int i = 0; i < mapShadingTypeToGeometryTypes[requestedShaderType].size(); i++)
	{
		if (mapShadingTypeToGeometryTypes[requestedShaderType][i] == newGeometryType)
		{
			existingGeometryType = true;
			break;
		}
	}

	//	
	if (existingGeometryType == false)
	{
		mapShadingTypeToGeometryTypes[requestedShaderType].push_back(newGeometryType);
	}
}

//	Clean up the Geometry to Shader Type map.
void RenderableManager::cleanGeometryTypeToShadingTypeMap()
{


}

//	Clean the Material Type to the Shading Type Map.
void RenderableManager::cleanMaterialTypeToShadingTypeMap()
{


}
