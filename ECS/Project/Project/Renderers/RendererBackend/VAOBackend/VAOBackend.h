#pragma once
#include "../../RenderablesMetaData.h"

class VAOBackend
{

public:

	//	Backend of the VAO.
	VAOBackend();

	//	Backend of the VAO.
	virtual ~VAOBackend();

	//	Add the Geometry Type Data.
	std::shared_ptr<GeometryTypeMetaData> addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryData);
	
	//	Update the Geometry Type.
	virtual void updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData);
	
	//	Return the Geometry Type Meta Data.
	std::shared_ptr<GeometryTypeMetaData> getGeometryTypeMetaData(std::string requestedGeometryType);

	//	Delete the Geometry Type.
	virtual void deleteGeometryType(std::string requestedGeometryType);

private:

	

};

