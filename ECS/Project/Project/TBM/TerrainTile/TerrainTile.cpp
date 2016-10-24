#include "TerrainTile.h"

//	Default TerrainTile Constructor.
TerrainTile::TerrainTile(glm::vec3 newTileCenter, float newTileSize, int newX, int newY)
{
	tileCenter = newTileCenter;
	tileSize = newTileSize;

	positionX = newX;
	positionY = newY;
}

//	Default TerrainTile Destructor. 
TerrainTile::~TerrainTile()
{

}

//	Generate the Terrain Tile Geometry.
void TerrainTile::generateTerrainTileGeometry(std::vector<std::vector<std::shared_ptr<TerrainTile>>> tilesArray)
{

	//	
	std::shared_ptr<TerrainTile> currentNorth = NULL;
	std::shared_ptr<TerrainTile> currentSouth = NULL;
	std::shared_ptr<TerrainTile> currentEast = NULL;
	std::shared_ptr<TerrainTile> currentWest = NULL;

	if (positionX + 1 < tilesArray.size())
		currentEast = tilesArray[positionX + 1][positionY];

	if (positionX - 1 >= 0)
		currentWest = tilesArray[positionX - 1][positionY];

	if (positionY + 1 < tilesArray.size())
		currentNorth = tilesArray[positionX][positionY + 1];

	if (positionY - 1 >= 0)
		currentSouth = tilesArray[positionX][positionY - 1];


	//	
	glm::vec3 northEastCorner = glm::vec3(1.0 * tileSize / 2.0, 0.0, 1.0 * tileSize / 2.0);
	glm::vec3 northWestCorner = glm::vec3(-1.0 * tileSize / 2.0, 0.0, 1.0 * tileSize / 2.0);
	glm::vec3 southWestCorner = glm::vec3(-1.0 * tileSize / 2.0, 0.0, -1.0 * tileSize / 2.0);
	glm::vec3 southEastCorner = glm::vec3(1.0 * tileSize / 2.0, 0.0, -1.0 * tileSize / 2.0);

	northEastCorner.x = tileCenter.x + northEastCorner.x;
	northEastCorner.z = tileCenter.z + northEastCorner.z;

	northWestCorner.x = tileCenter.x + northWestCorner.x;
	northWestCorner.z = tileCenter.z + northWestCorner.z;

	southWestCorner.x = tileCenter.x + southWestCorner.x;
	southWestCorner.z = tileCenter.z + southWestCorner.z;

	southEastCorner.x = tileCenter.x + southEastCorner.x;
	southEastCorner.z = tileCenter.z + southEastCorner.z;


	{
		//	Compute the Altitude of the North East Corner of the Tile.
		float NEAltitude = tileCenter.y;
		float averageCount = 1.0;

		if (positionX + 1 < tilesArray.size() && positionY + 1 < tilesArray.size())
		{
			NEAltitude += tilesArray[positionX + 1][positionY + 1]->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentEast != NULL)
		{
			NEAltitude += currentEast->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentNorth != NULL)
		{
			NEAltitude += currentNorth->tileCenter.y;
			averageCount += 1.0;
		}

		
		northEastCorner.y = NEAltitude / averageCount;
	}


	{
		//	Compute the Altitude of the North West Corner of the Tile.
		float NWAltitude = tileCenter.y;
		float averageCount = 1.0;

		if (positionX - 1 >= 0 && positionY + 1 < tilesArray.size())
		{
			NWAltitude += tilesArray[positionX - 1][positionY + 1]->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentWest != NULL)
		{
			NWAltitude += currentWest->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentNorth != NULL)
		{
			NWAltitude += currentNorth->tileCenter.y;
			averageCount += 1.0;
		}

		northWestCorner.y = NWAltitude / averageCount;
	}


	{
		//	Compute the Altitude of the South West Corner of the Tile.
		float SWAltitude = tileCenter.y;
		float averageCount = 1.0;

		if (positionX - 1 >= 0 && positionY - 1 >= 0)
		{
			SWAltitude += tilesArray[positionX - 1][positionY - 1]->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentWest != NULL)
		{
			SWAltitude += currentWest->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentSouth != NULL)
		{
			SWAltitude += currentSouth->tileCenter.y;
			averageCount += 1.0;
		}

		southWestCorner.y = SWAltitude / averageCount;
	}


	{
		//	Compute the Altitude of the South East Corner of the Tile.
		float SEAltitude = tileCenter.y;
		float averageCount = 1.0;

		if (positionX + 1 < tilesArray.size() && positionY - 1 >= 0)
		{
			SEAltitude += tilesArray[positionX + 1][positionY - 1]->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentEast != NULL)
		{
			SEAltitude += currentEast->tileCenter.y;
			averageCount += 1.0;
		}

		if (currentSouth != NULL)
		{
			SEAltitude += currentSouth->tileCenter.y;
			averageCount += 1.0;
		}

		southEastCorner.y = SEAltitude / averageCount;
	}



	Triangle triangle = Triangle(southWestCorner, northWestCorner, northEastCorner);
	triangle.computeFaceNormal();
	triangleMesh.push_back(triangle);

	triangle = Triangle(southWestCorner, northEastCorner, southEastCorner);
	triangle.computeFaceNormal();
	triangleMesh.push_back(triangle);

	indices.clear();
	vertexData.clear();


	for (int i = 0; i < triangleMesh.size(); i++)
	{
		//	Add Vertex A.
		indices.push_back(i * 3);
		Vertex vertexA;
		vertexA.position = glm::vec4(triangleMesh[i].getA(), 1.0);
		vertexA.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		vertexA.normal = glm::vec3(triangleMesh[i].computeFaceNormal());
		vertexData.push_back(vertexA);

		//	Add Vertex B.
		indices.push_back((i * 3) + 1);
		Vertex vertexB;
		vertexB.position = glm::vec4(triangleMesh[i].getB(), 1.0);
		vertexB.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		vertexB.normal = glm::vec3(triangleMesh[i].computeFaceNormal());
		vertexData.push_back(vertexB);


		//	Add Vertex C.
		indices.push_back((i * 3) + 2);
		Vertex vertexC;
		vertexC.position = glm::vec4(triangleMesh[i].getC(), 1.0);
		vertexC.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		vertexC.normal = glm::vec3(triangleMesh[i].computeFaceNormal());
		vertexData.push_back(vertexC);

	}
}

//	Return the Indices.
const std::vector<int>& TerrainTile::getIndices()
{
	return indices;
}

//	Return the Vertex.
const std::vector<Vertex>& TerrainTile::getVertexData()
{
	return vertexData;
}
