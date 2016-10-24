#pragma once
#include <memory>
#include <vector>

#include "../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../Vertex/Vertex.h"
#include "TerrainTile\TerrainTile.h"
#include "../RNGs/RNGs.h"

class EntityManager;
class Entity;

class GeometryData;

class TBM
{

public:

	//	Terrain Block Maker Constructor.
	TBM();

	//	Teraain Block Maker Destructor.
	virtual ~TBM();

	//	Generate the Tiles Array.
	virtual void generateTilesArray();
	
	//	Generate the Terrain Geometry.
	virtual void generateTerrainGeometry(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name);



private:

	//	
	float minHeight;
	float maxHeight;
	float tileSize;
	float tileCount;

	//	The Array of Tiles that make up the Terrain.
	std::vector<std::vector<std::shared_ptr<TerrainTile>>> tilesArray;
		
};

