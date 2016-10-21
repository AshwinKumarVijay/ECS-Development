#pragma once

#include <map>
#include <memory>

#include "../ResourceManager.h"
#include "../GeometryGeneratorSelector/GeometryGeneratorSelector.h"

class GeometryData;

class GeometryResourceManager : public ResourceManager
{
public:

	//	Default GeometryResourceManager Constructor.
	GeometryResourceManager(std::shared_ptr<EventQueue> newEventQueue);
	
	//	Default GeometryResourceManager Destructor.
	virtual ~GeometryResourceManager();

	//	Resource Management Functions.
	virtual void processResource(const ResourceDescription & newResourceDescription);

	//	Add Comments - TO DO
	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<GeometryData> newGeometryData);

	//	Add Comments - TO DO
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<GeometryData> newGeometryData);

	//	Add Comments - TO DO
	std::shared_ptr<GeometryData> getGeometry(std::string currentGeometryName);

	//	Add Comments - TO DO
	std::shared_ptr<const GeometryData> viewGeometry(std::string currentGeometryName) const;

	//	Add Comments - TO DO
	virtual void deleteGeometry(std::string deadGeometryName);


private:

	//	Geometry Generator Selector
	std::shared_ptr<GeometryGeneratorSelector> geometryGeneratorSelector;

	//	Map the Name to the Texture Data.
	std::map<std::string, std::shared_ptr<GeometryData>> mapNameToGeometryData;

};


