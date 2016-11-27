#include "RendererGeometryManager.h"
#include "../../../Resources/ResourceData/GeometryData/GeometryData.h"

//	Default RendererGeometryManager Constructor
RendererGeometryManager::RendererGeometryManager()
{

}

//	Defualt RendererGeometryManager Destructor
RendererGeometryManager::~RendererGeometryManager()
{

}

//	Add the Geometry.
void RendererGeometryManager::addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(newGeometryName);

	//	Check if the Geometry exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	TO DO
		//	Throw Already Exists Error.
	}
	else
	{
		//	Create the new Geometry.
		std::shared_ptr<RendererGeometryData> newRendererGeometryData = std::make_shared<RendererGeometryData>();

		//	Copy over the Geometry Name.
		newRendererGeometryData->geometryType = newGeometryName;

		//	Copy over the Geometry Description Representation.
		newRendererGeometryData->geometryDescriptionRepresentation = newGeometryData->getGeometryDescriptionRepresentation();

		//	Copy over the Geometry Draw Type.
		newRendererGeometryData->geometryDrawType = newGeometryData->getGeometryDrawType();

		//	Copy over the indices array.
		newRendererGeometryData->indicesArray = std::vector<int>(newGeometryData->viewGeometryIndices());

		//	Copy over the vertices array.
		newRendererGeometryData->verticesArray = std::vector<Vertex>(newGeometryData->viewGeometryVertices());

		//	Copy over the vertices normal data.
		newRendererGeometryData->verticesNormalData = std::vector<VertexNormalData>(newGeometryData->viewGeometryNormalData());

		//	Copy over the vertices texture data.
		newRendererGeometryData->verticesTextureData = std::vector<VertexTextureData>(newGeometryData->viewGeometryTextureData());

		//	Add the Geometry to the Geometry Map.
		mapNameToGeometryData[newGeometryName] = newRendererGeometryData;
	}
}

//	Update the Geometry.
void RendererGeometryManager::updateGeometry(std::string requestedGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if the Geometry exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Create the new Geometry.
		std::shared_ptr<RendererGeometryData> newRendererGeometryData = std::make_shared<RendererGeometryData>();

		//	Copy over the Geometry Name.
		newRendererGeometryData->geometryType = requestedGeometryName;

		//	Copy over the Geometry Draw Type.
		newRendererGeometryData->geometryDrawType = newGeometryData->getGeometryDrawType();

		//	Copy over the indices array.
		newRendererGeometryData->indicesArray = std::vector<int>(newGeometryData->viewGeometryIndices());
		
		//	Copy over the vertices array.
		newRendererGeometryData->verticesArray = std::vector<Vertex>(newGeometryData->viewGeometryVertices());

		//	Copy over the vertices normal data.
		newRendererGeometryData->verticesNormalData = std::vector<VertexNormalData>(newGeometryData->viewGeometryNormalData());

		//	Copy over the vertices texture data.
		newRendererGeometryData->verticesTextureData = std::vector<VertexTextureData>(newGeometryData->viewGeometryTextureData());

		//	Replace the Geometry.
		mapNameToGeometryData[requestedGeometryName] = newRendererGeometryData;
	}
	else
	{
		//	TO DO
		//	Throw Does Not Exist Error.
	}
}

//	Return the Geometry.
std::shared_ptr<RendererGeometryData> RendererGeometryManager::getGeometry(std::string requestedGeometryName)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if the Geometry Exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Return the Geometry.
		return geometryIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw Does Not Exist Error.
		return NULL;
	}
}

//	View the Geometry.
std::shared_ptr<const RendererGeometryData> RendererGeometryManager::viewGeometry(std::string requestedGeometryName) const
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(requestedGeometryName);

	//	Check if it exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Return the Geometry.
		return geometryIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw Does Not Exist Error.
		return NULL;
	}
}

//	Delete the Geometry.
void RendererGeometryManager::deleteGeometry(std::string deadGeometryName)
{
	//	Find the Geometry.
	auto geometryIterator = mapNameToGeometryData.find(deadGeometryName);

	//	Check if it exists.
	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	Erase the geometry.
		mapNameToGeometryData.erase(deadGeometryName);
	}
	else
	{
		//	TO DO
		//	Throw Does Not Exist Error.
	}
}
