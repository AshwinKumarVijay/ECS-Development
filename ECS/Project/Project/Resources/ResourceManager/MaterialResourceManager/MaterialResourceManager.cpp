#include "MaterialResourceManager.h"
#include "../../ResourceData/ResourceData.h"
#include "../../ResourceData/MaterialData/MaterialData.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"


//	Default MaterialResourceManager Constructor
MaterialResourceManager::MaterialResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, ModuleType::MATERIAL_MANAGER)
{


}

//	Default MaterialResourceManager Destructor
MaterialResourceManager::~MaterialResourceManager()
{


}

//	Process the provided resource.
void MaterialResourceManager::processResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";

	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "Material")
		{
			newResourceDescription.findProperty("Resource Name", resourceName);

			//	Get the Diffuse Albedo Values.
			std::string diffuseAlbedoLine = "1.0, 1.0, 1.0, 1.0";
			newResourceDescription.findProperty("Material Diffuse Albedo", diffuseAlbedoLine);
			std::vector<std::string> diffuseAlbedoLineValues = StringModifiers::split_string(diffuseAlbedoLine, ",");
			glm::vec4 diffuseAlbedoValues = glm::vec4(std::stof(diffuseAlbedoLineValues[0]), std::stof(diffuseAlbedoLineValues[1]), std::stof(diffuseAlbedoLineValues[2]), std::stof(diffuseAlbedoLineValues[3]));

			//	Get the Specular Albedo Values.
			std::string specularAlbedoLine = "1.0, 1.0, 1.0, 1.0";
			newResourceDescription.findProperty("Material Specular Albedo", specularAlbedoLine);
			std::vector<std::string> specularAlbedoLineValues = StringModifiers::split_string(specularAlbedoLine, ",");
			glm::vec4 specularAlbedoValues = glm::vec4(std::stof(specularAlbedoLineValues[0]), std::stof(specularAlbedoLineValues[1]), std::stof(specularAlbedoLineValues[2]), std::stof(specularAlbedoLineValues[3]));

			//	Get the Emissive Color Values.
			std::string emissiveColorLine = "0.0, 0.0, 0.0, 0.0";
			newResourceDescription.findProperty("Material Emissive Albedo", emissiveColorLine);
			std::vector<std::string> emissiveColorLineValues = StringModifiers::split_string(emissiveColorLine, ",");
			glm::vec4 emissiveColorValues = glm::vec4(std::stof(emissiveColorLineValues[0]), std::stof(emissiveColorLineValues[1]), std::stof(emissiveColorLineValues[2]), std::stof(emissiveColorLineValues[3]));

			//	Get the Metallic, Roughness and Opacity Values.
			std::string metallicRoughnessFresnelOpacityLine = "1.0, 1.0, 1.0, 1.0";
			newResourceDescription.findProperty("Material Metallicness Roughness and Opacity", metallicRoughnessFresnelOpacityLine);
			std::vector<std::string> metallicRoughnessOpacityLineValues = StringModifiers::split_string(metallicRoughnessFresnelOpacityLine, ",");
			glm::vec4 metallicRoughnessFresnelOpacityValues = glm::vec4(std::stof(metallicRoughnessOpacityLineValues[0]), std::stof(metallicRoughnessOpacityLineValues[1]), std::stof(metallicRoughnessOpacityLineValues[2]), std::stof(metallicRoughnessOpacityLineValues[3]));

			//	Get the Diffuse Albedo Map Value.
			std::string diffuseAlbedoMapLine = "None";
			newResourceDescription.findProperty("Material Diffuse Albedo Map", diffuseAlbedoMapLine);

			//	Get the Specular Albedo Map Value.
			std::string specularAlbedoMapLine = "None";
			newResourceDescription.findProperty("Material Specular Albedo Map", specularAlbedoMapLine);

			std::string MRFOMapLine = "None";
			newResourceDescription.findProperty("Material MRFO Map", specularAlbedoMapLine);

			//	Get the Normal Map Value.
			std::string normalMapLine = "None";
			newResourceDescription.findProperty("Material Normal Map", normalMapLine);

			//	Get the Occlusion Map Value.
			std::string occlusionMapLine = "None";
			newResourceDescription.findProperty("Material Occlusion Map", occlusionMapLine);

			//	Create the new Material Values.
			MaterialValues newMaterialValues;
			newMaterialValues.diffuseAlbdeo = diffuseAlbedoValues;
			newMaterialValues.specularAlbedo = specularAlbedoValues;
			newMaterialValues.emissiveColor = emissiveColorValues;
			newMaterialValues.metallicRoughnessFresnelOpacity = metallicRoughnessFresnelOpacityValues;

			//	Create the new Material Maps.
			MaterialMaps newMaterialMaps;
			newMaterialMaps.DiffuseAlbedoMap = "NONE";
			newMaterialMaps.SpecularAlbedoMap = "NONE";
			newMaterialMaps.MRFOMap = "NONE";
			newMaterialMaps.NormalMap = "NONE";
			newMaterialMaps.OcclusionMap = "NONE";

			//	Add it to the Material Manager.
			std::shared_ptr<MaterialData> newMaterialData = std::make_shared<MaterialData>(newMaterialValues, newMaterialMaps);
			addMaterial(resourceName, newMaterialData);
		}
	}
	else
	{

	}
}

//	Add a Material to the Material Resource Manager, specified by name.
void MaterialResourceManager::addMaterial(std::string newMaterialName, std::shared_ptr<MaterialData> newMaterialData)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(newMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		//	TO DO
		//	Throw Material already present error.
	}
	else
	{
		//	Insert the MaterialData, under the appropriate name.
		mapNameToMaterialData.insert(std::make_pair(newMaterialName, newMaterialData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_ADDED, ModuleType::MATERIAL_MANAGER, newMaterialName, std::dynamic_pointer_cast<const ResourceData>(newMaterialData));
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Material in the Material Resource Manager, specified by name.
void MaterialResourceManager::updateMaterial(std::string currentMaterialName, std::shared_ptr<MaterialData> newMaterialData)
{

	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		materialIterator->second = newMaterialData;
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_UPDATED, ModuleType::MATERIAL_MANAGER, currentMaterialName, newMaterialData);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
	}

}

//	Return the Material in the Material Resource Manager, specified by name.
std::shared_ptr<MaterialData> MaterialResourceManager::getMaterial(std::string currentMaterialName)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		return materialIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
		return NULL;
	}
}

//	Return the Material in the Material Resource Manager, specified by name. Return a const pointer.
std::shared_ptr<const MaterialData> MaterialResourceManager::viewMaterial(std::string currentMaterialName) const
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(currentMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		return materialIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
		return NULL;
	}
}

//	Delete the Material in the MaterialResourceManager.
void MaterialResourceManager::deleteMaterial(std::string deadMaterialName)
{
	//	Find the Material.
	auto materialIterator = mapNameToMaterialData.find(deadMaterialName);

	if (materialIterator != mapNameToMaterialData.end())
	{
		mapNameToMaterialData.erase(deadMaterialName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::MATERIAL_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, ModuleType::MATERIAL_MANAGER, deadMaterialName, nullptr);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find MaterialData error.
	}
}
