#include "VAOStorage.h"


//	Default VAOStorage Constructor.
VAOStorage::VAOStorage()
{

}

//	Default VAOStorage Destructor.
VAOStorage::~VAOStorage()
{
	//	
	for (auto currentVAO : VAOs)
	{
		currentVAO->geometryTypeMetaDatas.clear();
		glDeleteVertexArrays(1, &currentVAO->vaoID);
	}
}

//	Add the Geometry Type to the VAO Storage.
void VAOStorage::addGeometryType(std::shared_ptr<GeometryTypeMetaData> newGeometryType)
{
	//	Associate the VAO Meta Data with the Geometry Type.
	std::shared_ptr<VAOMetaData> vaoMetaData = getVAOforGeometry();
	newGeometryType->vaoMetaData = vaoMetaData;

	//	Add the Geometry Type to the VAO.
	vaoMetaData->geometryTypeMetaDatas[newGeometryType->geometryType] = newGeometryType;

	//	Create the Buffers.
}

//	Delete the Geometry Type from the VAO Storage.
void VAOStorage::deleteGeometryType(std::shared_ptr<GeometryTypeMetaData> deadGeometryType)
{
	deadGeometryType->vaoMetaData.lock()->geometryTypeMetaDatas.erase(deadGeometryType->geometryType);

	//	Delete the Buffers.
}

//	Get the Available VAO for Geometry.
std::shared_ptr<VAOMetaData> VAOStorage::getVAOforGeometry()
{
	//	
	for (auto currentVAO : VAOs)
	{
		if (currentVAO->geometryTypeMetaDatas.size() < 3)
		{
			return currentVAO;
		}
	}

	//	Construct the new VAO.
	std::shared_ptr<VAOMetaData> newVAO = std::make_shared<VAOMetaData>();
	glGenVertexArrays(1, &newVAO->vaoID);

	//	Add it to the VAOs.
	VAOs.push_back(newVAO);

	return newVAO;
}
