#include "PlanetRings.h"


//	Default PlanetRings Constructor.
PlanetRing::PlanetRing(const int & newRingsDivisions)
{
	ringDivisions = newRingsDivisions;
}

//	Default PlanetRings Destructor.
PlanetRing::~PlanetRing()
{
	
}

//	Generate Planet Ring.
void PlanetRing::generatePlanetRing(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>>& newGeometryDataList, std::string name)
{
	//	Generate the vectors of data.
	GLenum newGeometryDrawType = GL_LINES;
	std::vector<int> newGeometryIndices;
	std::vector<Vertex> newGeometryVertices;


	float thetaDegreeDivision = glm::pi<float>() * 2.0f / (float)(ringDivisions);

	//	
	for (int i = 0; i < ringDivisions; i++)
	{
			float currentTheta = thetaDegreeDivision * (float)i;

			float x = glm::cos(currentTheta);
			float z = glm::sin(currentTheta);

			float nextTheta = thetaDegreeDivision * (float)(i + 1);

			float nx = glm::cos(nextTheta);
			float nz = glm::sin(nextTheta);
			
			glm::vec3 vA = glm::vec3(x, 0, z);
			glm::vec3 vB = glm::vec3(nx, 0, nz);


			glm::vec3 ringNormal = glm::normalize((vA + vB) / 2.0f);

			newGeometryIndices.push_back(i * 2);
			Vertex currentVertexA;
			currentVertexA.position = glm::vec4(vA, 1.0);
			currentVertexA.normal = glm::vec3(ringNormal);
			currentVertexA.color = glm::vec4(1.0);
			newGeometryVertices.push_back(currentVertexA);


			newGeometryIndices.push_back((i * 2) + 1);
			Vertex currentVertexB;
			currentVertexB.position = glm::vec4(vB, 1.0);
			currentVertexB.normal = glm::vec3(ringNormal);
			currentVertexB.color = glm::vec4(1.0);
			newGeometryVertices.push_back(currentVertexB);
	}
	

	//	
	newGeometryDataList.push_back(std::make_pair(name, std::make_shared<GeometryData>(newGeometryDrawType, newGeometryIndices, newGeometryVertices)));
}
