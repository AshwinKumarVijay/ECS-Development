#include "RendererMaterialManager.h"
#include "../Resources/ResourceData/MaterialData/MaterialData.h"

//	Default RendererMaterialManager Constructor.
RendererMaterialManager::RendererMaterialManager()
{

}


//	Default RendererMaterialManager Destructor.
RendererMaterialManager::~RendererMaterialManager()
{

}

//	Add a new Material from provided MaterialData and the Material Name.
void RendererMaterialManager::addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(newMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	TO DO
		//	Throw Already Exists Error.
	}
	else
	{
		//	Create the New Material Values and Material Albedo Maps.
		std::shared_ptr<std::pair<RendererMaterialValues, RendererMaterialMaps>> newRendererMaterialData;
		newRendererMaterialData = std::make_shared<std::pair<RendererMaterialValues, RendererMaterialMaps>>();
		
		//	Copy over the Diffuse Albedo and the Metallic, Roughness, Fresnel and Opactiy.
		newRendererMaterialData->first.diffuseAlbedo = newMaterialData->viewMaterialValues().diffuseAlbdeo;
		newRendererMaterialData->first.specularAlbedo = newMaterialData->viewMaterialValues().specularAlbedo;
		newRendererMaterialData->first.metallicRoughnessFresnelOpacity = newMaterialData->viewMaterialValues().metallicRoughnessFresnelOpacity;

		//	Copy over the Diffuse and Specular Albedo Maps.
		newRendererMaterialData->second.DiffuseAlbedoMap = newMaterialData->viewMaterialMaps().DiffuseAlbedoMap;
		newRendererMaterialData->second.SpecularAlbedoMap = newMaterialData->viewMaterialMaps().SpecularAlbedoMap;

		//	Copy over the MRFO, Normal and Occlusion Maps.
		newRendererMaterialData->second.MRFOMap = newMaterialData->viewMaterialMaps().MRFOMap;
		newRendererMaterialData->second.NormalMap = newMaterialData->viewMaterialMaps().NormalMap;
		newRendererMaterialData->second.OcclusionMap = newMaterialData->viewMaterialMaps().OcclusionMap;
	
		//	Associated the Material Name with the new Material Data.
		mapNameToMaterialData[newMaterialName] = newRendererMaterialData;
	}
}

//	Update the Material of the Material Name and the specified Material Data.
void RendererMaterialManager::updateMaterial(std::string requestedMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(requestedMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Copy over the Diffuse Albedo and the Metallic, Roughness, Fresnel and Opactiy.
		mapNameToMaterialData[requestedMaterialName]->first.diffuseAlbedo = newMaterialData->viewMaterialValues().diffuseAlbdeo;
		mapNameToMaterialData[requestedMaterialName]->first.specularAlbedo = newMaterialData->viewMaterialValues().specularAlbedo;
		mapNameToMaterialData[requestedMaterialName]->first.metallicRoughnessFresnelOpacity = newMaterialData->viewMaterialValues().metallicRoughnessFresnelOpacity;

		//	Copy over the Diffuse and Specular Albedo Maps.
		mapNameToMaterialData[requestedMaterialName]->second.DiffuseAlbedoMap = newMaterialData->viewMaterialMaps().DiffuseAlbedoMap;
		mapNameToMaterialData[requestedMaterialName]->second.SpecularAlbedoMap = newMaterialData->viewMaterialMaps().SpecularAlbedoMap;

		//	Copy over the MRFO, Normal and Occlusion Maps.
		mapNameToMaterialData[requestedMaterialName]->second.MRFOMap = newMaterialData->viewMaterialMaps().MRFOMap;
		mapNameToMaterialData[requestedMaterialName]->second.NormalMap = newMaterialData->viewMaterialMaps().NormalMap;
		mapNameToMaterialData[requestedMaterialName]->second.OcclusionMap = newMaterialData->viewMaterialMaps().OcclusionMap;
	}
	else
	{
		//	TO DO
		//	Throw does not exist error.
	}
}

//	View the Material of the specified Name.
std::shared_ptr<const std::pair<RendererMaterialValues, RendererMaterialMaps>> RendererMaterialManager::viewMaterial(const std::string & requestedMaterialName) const
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(requestedMaterialName);
	
	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Return the Material
		return materialIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw does not exist error.
		return NULL;
	}
}

//	Delete the Material of the specified Name.
void RendererMaterialManager::deleteMaterial(std::string deadMaterialName)
{
	//	Find the Material to see if the Material exists.
	auto materialIterator = mapNameToMaterialData.find(deadMaterialName);

	//	Check if the Material Already Exists.
	if (materialIterator != mapNameToMaterialData.end())
	{
		//	Erase the Material.
		mapNameToMaterialData.erase(materialIterator);
	}
	else
	{
		//	TO DO
		//	Throw does not exist error.
	}
}
