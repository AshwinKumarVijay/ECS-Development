#include "TBM.h"
#include "../ECS/EntityManager/EntityManager.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Transform/Transform.h"
#include "../Components/GeometryComponent/GeometryComponent.h"

//	Default TBM Constructor.
TBM::TBM()
{
	minHeight = 0.0f;
	maxHeight = 25.0f;

	tileSize = 1.0;
	tileCount = 25;
}

//	Default TBM Destructor.
TBM::~TBM()
{

}

//	Generate the Tiles Array.
void TBM::generateTilesArray()
{

	//	Clear out the previous tiles.
	for (int i = 0; i < tilesArray.size(); i++)
	{
		tilesArray[i].clear();
	}

	tilesArray.clear();

	//	Compute the center of the lower left most tile.
	float minXCenter = (((-tileCount / 2.0)) * (tileSize)) + tileSize / 2.0;
	float minYCenter = (((-tileCount / 2.0)) * (tileSize)) + tileSize / 2.0;


	//	Create the empty 2D vector of Tiles, and set the initial positions of the Tiles.
	tilesArray = std::vector<std::vector<std::shared_ptr<TerrainTile>>>(tileCount);
	for (int x = 0; x < tileCount; x++)
	{
		tilesArray[x] = std::vector<std::shared_ptr<TerrainTile>>(tileCount);
		for (int y = 0; y < tileCount; y++)
		{
			float altitude = RNGs::doubleRand(0.0, 5.0);
			glm::vec3 tileCenter = glm::vec3(minXCenter + (((double)x) * tileSize), altitude, minYCenter + (((double)y) * tileSize));
			tilesArray[x][y] = std::make_shared<TerrainTile>(tileCenter, tileSize, x, y);
		}
	}

	//	Generate the Terrain Tile Geometry for each tile.
	for (int x = 0; x < tileCount; x++)
	{
		for (int y = 0; y < tileCount; y++)
		{
			tilesArray[x][y]->generateTerrainTileGeometry(tilesArray);
		}
	}

}

//	Generate the Terrain Geometry.
void TBM::generateTerrainGeometry(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name)
{
	//	Generate the vectors of data.
	GLenum newGeometryDrawType = GL_TRIANGLES;
	std::vector<int> newGeometryIndices;
	std::vector<Vertex> newGeometryVertices;

	//	The current base index, since we are joining together multiple vectors, and need to correctly index.
	int currentBaseIndex = 0;

	//	Iterate over the tiles and fill the vectors.
	for (int x = 0; x < tileCount; x++)
	{
		for (int y = 0; y < tileCount; y++)
		{
			std::shared_ptr<TerrainTile> currentTile = tilesArray[x][y];

			//	
			const std::vector<int> & indices = currentTile->getIndices();
			const std::vector<Vertex> & vertexData = currentTile->getVertexData();

			//	
			for (int i = 0; i < indices.size(); i++)
			{
				newGeometryIndices.push_back(currentBaseIndex + i);
			}

			for (int i = 0; i < vertexData.size(); i++)
			{
				Vertex currentVertex = vertexData[i];
				newGeometryVertices.push_back(vertexData[i]);
			}

			//	
			currentBaseIndex = newGeometryIndices.size();
		}
	}


	//	Construct the GeometryData with Vertex Data.
	std::shared_ptr<GeometryData> newGeometry = std::make_shared<GeometryData>(newGeometryDrawType, newGeometryIndices, newGeometryVertices);
	newGeometryDataList.push_back(std::make_pair(name, newGeometry));
}



