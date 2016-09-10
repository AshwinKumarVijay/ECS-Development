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
const std::map<std::string, std::vector<std::string>> & RenderableManager::getShaderAndGeometryTypes()
{
	return mapShaderTypeToGeometryTypes;
}

//	Return the number of Renderables that use the Shader Type.
int RenderableManager::getShaderTypeRenderableNumber(const std::string & requestedShaderType)
{
	//	The Number of Renderables that use this Shader.
	int shaderTypeRenderableCount = 0;

	//	Iterate over the Renderables.
	for (auto shaderTypeIterator = mapShaderTypeAndGeometryTypeToRenderables.begin(); shaderTypeIterator != mapShaderTypeAndGeometryTypeToRenderables.end(); shaderTypeIterator++)
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
int RenderableManager::getShaderTypeGeometryTypeRenderableNumber(const std::string & requestedShaderType, const std::string & requestedGeometryType)
{
	//	Find the Renderables that use both the Renderables and the Geometry Type.
	std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> renderables = viewRenderablesOfShaderTypeAndGeometryType(requestedShaderType, requestedGeometryType);

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
void RenderableManager::updateShaderType(const long int & currentRenderableID, const std::string & newShaderType)
{
	//	Remove the Renderable from storage.
	removeRenderableFromStorage(currentRenderableID);
	
	//	Change the Shader Type.
	mapIDToRenderable[currentRenderableID]->setShaderType(newShaderType);

	//	Add it back in.
	addRenderableToStorage(currentRenderableID);
}

//	Update the Geometry of the renderable specified by ID.
void RenderableManager::updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType)
{
	//	Remove the Renderable from Storage.
	removeRenderableFromStorage(currentRenderableID);

	//	Change the Geometry Type.
	mapIDToRenderable[currentRenderableID]->setGeometryType(newGeometryType);

	//	Add the Renderable Back in.
	addRenderableToStorage(currentRenderableID);
}

//	Update the Material of the renderable specified by ID.
void RenderableManager::updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType)
{
	for (auto itr = mapShaderTypeAndGeometryTypeToRenderables.begin(); itr != mapShaderTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		for (int i = 0; i < itr->second->size(); i++)
		{
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				(*itr->second)[i]->setMaterialType(newMaterialType);
			}
		}
	}
}


//	Update the Transform of the renderable specified by ID.
void RenderableManager::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
	for (auto itr = mapShaderTypeAndGeometryTypeToRenderables.begin(); itr != mapShaderTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		for (int i = 0; i < itr->second->size(); i++)
		{
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				(*itr->second)[i]->setTransformMatrix(newTransformMatrix);
			}
		}
	}
}

//	Return a pointer to the renderables that use the both the geometry and the shader type.
std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> RenderableManager::viewRenderablesOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const
{
	//	Find the Renderables with the specified Shader Type and Geometry Type.
	auto renderableGeometryShaderIterator = mapShaderTypeAndGeometryTypeToRenderables.find(std::make_pair(newShaderType, newGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (renderableGeometryShaderIterator != mapShaderTypeAndGeometryTypeToRenderables.end())
	{
		return renderableGeometryShaderIterator->second;
	}
	else
	{
		return NULL;
	}

}

//	Return a pointer to the vector of materials that use both the shader type and the geometry type.
std::shared_ptr<const std::vector<std::string>> RenderableManager::viewMaterialsOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const
{
	//	Find the Materials used by the Renderables with the specified Shader Type and Geometry Type.
	auto materialGeometryShaderIterator = mapShaderTypeAndGeometryTypeToMaterials.find(std::make_pair(newShaderType, newGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (materialGeometryShaderIterator != mapShaderTypeAndGeometryTypeToMaterials.end())
	{
		return materialGeometryShaderIterator->second;
	}
	else
	{
		return NULL;
	}
}

//	Return a pointer to the vector of transforms that use both the shader type and the geometry type.
std::shared_ptr<const std::vector<glm::mat4>> RenderableManager::viewTransformsOfShaderTypeAndGeometryType(const std::string & newShaderType, const std::string & newGeometryType) const
{
	//	Find the Transform Matrices used by the Renderables with the specified Shader Type and Geometry Type.
	auto transformGeometryShaderIterator = mapShaderTypeAndGeometryTypeToTransforms.find(std::make_pair(newShaderType, newGeometryType));

	//	Check if the Renderables exist. Otherwise, return NULL.
	if (transformGeometryShaderIterator != mapShaderTypeAndGeometryTypeToTransforms.end())
	{
		return transformGeometryShaderIterator->second;
	}
	else
	{
		return NULL;
	}
}


//	Remove the Renderable specified by ID.
void RenderableManager::removeRenderable(const long int & currentRenderableID)
{
	removeRenderableFromStorage(currentRenderableID);
	//	TO DO
	//	Throw Exception if Renderable is not found.
}

//	Return the list of renderables that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<std::shared_ptr<Renderable>>> RenderableManager::getRenderablesList(std::pair<std::string, std::string> shaderTypeAndGeometryType)
{
	if (mapShaderTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShaderTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShaderTypeAndGeometryTypeToRenderables[shaderTypeAndGeometryType] = std::make_shared<std::vector<std::shared_ptr<Renderable>>>();
	}
}

//	Return the list of materials that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<std::string>> RenderableManager::getMaterialsList(std::pair<std::string, std::string> shaderTypeAndGeometryType)
{
	if (mapShaderTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShaderTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShaderTypeAndGeometryTypeToMaterials[shaderTypeAndGeometryType] = std::make_shared<std::vector<std::string>>();
	}
}


//	Return the list of transforms that use both the shader and geometry type specified, and create one if none exists.
std::shared_ptr<std::vector<glm::mat4>> RenderableManager::getTransformsList(std::pair<std::string, std::string> shaderTypeAndGeometryType)
{
	if (mapShaderTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType] != NULL)
	{
		return 	mapShaderTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType];
	}
	else
	{
		return mapShaderTypeAndGeometryTypeToTransforms[shaderTypeAndGeometryType] = std::make_shared<std::vector<glm::mat4>>();
	}
}

//	Add a Renderable to the Storage.
void RenderableManager::addRenderableToStorage(const long int & currentRenderableID)
{
	//	Current Geometry Type.
	std::string currentGeometryType = mapIDToRenderable[currentRenderableID]->getGeometryType();
	
	//	Current Shader Type.
	std::string currentShaderType = mapIDToRenderable[currentRenderableID]->getShaderType();

	//	
	std::pair<std::string, std::string> shaderTypeAndGeometryType = std::make_pair(currentShaderType, currentGeometryType);

	getRenderablesList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]);
	getTransformsList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]->getTransformMatrix());
	getMaterialsList(shaderTypeAndGeometryType)->push_back(mapIDToRenderable[currentRenderableID]->getMaterialType());

	addGeometryTypeToShaderTypeMap(currentGeometryType, currentShaderType);
}

//	Remove the Renderable from Storage.
void RenderableManager::removeRenderableFromStorage(const long int & currentRenderableID)
{
	for (auto itr = mapShaderTypeAndGeometryTypeToRenderables.begin(); itr != mapShaderTypeAndGeometryTypeToRenderables.end(); itr++)
	{
		for (int i = 0; i < itr->second->size(); i++)
		{
			if ((*itr->second)[i]->getRenderableID() == currentRenderableID)
			{
				itr->second->erase(itr->second->begin() + i);
				mapShaderTypeAndGeometryTypeToMaterials[itr->first]->erase(mapShaderTypeAndGeometryTypeToMaterials[itr->first]->begin() + i);
				mapShaderTypeAndGeometryTypeToTransforms[itr->first]->erase(mapShaderTypeAndGeometryTypeToTransforms[itr->first]->begin() + i);
			}
		}
	}

	cleanGeometryTypeToShaderTypeMap();
}

//	Add the Geometry Type to Shader Type.
void RenderableManager::addGeometryTypeToShaderTypeMap(const std::string & newGeometryType, const std::string & requestedShaderType)
{
	bool existingGeometryType = false;
	
	for (int i = 0; i < mapShaderTypeToGeometryTypes[requestedShaderType].size(); i++)
	{
		if (mapShaderTypeToGeometryTypes[requestedShaderType][i] == newGeometryType)
		{
			existingGeometryType = true;
			break;
		}
	}

	if (existingGeometryType == false)
	{
		mapShaderTypeToGeometryTypes[requestedShaderType].push_back(newGeometryType);
	}
}

//	Clean up the Geometry to Shader Type map.
void RenderableManager::cleanGeometryTypeToShaderTypeMap()
{

}
