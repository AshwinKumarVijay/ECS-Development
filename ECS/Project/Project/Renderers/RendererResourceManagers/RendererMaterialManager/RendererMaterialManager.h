#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "glm\glm.hpp"

class MaterialData;

//	
struct RendererMaterialValues
{
	//	The Diffuse Albedo Color.
	glm::vec4 diffuseAlbedo = glm::vec4(1.0);

	//	The Specular Albedo Color.
	glm::vec4 specularAlbedo = glm::vec4(1.0);

	//	The Emissive Color.
	glm::vec4 emissiveColor = glm::vec4(0.0);

	//	Metallic, Roughness and Opacity.
	glm::vec4 metallicRoughnessFresnelOpacity = glm::vec4(1.0, 1.0, 1.0, 1.0);
};


struct RendererMaterialMaps
{
	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	std::string DiffuseAlbedoMap = "NONE";

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	std::string SpecularAlbedoMap = "NONE";

	//	The MetallicRoughnessFresnelOpactiy Map.
	std::string MRFOMap = "NONE";

	//	The Normal Map - No Default Normal Map.
	std::string NormalMap = "NONE";

	//	The Occlusion Map - No Default Occlusion Map.
	std::string OcclusionMap = "NONE";
};


class RendererMaterialManager
{

public:

	//	Default RendererMaterialManager Constructor.
	RendererMaterialManager();

	//	Default RendererMaterialManager Destructor.
	virtual ~RendererMaterialManager();

	//	Add a new Material from provided MaterialData and the Material Name.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData);

	//	View the Material of the specified Name.
	std::shared_ptr<const std::pair<RendererMaterialValues, RendererMaterialMaps>> viewMaterial(const std::string & requestedMaterialName) const;

	//	Update the Material of the Material Name and the specified Material Data.
	virtual void updateMaterial(std::string requestedMaterialName, std::shared_ptr<const MaterialData> newMaterialData);

	//	Delete the Material of the specified Name.
	virtual void deleteMaterial(std::string deadMaterialName);

private:

	//	Map of the Material Names to the Material Data.
	std::map <std::string, std::shared_ptr<std::pair<RendererMaterialValues, RendererMaterialMaps>>> mapNameToMaterialData;

};

