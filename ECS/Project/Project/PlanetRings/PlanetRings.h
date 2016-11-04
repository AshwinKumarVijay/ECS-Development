#pragma once
#include <memory>
#include <vector>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"

#include "glm\gtc\matrix_inverse.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "../Vertex/Vertex.h"
#include "../Triangle/Triangle.h"
#include "../RNGs/RNGs.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"


class PlanetRing
{

public:

	//	Default PlanetRings Constructor.
	PlanetRing(const int & newRingsDivisions);

	//	Default PlanetRings Destructor.
	virtual ~PlanetRing();

	//
	virtual void generatePlanetRing(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryDataList, std::string name);

private:
	float ringDivisions;

};

