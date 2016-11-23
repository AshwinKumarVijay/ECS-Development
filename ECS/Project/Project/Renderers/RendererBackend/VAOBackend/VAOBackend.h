#pragma once
#include "../../RenderablesMetaData.h"

class VAOBackend
{

public:

	//	Default VAOBackend Constructor.
	VAOBackend();

	//	Default VAOBackend Destructor.
	virtual ~VAOBackend();

	//	Add the Geometry Type Data.
	virtual void addGeometryType(std::shared_ptr<GeometryTypeMetaData> newGeometryType);
	
	//	Update the Geometry Type.
	virtual void updateGeometryType(std::shared_ptr<GeometryTypeMetaData> updatedGeometryType);
	
	//	Delete the Geometry Type.
	virtual void deleteGeometryType(std::shared_ptr<GeometryTypeMetaData> deadGeometryType);


	//	Return the list of VAOs.
	const std::vector<std::shared_ptr<VAOMetaData>> & getVAOs();


private:

	//	Return the VAO for Geometry Type. 
	virtual std::shared_ptr<VAOMetaData> getAvailableVAOforGeometry(std::shared_ptr<RendererGeometryData> newGeometryData);

	//	Map of the Geometry Type to the associated VAO.
	std::map<std::string, std::shared_ptr<VAOMetaData>> mapGeometryTypeToVAO;

	//	Vector of the VAOs.
	std::vector<std::shared_ptr<VAOMetaData>> VAOs;

};

