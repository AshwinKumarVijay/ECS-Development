#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>
#include <memory>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"

#include "glm\gtc\matrix_inverse.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "../RNGs/RNGs.h"
#include "../Vertex/Vertex.h"

class GeometryData;


struct IcosphereTriangleIndices
{
	int v1;
	int v2;
	int v3;

	IcosphereTriangleIndices(int v1, int v2, int v3)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
};

class Icosphere
{

public:
	
	//	Default Icosphere Constructor.
	Icosphere(int newLevels, int newRoughness);

	//	Default Icosphere Destructor.
	virtual ~Icosphere();

	//	Generate the Icosphere Geometry, with per vertex normal.
	virtual void generateIcosphereGeometryPerVertex(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name);

	//	Generate the Icosphere Geometry, with per face normal.
	virtual void generateIcosphereGeometryPerFace(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name);


private:

	//	Refine the Icopshere.
	void refineIcosphere(int levels);

	//	Get the index of the middle point.
	int constructMiddlePoint(int point1, int point2);

	//	Return the Face Normal of the Triangle.
	glm::vec3 getFaceNormal(const IcosphereTriangleIndices & face);

	//	Add the Vertex.
	int addVertex(const glm::vec3 & newVertex);

	//	The list of vertices, and indices.
	std::vector<glm::vec3> vertices;
	std::vector<int> indices;

	//	The list of faces.
	std::vector<std::shared_ptr<IcosphereTriangleIndices>> faces;

	//	The Middle Point Index Cache.
	std::map<std::pair<int, int>, int> middlePointIndexCache;

	//	The Final Mesh Vertices.
	std::vector<Vertex> finalMeshVertices;

	//	The Final Mesh Indices.
	std::vector<int> finalMeshIndices;

	//	Index.
	int index;

	int roughness;

};

