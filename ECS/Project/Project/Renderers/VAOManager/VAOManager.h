#pragma once

#include <map>
#include <memory>
#include <vector>

#include "VAOStorage\VAOStorage.h"

struct RendererGeometryData;

class VAOManager
{

public:

	//	Default VAOManager Constructor.
	VAOManager();

	//	Default VAOManager Destructor.
	virtual ~VAOManager();

	//	Add Geometry to VAO Storage.
	virtual void addGeometryToVAOStorage(std::shared_ptr<RendererGeometryData> newGeometryData);

	//	View VAOs of the Requested Type.
	std::shared_ptr<const std::vector<VAOStorage>> viewVAOsOfType(const int & requestedVAOType);

	//	Update the Geometry.
	virtual void updateGeometry(std::shared_ptr<RendererGeometryData> newGeometryData);

	//	Remove the Geometry from VAO Storage.
	virtual void removeGeometryFromVAOStorage(const std::string & deadGeometryName);

	//	Return the const map of ints to VAO Storage.
	const std::map<int, std::shared_ptr<std::vector<VAOStorage>>> & viewMapVAOTypeToVAOs();

private:

	//	Set the VAO from the Geometry Type.
	virtual void setBoundVAOFormatFromType(const int & geometryType);
	
	//	Map the VAO Type to the list of VAOs that use it.
	std::map<int, std::shared_ptr<std::vector<VAOStorage>>> mapVAOTypeToVAOs;

};

