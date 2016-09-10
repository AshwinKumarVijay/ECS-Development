#include "VAOManager.h"
#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"

//	Default VAOManager Constructor
VAOManager::VAOManager()
{

}

//	Default VAOManager Destructor
VAOManager::~VAOManager()
{
	//	Iterate over the VAOs types.
	for (auto vaoTypeIterator = mapVAOTypeToVAOs.begin(); vaoTypeIterator != mapVAOTypeToVAOs.end(); vaoTypeIterator++)
	{
		//	Get the VAO
		std::shared_ptr<std::vector<VAOStorage>> VAOs = vaoTypeIterator->second;

		//	Delete the VAOs.
		for (int i = 0; i < VAOs->size(); i++)
		{
			(*VAOs)[i].deleteVAO();
		}
	}
}

//	Add the Geometry to the VAO Storage.
void VAOManager::addGeometryToVAOStorage(std::shared_ptr<RendererGeometryData> newGeometryData)
{
	//	Get the Geometry Vertex Information Type.
	int geometryDescriptionRepresentation = newGeometryData->geometryDescriptionRepresentation;

	//	Find the VAOs of the specified type.
	auto vaoTypeIterator = mapVAOTypeToVAOs.find(geometryDescriptionRepresentation);

	//	Check if there are any VAOs that support the geometry vertex information type.
	if (vaoTypeIterator != mapVAOTypeToVAOs.end())
	{
		//	Create the VAO 
		std::shared_ptr<std::vector<VAOStorage>> VAOs = vaoTypeIterator->second;

		//	The ID of the smallest VAO.
		int minSizeVAOID = 0;

		//	Ths size of the smallest VAO.
		int minSizeVAO = INT_MAX;

		//	Iterate over the VAOs.
		for (int i = 0; i < VAOs->size(); i++)
		{
			//	Check if this VAO is smaller than the currently selected one.
			if (minSizeVAO > (*VAOs)[i].viewGeometryNames().size())
			{
				//	Update the variables.
				minSizeVAOID = i;
				minSizeVAO = (int)(*VAOs)[i].viewGeometryNames().size();
			}
		}

		//	Add the Geometry Data to the appropriate VAO.
		(*VAOs)[minSizeVAOID].addGeometryToStorage(newGeometryData);
	}
	else
	{
		//	If there are no available VAOs, create a new VAO.
		VAOStorage newVAO;

		//	Initialize the VAO.
		newVAO.initializeVAO();

		//	Set the VAO Format from the Geometry Vertex Information Type.
		setBoundVAOFormatFromType(geometryDescriptionRepresentation);

		//	Add Geometry Storage to the VAO.
		newVAO.addGeometryToStorage(newGeometryData);

		//	Create the new vectors of the VAOs that support this type.
		mapVAOTypeToVAOs[geometryDescriptionRepresentation] = std::make_shared<std::vector<VAOStorage>>();

		//	Push back the newly created VAO.
		mapVAOTypeToVAOs[geometryDescriptionRepresentation]->push_back(newVAO);
	}
}

//	View the VAOs of this Type.
std::shared_ptr<const std::vector<VAOStorage>> VAOManager::viewVAOsOfType(const int & requestedVAOType)
{
	//	Find the VAOs of the specified type.
	auto vaoTypeIterator = mapVAOTypeToVAOs.find(requestedVAOType);

	//	Check if there are any VAO Type.
	if (vaoTypeIterator != mapVAOTypeToVAOs.end())
	{
		//	Return the associated VAOStorages.
		return vaoTypeIterator->second;
	}
	else
	{
		//	Return NULL.
		return NULL;
	}
}

//	Update the Geometry.
void VAOManager::updateGeometry(std::shared_ptr<RendererGeometryData> newGeometryData)
{


}

//	Remove Geometry From VAO Storage.
void VAOManager::removeGeometryFromVAOStorage(const std::string & deadGeometryName)
{
	//	Iterate over the VAO Types.
	for (auto vaoTypeIterator = mapVAOTypeToVAOs.begin(); vaoTypeIterator != mapVAOTypeToVAOs.end(); vaoTypeIterator++)
	{
		//	
		std::shared_ptr<std::vector<VAOStorage>> VAOs = vaoTypeIterator->second;

		//	Remove the Geometry from the VAOs.
		for (int i = 0; i < VAOs->size(); i++)
		{
			(*VAOs)[i].removeGeometryFromStorage(deadGeometryName);
		}
	}
}

//	Return the Map of VAO Types to VAOs.	
const std::map<int, std::shared_ptr<std::vector<VAOStorage>>>& VAOManager::viewMapVAOTypeToVAOs()
{
	return mapVAOTypeToVAOs;
}

//	Set the Bound VAO Format.
void VAOManager::setBoundVAOFormatFromType(const int & geometryVertexInformationType)
{
	//	Check for basic vertex data.
	if ((geometryVertexInformationType & 1) == 1)
	{
		//	Position - as a vec3
		glEnableVertexAttribArray(0);
		glVertexAttribFormat(0, 4, GL_FLOAT, false, 0);
		glVertexAttribBinding(0, 0);

		//	Normal - as a vec3
		glEnableVertexAttribArray(1);
		glVertexAttribFormat(1, 3, GL_FLOAT, false, 0);
		glVertexAttribBinding(1, 1);

		//	Color - as a vec4
		glEnableVertexAttribArray(2);
		glVertexAttribFormat(2, 4, GL_FLOAT, false, 0);
		glVertexAttribBinding(2, 2);

	}

	//	Check for normal data.
	if ((geometryVertexInformationType & 2) == 2)
	{
		//	Vertex Tangent - as a vec3
		glEnableVertexAttribArray(3);
		glVertexAttribFormat(3, 3, GL_FLOAT, false, 0);
		glVertexAttribBinding(3, 3);

		//	Vertex Bitangent - as a vec3
		glEnableVertexAttribArray(4);
		glVertexAttribFormat(4, 3, GL_FLOAT, false, 0);
		glVertexAttribBinding(4, 4);
	}

	//	Check for texture data.
	if ((geometryVertexInformationType & 4) == 4)
	{
		//	Vertex Texture Coordinates 1 - as a vec2
		glEnableVertexAttribArray(5);
		glVertexAttribFormat(5, 2, GL_FLOAT, false, 0);
		glVertexAttribBinding(5, 5);

		//	Vertex Texture Coordinates 2- as a vec2
		glEnableVertexAttribArray(6);
		glVertexAttribFormat(6, 2, GL_FLOAT, false, 0);
		glVertexAttribBinding(6, 6);
	}

}
