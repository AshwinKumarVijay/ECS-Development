#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>

#include "GL\glew.h"

#include "glm\glm.hpp"

#include "../Vertex/Vertex.h"

class GeometryData;

struct RendererGeometryData
{
	//	The Name of the Geometry.
	std::string geometryName;

	//	The Type of the Geometry
	//	0 - NO VERTEX INFORMATION
	//	1 - VERTEX BASIC DATA
	//  2 - VERTEX TANGENT BITANGENT DATA
	//	3 - VERTEX TEXTURE COORDINATES ONE
	//	4 - VERTEX TEXTURE COORDINATES TWO
	int geometryDescriptionRepresentation = 0;

	//	The Draw Type of the Geometry.
	GLenum geometryDrawType;

	//	The VAO storing this Geometry.
	unsigned int VAO = 0;

	//	The EBO.
	unsigned int EBO = 0;

	//	The offset into the EBO.
	unsigned int offsetEBO = 0;

	//	The vertexVBO and the offset into the vertexVBO.
	unsigned int vertexVBO = 0;
	unsigned int offsetVertexVBO = 0;

	//	The vertexNormalVBO and the offset into the vertexNormalVBO.
	unsigned int vertexNormalVBO = 0;
	unsigned int offsetVertexNormalVBO = 0;

	//	The vertexTextureVBO and the offset into the vertexVBO.
	unsigned int vertexTextureVBO = 0;
	unsigned int offsetVertexTextureVBO = 0;

	//	The array of indices.
	std::vector<int> indicesArray;

	//	The array of vertices.
	std::vector<Vertex> verticesArray;

	//	The Vertex Normal Data of this Geometry.
	std::vector<VertexNormalData> verticesNormalData;

	//	The Vertex Texture Data of this Geometry.
	std::vector<VertexTextureData> verticesTextureData;
};

class RendererGeometryManager
{

public:
	
	//	Default RendererGeometryManager Constructor.
	RendererGeometryManager();

	//	Default RendererGeometryManager Destructor.
	virtual ~RendererGeometryManager();

	//	Add a Geometry to the RendererGeometryManager, with the specified name and the specified GeometryData.
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData);

	//	Update the Geometry of the specified name, with the specified GeometryData.
	virtual void updateGeometry(std::string requestedGeometryName, std::shared_ptr<const GeometryData> newGeometryData);

	//	Return the Geometry of the specified name.
	std::shared_ptr<RendererGeometryData> getGeometry(std::string requestedGeometryName);

	//	Return the Geometry of the specified name.
	std::shared_ptr<const RendererGeometryData> viewGeometry(std::string requestedGeometryName) const;

	//	Delete the Geometry of the specified name.
	virtual void deleteGeometry(std::string deadGeometryName);


private:

	//	Map the Name to the Geometry Data.
	std::map<std::string, std::shared_ptr<RendererGeometryData>> mapNameToGeometryData;

};

