#pragma once

#include <memory>
#include <map>
#include <vector>
#include <cerrno>
#include <iostream>
#include <string>

#include "glm\glm.hpp"

#include "TinyObjLoader\tiny_obj_loader.h"
#include "../Vertex/Vertex.h"

class GeometryData;

class GeometryGeneratorSelector
{
public:

	//	Default GeometryGeneratorSelector Constructor.
	GeometryGeneratorSelector();

	//	Default GeometryGeneratorSelector Destructor.
	virtual ~GeometryGeneratorSelector();

	//	Generate the Geometry of the GeometryType, the Object Filename and the Parameters.
	std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> generateGeometry(std::string geometryType, std::string objFileName, std::string parameters);

	//	Load the Object From the provided Filen, as specified by filename.
	virtual void loadObjectFromFile(std::string objFileName, std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> newGeometryData);

};

