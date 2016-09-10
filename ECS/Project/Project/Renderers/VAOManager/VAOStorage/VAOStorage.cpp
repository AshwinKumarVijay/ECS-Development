#include "VAOStorage.h"
#include "../../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"

//	Default VAOStorage Constructor
VAOStorage::VAOStorage()
{
	vaoID = 0;
}


//	Default VAOStorage Destructor
VAOStorage::~VAOStorage()
{

}

//	Create and initialize the VAO.
void VAOStorage::initializeVAO()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

}

//	Add the Geometry to the list of Geometry stored in this VAO
void VAOStorage::addGeometryToStorage(std::shared_ptr<RendererGeometryData> newGeometry)
{
	newGeometry->VAO = vaoID;
	glBindVertexArray(vaoID);


	//	Generate a new EBO for the Indices.
	glGenBuffers(1, &newGeometry->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeometry->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, newGeometry->indicesArray.size() * sizeof(GLuint), newGeometry->indicesArray.data(), GL_STATIC_DRAW);
	newGeometry->offsetEBO = 0;

	//	Generate a new VBO for the Vertices.
	glGenBuffers(1, &newGeometry->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, newGeometry->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, newGeometry->verticesArray.size() * sizeof(Vertex), newGeometry->verticesArray.data(), GL_STATIC_DRAW);
	newGeometry->offsetVertexVBO = 0;

	//	Check if we need to create a VBO for Normal Data.
	if ((newGeometry->geometryDescriptionRepresentation & 2) == 2)
	{
		//	Generate a new Vertex Normal VBO for the Vertices.
		glGenBuffers(1, &newGeometry->vertexNormalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, newGeometry->vertexNormalVBO);
		glBufferData(GL_ARRAY_BUFFER, newGeometry->verticesNormalData.size() * sizeof(VertexNormalData), newGeometry->verticesNormalData.data(), GL_STATIC_DRAW);
		newGeometry->offsetVertexNormalVBO = 0;
	}

	//	Check if need to create a VBO for the Texture Coordinates.
	if ((newGeometry->geometryDescriptionRepresentation & 4) == 4)
	{
		//	Generate a new Vertex Normal VBO for the Vertices.
		glGenBuffers(1, &newGeometry->vertexTextureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, newGeometry->vertexTextureVBO);
		glBufferData(GL_ARRAY_BUFFER, newGeometry->verticesTextureData.size() * sizeof(VertexTextureData), newGeometry->verticesTextureData.data(), GL_STATIC_DRAW);
		newGeometry->offsetVertexTextureVBO = 0;
	}

	geometryNames.push_back(newGeometry->geometryName);
	rendererGeometryDatas.push_back(newGeometry);

	//	Unbind All BUffers.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//	Return the VAO ID.
GLuint VAOStorage::getVAOID() const
{
	return vaoID;
}

//	View the list of Geometry Names being stored in this VAO.
const std::vector<std::string>& VAOStorage::viewGeometryNames() const
{
	return geometryNames;
}

//	Return the Geometry Datas being stored in this VAO.
const std::vector<std::shared_ptr<RendererGeometryData>> & VAOStorage::viewGeometryDatas() const
{
	return rendererGeometryDatas;
}

//	Remove the Geometry from Storage.	
void VAOStorage::removeGeometryFromStorage(std::string deadGeometryName)
{
	//	Iterate over the Geometry Names.
	for (int i = 0; i < geometryNames.size(); i++)
	{
		//	Check if this is the Geometry Name.
		if (geometryNames[i] == deadGeometryName)
		{
			//	Erase the Geometry Name from the Geometry Names List.
			geometryNames.erase(geometryNames.begin() + i);

			//	Erase the Geometry Data Associated.
			rendererGeometryDatas.erase(rendererGeometryDatas.begin() + i);

			//	Break.
			break;
		}
	}
}

//	Delete the VAO associated with this VAOStorage.
void VAOStorage::deleteVAO()
{
	//	Clear the VAO.
	clearVAO();

	//	Delete the VAO.
	glDeleteVertexArrays(1, &vaoID);
	
	//	Reset the VAO ID.
	vaoID = 0;
}

//	Clear the VAO
void VAOStorage::clearVAO()
{
	//	Check if we have any Geometry.
	while (geometryNames.size() > 0)
	{
		//	
		std::shared_ptr<RendererGeometryData> deadGeometryData = rendererGeometryDatas[0];

		glDeleteBuffers(1, &deadGeometryData->EBO);
		glDeleteBuffers(1, &deadGeometryData->vertexVBO);
		glDeleteBuffers(1, &deadGeometryData->vertexNormalVBO);
		glDeleteBuffers(1, &deadGeometryData->vertexTextureVBO);

		//	
		geometryNames.erase(geometryNames.begin() + 0);

		//	
		rendererGeometryDatas.erase(rendererGeometryDatas.begin() + 0);
	}
}

