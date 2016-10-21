#include "GeometryResourceManager.h"
#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ResourceData/GeometryData/GeometryData.h"

//	Default GeometryResourceManager Constructor
GeometryResourceManager::GeometryResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, ModuleType::GEOMETRY_MANAGER)
{
	geometryGeneratorSelector = std::make_shared<GeometryGeneratorSelector>();
}

//	Default GeometryResourceManager Destructor
GeometryResourceManager::~GeometryResourceManager()
{

}

//	Process the provided resource.
void GeometryResourceManager::processResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";

	//	
	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "Geometry")
		{
			//	Get the Resource Name. Used as the Geometry Name.
			newResourceDescription.findProperty("Resource Name", resourceName);

			//	Get the Geometry Type. Used to create the geometry.
			std::string geometryType = "None";
			newResourceDescription.findProperty("Geometry Type", geometryType);

			//	Get the Geometry Filename.
			std::string geometryFilename = "None";
			newResourceDescription.findProperty("Geometry Filename", geometryFilename);

			//	Get the Geometry Parameters.
			std::string geometryParameters = "None";
			newResourceDescription.findProperty("Geometry Parameters", geometryParameters);

			//	Parse OBJS.
			std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> generatedGeometry = geometryGeneratorSelector->generateGeometry(geometryType, geometryFilename, geometryParameters);

			//	
			if (generatedGeometry->size() == 1)
			{
				addGeometry(resourceName, (*generatedGeometry)[0]);
			}
			else
			{
				//	Assuming more than one piece of Geometry was created.
				for (int i = 0; i < generatedGeometry->size(); i++)
				{
					//	Create the new geometry name.
					std::string currentGeometryName = resourceName + " " + std::to_string(i);

					//	Add the new geometry.
					addGeometry(currentGeometryName, (*generatedGeometry)[i]);
				}
			}
		}
	}
	else
	{

	}

}

//	Add the Geometry Data, under the specified name.
void GeometryResourceManager::addGeometry(std::string newGeometryName, std::shared_ptr<GeometryData> newGeometryData)
{
	auto geometryIterator = mapNameToGeometryData.find(newGeometryName);

	if (geometryIterator != mapNameToGeometryData.end())
	{
		//	TO DO
		//	Throw Geometry already present error.
	}
	else
	{
		//	Insert the GeometryData, under the appropriate name.
		mapNameToGeometryData.insert(std::make_pair(newGeometryName, newGeometryData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::GEOMETRY_MANAGER, newGeometryName, newGeometryData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Geometry Data, under the specified name.
void GeometryResourceManager::updateGeometry(std::string currentGeometryName, std::shared_ptr<GeometryData> newGeometryData)
{
	auto geometryIterator = mapNameToGeometryData.find(currentGeometryName);

	if (geometryIterator != mapNameToGeometryData.end())
	{
		geometryIterator->second = newGeometryData;
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_UPDATED, ModuleType::GEOMETRY_MANAGER, currentGeometryName, newGeometryData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find GeometryData error.
	}
}

//	Return the Geometry Data, under the specified name.
std::shared_ptr<GeometryData> GeometryResourceManager::getGeometry(std::string currentGeometryName)
{
	auto geometryIterator = mapNameToGeometryData.find(currentGeometryName);

	if (geometryIterator != mapNameToGeometryData.end())
	{
		return geometryIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find GeometryData error.
		return NULL;
	}
}

//	Return the Geometry Data, under the specified name.
std::shared_ptr<const GeometryData> GeometryResourceManager::viewGeometry(std::string currentGeometryName) const
{
	auto geometryIterator = mapNameToGeometryData.find(currentGeometryName);

	if (geometryIterator != mapNameToGeometryData.end())
	{
		return geometryIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find GeometryData error.
		return NULL;
	}
}

//	Delete the Geometry Data, under the specified name.
void GeometryResourceManager::deleteGeometry(std::string deadGeometryName)
{
	auto geometryIterator = mapNameToGeometryData.find(deadGeometryName);

	if (geometryIterator != mapNameToGeometryData.end())
	{
		mapNameToGeometryData.erase(deadGeometryName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::GEOMETRY_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::GEOMETRY_MANAGER, deadGeometryName, nullptr);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find GeometryData error.
	}
}


