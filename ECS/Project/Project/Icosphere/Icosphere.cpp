#include "Icosphere.h"
#include "GL\glew.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"
//	
Icosphere::Icosphere(int newLevels, int newRoughness)
{
	index = 0;
	vertices.clear();
	indices.clear();
	faces.clear();
	middlePointIndexCache.clear();
	finalMeshIndices.clear();
	finalMeshVertices.clear();

	roughness = newRoughness;
	if (roughness > 100)
		roughness = 100;
	if (roughness < 0)
		roughness = 0;

	float t = (1.0f + sqrt(5.0f)) / 2.0f;

	//	0
	addVertex(glm::vec3(-1.0, t, 0.0));

	//	1
	addVertex(glm::vec3(1.0, t, 0.0));

	//	2
	addVertex(glm::vec3(-1.0, -t, 0.0));

	//	3
	addVertex(glm::vec3(1.0, -t, 0.0));

	//	4
	addVertex(glm::vec3(0, -1.0, t));

	//	5
	addVertex(glm::vec3(0, 1.0, t));

	//	6
	addVertex(glm::vec3(0, -1.0, -t));

	//	7
	addVertex(glm::vec3(0, 1.0, -t));

	//	8
	addVertex(glm::vec3(t, 0.0, -1.0));

	//	9
	addVertex(glm::vec3(t, 0.0, 1.0));

	//	10
	addVertex(glm::vec3(-t, 0.0, -1.0));

	//	11
	addVertex(glm::vec3(-t, 0.0, 1.0));


	faces = std::vector<std::shared_ptr<IcosphereTriangleIndices>>();
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(0, 11, 5));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(0, 5, 1));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(0, 1, 7));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(0, 7, 10));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(0, 10, 11));

	faces.push_back(std::make_shared<IcosphereTriangleIndices>(1, 5, 9));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(5, 11, 4));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(11, 10, 2));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(10, 7, 6));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(7, 1, 8));

	faces.push_back(std::make_shared<IcosphereTriangleIndices>(3, 9, 4));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(3, 4, 2));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(3, 2, 6));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(3, 6, 8));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(3, 8, 9));

	faces.push_back(std::make_shared<IcosphereTriangleIndices>(4, 9, 5));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(2, 4, 11));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(6, 2, 10));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(8, 6, 7));
	faces.push_back(std::make_shared<IcosphereTriangleIndices>(9, 8, 1));

	refineIcosphere(newLevels);
}

//	
Icosphere::~Icosphere()
{

}

//	
void Icosphere::refineIcosphere(int levels)
{

	for (int count = 0; count < levels; count++)
	{
		auto next_faces = std::vector<std::shared_ptr<IcosphereTriangleIndices>>();

		for (auto current_triangle : faces)
		{

			int v1 = constructMiddlePoint(current_triangle->v1, current_triangle->v2);
			int v2 = constructMiddlePoint(current_triangle->v2, current_triangle->v3);
			int v3 = constructMiddlePoint(current_triangle->v3, current_triangle->v1);

			next_faces.push_back(std::make_shared<IcosphereTriangleIndices>(current_triangle->v1, v1, v3));
			next_faces.push_back(std::make_shared<IcosphereTriangleIndices>(current_triangle->v2, v2, v1));
			next_faces.push_back(std::make_shared<IcosphereTriangleIndices>(current_triangle->v3, v3, v2));
			next_faces.push_back(std::make_shared<IcosphereTriangleIndices>(v1, v2, v3));
		}



		faces.clear();

		for (unsigned int count2 = 0; count2 < next_faces.size(); count2++)
		{
			faces.push_back(next_faces[count2]);
		}

		next_faces.clear();
	}
}

//	Generate the Icosphere Geometry per Vertex.	
void Icosphere::generateIcosphereGeometryPerVertex(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name)
{
	//	Generate the vectors of data.
	GLenum newGeometryDrawType = GL_TRIANGLES;
	std::vector<int> newGeometryIndices;
	std::vector<Vertex> newGeometryVertices;

	finalMeshVertices.clear();
	finalMeshIndices.clear();

	for (auto &current_vertex : vertices)
	{
		if (roughness != 0)
		{
			current_vertex.x = current_vertex.x + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
			current_vertex.y = current_vertex.y + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
			current_vertex.z = current_vertex.z + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
		}
	}


	//	Iterate over the vertices, and create vertices.
	for (auto current_vertex : vertices)
	{
		Vertex finalMeshVertex;
		finalMeshVertex.position = glm::vec4(current_vertex, 1.0);
		finalMeshVertex.normal = glm::vec3(0.0, 0.0, 0.0);
		finalMeshVertex.color = glm::vec4(1.0);
		finalMeshVertices.push_back(finalMeshVertex);
	}

	//	Iterate over the faces.
	for (auto current_triangle : faces)
	{

		glm::vec3 current_normal = getFaceNormal(*current_triangle);

		finalMeshIndices.push_back(current_triangle->v1);
		finalMeshIndices.push_back(current_triangle->v2);
		finalMeshIndices.push_back(current_triangle->v3);

		finalMeshVertices[current_triangle->v1].normal += current_normal;
		finalMeshVertices[current_triangle->v2].normal += current_normal;
		finalMeshVertices[current_triangle->v3].normal += current_normal;
	}

	//	Iterate over the vertices.
	for (auto current_finalMeshVertex : finalMeshVertices)
	{
		current_finalMeshVertex.normal = normalize(current_finalMeshVertex.normal);
		newGeometryVertices.push_back(current_finalMeshVertex);
	}

	//	Iterate over the indices.
	int initialSize = (int)newGeometryIndices.size();
	for (auto current_finalMeshIndex : finalMeshIndices)
	{
		newGeometryIndices.push_back(initialSize + current_finalMeshIndex);
	}

	newGeometryDataList.push_back(std::make_pair(name, std::make_shared<GeometryData>(GL_TRIANGLES, newGeometryIndices, newGeometryVertices)));
}

//	Generate the Icosphere Geometry per Face.
void Icosphere::generateIcosphereGeometryPerFace(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name)
{

	//	Generate the vectors of data.
	GLenum newGeometryDrawType = GL_TRIANGLES;
	std::vector<int> newGeometryIndices;
	std::vector<Vertex> newGeometryVertices;

	finalMeshVertices.clear();
	finalMeshIndices.clear();

	int indicesCount = 0;
	Vertex finalMeshVertex;

	for (auto &current_vertex : vertices)
	{
		if (roughness != 0)
		{
			current_vertex.x = current_vertex.x + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
			current_vertex.y = current_vertex.y + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
			current_vertex.z = current_vertex.z + (float)(RNGs::doubleRand(0.0, 1.0) * (roughness / 100.0));
		}
	}

	for (auto current_triangle : faces)
	{
		glm::vec3 current_normal = getFaceNormal(*current_triangle);

		//	First Vertex of the Triangle
		finalMeshVertex.position = glm::vec4(vertices[current_triangle->v1], 1.0);
		finalMeshVertex.normal = current_normal;
		finalMeshVertex.color = glm::vec4(1.0);
		finalMeshVertices.push_back(finalMeshVertex);
		finalMeshIndices.push_back(indicesCount);
		indicesCount++;

		//	Second Vertex of the Triangle
		finalMeshVertex.position = glm::vec4(vertices[current_triangle->v2], 1.0);
		finalMeshVertex.normal = current_normal;
		finalMeshVertex.color = glm::vec4(1.0);
		finalMeshVertices.push_back(finalMeshVertex);
		finalMeshIndices.push_back(indicesCount);
		indicesCount++;

		//	Third Vertex of the Triangle
		finalMeshVertex.position = glm::vec4(vertices[current_triangle->v3], 1.0);
		finalMeshVertex.normal = current_normal;
		finalMeshVertex.color = glm::vec4(1.0);
		finalMeshVertices.push_back(finalMeshVertex);
		finalMeshIndices.push_back(indicesCount);
		indicesCount++;
	}

	for (auto current_finalMeshVertex : finalMeshVertices)
	{
		current_finalMeshVertex.normal = normalize(current_finalMeshVertex.normal);
		newGeometryVertices.push_back(current_finalMeshVertex);
	}

	int initialSize = (int)newGeometryIndices.size();
	for (auto current_finalMeshIndex : finalMeshIndices)
	{
		newGeometryIndices.push_back(initialSize + current_finalMeshIndex);
	}


	newGeometryDataList.push_back(std::make_pair(name, std::make_shared<GeometryData>(GL_TRIANGLES, newGeometryIndices, newGeometryVertices)));

}

//	
int Icosphere::constructMiddlePoint(int point1, int point2)
{
	int smallerIndex = point1 < point2 ? point1 : point2;
	int largerIndex = point1 < point2 ? point2 : point1;
	auto key = std::make_pair(smallerIndex, largerIndex);
	auto valueLocater = middlePointIndexCache.find(key);
	if (valueLocater != middlePointIndexCache.end())
	{
		return valueLocater->second;
	}

	glm::vec3 vertex1 = vertices[point1];
	glm::vec3 vertex2 = vertices[point2];
	glm::vec3 middle = glm::vec3((vertex1.x + vertex2.x) / 2.0, (vertex1.y + vertex2.y) / 2.0, (vertex1.z + vertex2.z) / 2.0);

	int newVertexIndex = this->addVertex(middle);
	this->middlePointIndexCache.insert(std::make_pair(key, newVertexIndex));
	return newVertexIndex;
}

//	
int Icosphere::addVertex(const glm::vec3 & newVertex)
{
	glm::vec3 normalizedVertex = normalize(newVertex);
	vertices.push_back(normalizedVertex);
	return index++;
}

//	
glm::vec3 Icosphere::getFaceNormal(const IcosphereTriangleIndices & face)
{
	glm::vec3 point1 = vertices[face.v1];
	glm::vec3 point2 = vertices[face.v2];
	glm::vec3 point3 = vertices[face.v3];

	glm::vec3 edge1 = point2 - point1;
	glm::vec3 edge2 = point3 - point1;

	glm::vec3 normal = normalize(cross(edge1, edge2));

	return normal;
}
