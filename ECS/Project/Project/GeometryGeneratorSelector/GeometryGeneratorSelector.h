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
#include "../TBM/TBM.h"

class GeometryData;

class GeometryGeneratorSelector
{
public:

	//	Default GeometryGeneratorSelector Constructor.
	GeometryGeneratorSelector();

	//	Default GeometryGeneratorSelector Destructor.
	virtual ~GeometryGeneratorSelector();

	//	Add Comments - TO DO
	virtual void generateGeometry(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, const ResourceDescription & newResouceDescription);

	//	Add Comments - TO DO
	virtual void loadGeometryFromObj(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, std::string geometryName, std::string filename);

	//	Add Comments - TO DO
	virtual void loadGeometryFromTBM(std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & geometryList, std::string geometryName);

};

