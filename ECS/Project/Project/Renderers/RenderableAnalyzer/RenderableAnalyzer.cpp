#include "RenderableAnalyzer.h"
#include "../Renderable/Renderable.h"
#include "../RendererBackend/RenderablesOfType/RenderablesOfType.h"


//	Default RenderableAnalyzer Constructor.
RenderableAnalyzer::RenderableAnalyzer()
{
	defaultShaderType = "ERROR_NO_SHADER";
	defaultMaterialType = "ERROR_NO_MATERIAL";
	defaultGeometryType = "ERROR_NO_GEOMETRY";
}

//	Default RenderableAnalyzer Destructor.
RenderableAnalyzer::~RenderableAnalyzer()
{

}

//	Create and Return a New Renderable, and the ID of the Renderable.
long int RenderableAnalyzer::createRenderable()
{
	//	Check if we can reuse Renderable IDs.
	if (inactiveRenderables.size() == 0)
	{
		long int newRenderableID = activeRenderables.size();
		
		activeRenderables.push_back(newRenderableID);
		addRenderable(newRenderableID);
		return newRenderableID;
	}
	else
	{
		long int newRenderableID = inactiveRenderables[inactiveRenderables.size() - 1];
		inactiveRenderables.pop_back();
		addRenderable(newRenderableID);
		return newRenderableID;
	}
}

//	Add a Renderable to the list of Renderables.
void RenderableAnalyzer::addRenderable(const long int & currentRenderableID)
{
	std::shared_ptr<Renderable> newRenderable = std::make_shared<Renderable>(currentRenderableID);

	//	Set the Default ShaderType.
	newRenderable->setShaderType(defaultShaderType);

	//	Set the Default Geometry Type.
	newRenderable->setGeometryType(defaultGeometryType);
	
	//	Set the Default Material Type.
	newRenderable->setMaterialType(defaultMaterialType);

	//	Create the new renderable info.
	std::shared_ptr<RenderableMetaData> newRenderableInfo = std::make_shared<RenderableMetaData>();
	
	//	Assign the new renderable info.
	newRenderableInfo->renderable = newRenderable;

	//	Create the new renderable type.
	newRenderableInfo->renderableType = std::make_shared<RenderableType>(defaultShaderType, defaultGeometryType, defaultMaterialType);

	//	
	mapRenderableIDToRenderableInfo[currentRenderableID] = newRenderableInfo;

	//	
	addRenderableInfoToList(newRenderableInfo);
}

//	Return the const Renderable associated with the specified RenderableID
std::shared_ptr<const Renderable> RenderableAnalyzer::viewRenderable(const long int & currentRenderableID) const
{
	//	Find the RenderableID.
	auto renderableTypeKeySearcher = mapRenderableIDToRenderableInfo.find(currentRenderableID);

	//	Check if we have actually found the Renderable Type Key.
	if (renderableTypeKeySearcher != mapRenderableIDToRenderableInfo.end())
	{
		return renderableTypeKeySearcher->second->renderable;
	}

	//	Return Null if no Renderable was not found.
	return NULL;
}

//	Return the Type Keys that are used.
const std::set<RenderableType>& RenderableAnalyzer::viewRenderablesTypes() const
{
	return renderableTypes;
}

const SortedRenderablesTypes & RenderableAnalyzer::viewSortedRenderablesTypes() const
{ 
	return sortedRenderableTypes;
}


//	Return the Renderable Info associated with the Renderable ID.
std::shared_ptr<RenderableMetaData> RenderableAnalyzer::getRenderableInfo(const long int & currentRenderableID)
{
	//	Find the RenderableID.
	auto renderableTypeKeySearcher = mapRenderableIDToRenderableInfo.find(currentRenderableID);

	//	Check if we have actually found the Renderable Type Key.
	if (renderableTypeKeySearcher != mapRenderableIDToRenderableInfo.end())
	{
		return renderableTypeKeySearcher->second;
	}

	//	Return Null if no Renderable was not found.
	return NULL;
}

//	Update the Shading Type of the specified Renderable.
void RenderableAnalyzer::updateShadingType(const long int & currentRenderableID, const std::string & newShaderType)
{
	//	Get the Renderable Info.
	std::shared_ptr<RenderableMetaData> currentRenderableInfo = getRenderableInfo(currentRenderableID);

	if (currentRenderableInfo != NULL)
	{
		//	
		if (currentRenderableInfo->renderable->getShaderType() != newShaderType)
		{
			removeRenderableInfoFromList(currentRenderableID);

			//	Update the Renderable and the Renderable Info.
			currentRenderableInfo->renderable->setShaderType(newShaderType);
			currentRenderableInfo->renderableType->shaderType = newShaderType;

			addRenderableInfoToList(currentRenderableInfo);
		}
	}
}


//	Update the Geometry Type of the specified Renderable.
void RenderableAnalyzer::updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType)
{
	//	Get the Renderable Info.
	std::shared_ptr<RenderableMetaData> currentRenderableInfo = getRenderableInfo(currentRenderableID);

	if (currentRenderableInfo != NULL)
	{
		//	
		if (currentRenderableInfo->renderable->getShaderType() != newGeometryType)
		{
			removeRenderableInfoFromList(currentRenderableID);

			//	Update the Renderable and the Renderable Info.
			currentRenderableInfo->renderable->setGeometryType(newGeometryType);
			currentRenderableInfo->renderableType->geometryType = newGeometryType;

			addRenderableInfoToList(currentRenderableInfo);
		}
	}
}

//	Update the Material Type of the specified Renderable.
void RenderableAnalyzer::updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType)
{
	//	Get the Renderable Info.
	std::shared_ptr<RenderableMetaData> currentRenderableInfo = getRenderableInfo(currentRenderableID);

	if (currentRenderableInfo != NULL)
	{
		//	
		if (currentRenderableInfo->renderable->getShaderType() != newMaterialType)
		{
			removeRenderableInfoFromList(currentRenderableID);

			//	Update the Renderable and the Renderable Info.
			currentRenderableInfo->renderable->setMaterialType(newMaterialType);
			currentRenderableInfo->renderableType->materialType = newMaterialType;

			addRenderableInfoToList(currentRenderableInfo);
		}
	}
}

//	Update the Transform Matrix of the specified Renderable.
void RenderableAnalyzer::updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix)
{
	//	Get the Renderable Info.
	std::shared_ptr<RenderableMetaData> currentRenderableInfo = getRenderableInfo(currentRenderableID);

	if (currentRenderableInfo != NULL)
	{
		std::shared_ptr<RenderablesOfType> renderablesOfType = getRenderablesOfType(*(currentRenderableInfo->renderableType));
		(*(renderablesOfType->getRenderableTransformMatrices()))[currentRenderableInfo->renderableEntry] = newTransformMatrix;
	}
}

//	Return the Renderables of this particular Type Key
std::shared_ptr<const RenderablesOfType> RenderableAnalyzer::viewRenderablesOfType(const RenderableType & renderableType) const
{
	//	
	auto renderableTypeKeySearcher = mapRenderableTypeToRenderables.find(renderableType);

	//	
	if (renderableTypeKeySearcher != mapRenderableTypeToRenderables.end())
	{
		//	
		return renderableTypeKeySearcher->second;
	}

	return NULL;
}

void RenderableAnalyzer::removeRenderable(const long int & deadRenderable)
{
	removeRenderableInfoFromList(deadRenderable);
	mapRenderableIDToRenderableInfo.erase(deadRenderable);
}


//	Return the Type Key Renderables, and create an entry for this specific type if does not exist.
std::shared_ptr<RenderablesOfType> RenderableAnalyzer::getRenderablesOfType(const RenderableType & renderableType)
{
	//	
	auto renderableTypeKeySearcher = mapRenderableTypeToRenderables.find(renderableType);

	//	
	if (renderableTypeKeySearcher != mapRenderableTypeToRenderables.end())
	{
		//	
		return renderableTypeKeySearcher->second;
	}
	else
	{
		//	
		renderableTypes.insert(renderableType);
		sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes[renderableType.shaderType].geometryTypeAssociatedMaterialTypes[renderableType.geometryType].materialsTypes.insert(renderableType.materialType);

		//	
		mapRenderableTypeToRenderables[renderableType] = std::make_shared<RenderablesOfType>(renderableType);
		return mapRenderableTypeToRenderables[renderableType];
	}
}


//	
void RenderableAnalyzer::addRenderableInfoToList(const std::shared_ptr<RenderableMetaData> newRenderableInfo)
{
	//	Get the list of Renderables with that type.
	std::shared_ptr<RenderablesOfType> renderablesOfType = getRenderablesOfType(*(newRenderableInfo->renderableType));

	//	We are adding to the end of that list, so the entry is at the current size.
	newRenderableInfo->renderableEntry = renderablesOfType->getRenderableMetaDatas()->size();

	//	Append the Renderable to the end of the list.
	renderablesOfType->getRenderableMetaDatas()->push_back(newRenderableInfo);

	//	Append the Transform Matrix to the end of the list.
	renderablesOfType->getRenderableTransformMatrices()->push_back(newRenderableInfo->renderable->getTransformMatrix());
}

void RenderableAnalyzer::removeRenderableInfoFromList(const long int & currentRenderableID)
{
	//	Get the list of Renderables with that type.
	std::shared_ptr<RenderableMetaData> currentRenderableInfo = getRenderableInfo(currentRenderableID);

	//	
	std::shared_ptr<RenderablesOfType> renderablesOfType = getRenderablesOfType(*(currentRenderableInfo->renderableType));

	//	
	if (currentRenderableInfo->renderableEntry != -1)
	{
		//	First, replace the entries of this renderable with the entries of the last renderable in the list.
		(*(renderablesOfType->getRenderableMetaDatas()))[currentRenderableInfo->renderableEntry] = (*(renderablesOfType->getRenderableMetaDatas()))[renderablesOfType->getRenderableMetaDatas()->size() - 1];
		(*(renderablesOfType->getRenderableTransformMatrices()))[currentRenderableInfo->renderableEntry] = (*(renderablesOfType->getRenderableTransformMatrices()))[renderablesOfType->getRenderableMetaDatas()->size() - 1];


		//	Then, update the entry of the Renderable Info that is now at the original location.
		(*(renderablesOfType->getRenderableMetaDatas()))[currentRenderableInfo->renderableEntry]->renderableEntry = currentRenderableInfo->renderableEntry;

		//	Then remove the two, now duplicated, entries at the end of the list.
		renderablesOfType->getRenderableMetaDatas()->pop_back();
		renderablesOfType->getRenderableTransformMatrices()->pop_back();

		if (renderablesOfType->getRenderableMetaDatas()->size() == 0)
		{
			renderablesOfType->getRenderableMetaDatas() = NULL;
			renderablesOfType->getRenderableTransformMatrices() = NULL;
			renderablesOfType = NULL;

			//	TO DO
			mapRenderableTypeToRenderables.erase(*(currentRenderableInfo->renderableType));
			
			//	TO DO
			renderableTypes.erase(*(currentRenderableInfo->renderableType));

			//	TO DO
			sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes[currentRenderableInfo->renderableType->shaderType].geometryTypeAssociatedMaterialTypes[currentRenderableInfo->renderableType->geometryType].materialsTypes.erase(currentRenderableInfo->renderableType->materialType);
		
			if (sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes[currentRenderableInfo->renderableType->shaderType].geometryTypeAssociatedMaterialTypes[currentRenderableInfo->renderableType->geometryType].materialsTypes.size() == 0)
			{
				sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes[currentRenderableInfo->renderableType->shaderType].geometryTypeAssociatedMaterialTypes.erase(currentRenderableInfo->renderableType->geometryType);

				if (sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes[currentRenderableInfo->renderableType->shaderType].geometryTypeAssociatedMaterialTypes.size() == 0)
				{
					sortedRenderableTypes.shaderTypeAssociatedGeometryMaterialTypes.erase(currentRenderableInfo->renderableType->shaderType);
				}
			}

		}

		//	
		currentRenderableInfo->renderableEntry = -1;
	}
}
