#pragma once

#include <memory>
#include <map>
#include <vector>
#include <cerrno>
#include <iostream>
#include <string>

#include "glm\glm.hpp"


#include "../Vertex/Vertex.h"
#include "../RDFP/ResourceDescription.h"

#include "TinyObjLoader\tiny_obj_loader.h"
#include "../Icosphere/Icosphere.h"
#include "../PlanetRings/PlanetRings.h"

class GeometryData;

class GeometryGeneratorSelector
{
public:

	//	Default GeometryGeneratorSelector Constructor.
	GeometryGeneratorSelector();

	//	Default GeometryGeneratorSelector Destructor.
	virtual ~GeometryGeneratorSelector();

	//	Generate the Geometry from the provided Resource Description.
	virtual void generateGeometry(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, const ResourceDescription & newResouceDescription);

	//	Load the Geometry from the Obj.
	virtual void loadGeometryFromObj(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, std::string geometryName, const ResourceDescription & newResourceDescription);

	//	Generate geometry from an Icosphere.
	virtual void loadGeometryFromIcosphere(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, std::string geometryName, const ResourceDescription & newResourceDescription);

	//	Generate geometry from a PlanetRing Maker.
	virtual void loadGeometryFromPlanetRing(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, std::string geometryName, const ResourceDescription & newResourceDescription);

};

