#include "VAOBackend.h"
#include "../../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"

//	Default VAOBackend Constructor.
VAOBackend::VAOBackend()
{

}

//	Default VAOBackend Destructor.
VAOBackend::~VAOBackend()
{
	mapGeometryTypeToVAO.clear();
	
	for (int i = 0; i < VAOs.size(); i++)
	{
		glDeleteVertexArrays(1, &VAOs[i]->vaoID);
		VAOs[i]->geometryTypeMetaDatas.clear();
	}
}

//	Add the Geometry Type Data.
void VAOBackend::addGeometryType(std::shared_ptr<GeometryTypeMetaData> newGeometryType)
{
	//	Check if the Geometry passed in is not NULL.
	if (newGeometryType != NULL)
	{
		//	
		std::shared_ptr<VAOMetaData> VAO = getAvailableVAOforGeometry(newGeometryType->rendererGeometryData);
		std::shared_ptr<RendererGeometryData> newGeometryData = newGeometryType->rendererGeometryData;

		//	
		glGenBuffers(1, &newGeometryData->EBO);
		glNamedBufferData(newGeometryData->EBO, newGeometryData->indicesArray.size() * sizeof(GLuint), newGeometryData->indicesArray.data(), GL_STATIC_DRAW);

		//	
		glGenBuffers(1, &newGeometryData->vertexVBO);
		glNamedBufferData(newGeometryData->vertexVBO, newGeometryData->verticesArray.size() * sizeof(Vertex), newGeometryData->verticesArray.data(), GL_STATIC_DRAW);
		newGeometryData->offsetVertexVBO = 0;

		//	Check if we need to create a VBO for Normal Data.
		if ((newGeometryData->geometryDescriptionRepresentation & 2) == 2)
		{
			//	Generate a new Vertex Normal VBO for the Vertices.
			glGenBuffers(1, &newGeometryData->vertexNormalVBO);
			glBufferData(newGeometryData->vertexVBO, newGeometryData->verticesNormalData.size() * sizeof(VertexNormalData), newGeometryData->verticesNormalData.data(), GL_STATIC_DRAW);
			newGeometryData->offsetVertexNormalVBO = 0;
		}
		else
		{
			newGeometryData->vertexNormalVBO = 0;
			newGeometryData->offsetVertexNormalVBO = 0;
		}

		//	Check if need to create a VBO for the Texture Coordinates.
		if ((newGeometryData->geometryDescriptionRepresentation & 4) == 4)
		{
			//	Generate a new Vertex Normal VBO for the Vertices.
			glGenBuffers(1, &newGeometryData->vertexTextureVBO);
			glNamedBufferData(newGeometryData->vertexTextureVBO, newGeometryData->verticesTextureData.size() * sizeof(VertexTextureData), newGeometryData->verticesTextureData.data(), GL_STATIC_DRAW);
			newGeometryData->offsetVertexTextureVBO = 0;
		}
		else
		{
			newGeometryData->vertexTextureVBO = 0;
			newGeometryData->offsetVertexTextureVBO = 0;
		}
		
		//	
		VAO->geometryTypeMetaDatas[newGeometryData->geometryName] = newGeometryType;
		newGeometryType->vaoMetaData = VAO;
		mapGeometryTypeToVAO[newGeometryType->geometryType] = VAO;
	}
}

//	Update the Geometry Type.
void VAOBackend::updateGeometryType(std::shared_ptr<GeometryTypeMetaData> updatedGeometryData)
{
	//
	if (updatedGeometryData != NULL)
	{
		
	}

}

//	Delete the Geometry Type.
void VAOBackend::deleteGeometryType(std::shared_ptr<GeometryTypeMetaData> deadGeometryType)
{
	//
	if (deadGeometryType != NULL)
	{
		//	
		auto VAOEntry = mapGeometryTypeToVAO.find(deadGeometryType->geometryType);

		//	
		if (VAOEntry != mapGeometryTypeToVAO.end())
		{
			//	
			for (int i = 0; i < VAOs.size(); i++)
			{
				//	
				if (VAOEntry->second->vaoID == VAOs[i]->vaoID)
				{
					//	
					VAOs[i]->geometryTypeMetaDatas.erase(deadGeometryType->geometryType);
					mapGeometryTypeToVAO.erase(VAOEntry);
					break;
				}
			}
		}
	}
}

//	Return the VAOs.
const std::vector<std::shared_ptr<VAOMetaData>>& VAOBackend::getVAOs()
{
	return VAOs;
}

//	Return a VAO for the Geometry Type.
std::shared_ptr<VAOMetaData> VAOBackend::getAvailableVAOforGeometry(std::shared_ptr<RendererGeometryData> newGeometryData)
{
	for (int i = 0; i < VAOs.size(); i++)
	{
		if (VAOs[i]->geometryTypeMetaDatas.size() < 3)
		{
			return VAOs[i];
		}
	}

	std::shared_ptr<VAOMetaData> newVAO = std::make_shared<VAOMetaData>();

	glGenVertexArrays(1, &newVAO->vaoID);

	VAOs.push_back(newVAO);
	
	return newVAO;
}
