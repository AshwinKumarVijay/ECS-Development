#pragma once

#include <vector>
#include <memory>


#include "glm\glm.hpp"

#include "../../RNGs/RNGs.h"
#include "../Vertex/Vertex.h"
#include "../Triangle/Triangle.h"

class TerrainTile
{

public:
	
	//	Default Terrain Tile Constructor.
	TerrainTile(glm::vec3 newTileCenter, float tileSize, int newX, int newY);

	//	Default Terrain Tile Destructor.
	~TerrainTile();
	
	//	Generate the Geometry into the appropriate buffers.
	virtual void generateTerrainTileGeometry(std::vector<std::vector<std::shared_ptr<TerrainTile>>> tilesArray);

	//	Return the Indices.
	virtual const std::vector<int> & getIndices();

	//	Return the VertexData.
	virtual const std::vector<Vertex> & getVertexData();


private:
		
	//	Tile Center.
	glm::vec3 tileCenter;
	float tileSize;

	//	Triangle Mesh.
	std::vector<Triangle> triangleMesh;

	std::vector<int> indices;
	std::vector<Vertex> vertexData;
	std::vector<VertexTextureData> uvData;

	int positionX, positionY;

};
