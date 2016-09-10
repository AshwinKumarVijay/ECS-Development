#pragma once

#include <string>
#include "glm\glm.hpp"
#include "../ResourceData.h"

//	
struct MaterialValues
{
	//	The Diffuse Albedo Color.
	glm::vec4 diffuseAlbdeo = glm::vec4(1.0);

	//	The Specular Albedo Color.
	glm::vec4 specularAlbedo = glm::vec4(1.0);

	//	The Emissive Color.
	glm::vec4 emissiveColor = glm::vec4(0.0);

	//	Metallic, Roughness and Opacity.
	glm::vec4 metallicRoughnessFresnelOpacity = glm::vec4(1.0, 1.0, 1.0, 1.0);
};

//	
struct MaterialMaps
{
	//	The Diffuse Albedo Map - No Default Diffuse Albedo Map.
	std::string DiffuseAlbedoMap = "NONE";

	//	The Specular Albedo Map - No Default Specular Albedo Map.
	std::string SpecularAlbedoMap = "NONE";

	//	The Metallicness, Roughness, Fresnel and Opacity.
	std::string MRFOMap = "NONE";

	//	The Normal Map - No Default Normal Map.
	std::string NormalMap = "NONE";

	//	The Occlusion Map - No Default Occlusion Map.
	std::string OcclusionMap = "NONE";
};


//	
class MaterialData : public ResourceData
{

public:

	//	Default Material Data Constructor.
	MaterialData(const MaterialValues & newMaterialValues, const MaterialMaps & newMaterialMaps);

	//	Default Material Data Destructor.
	~MaterialData();

	//	View the Material Values.
	const MaterialValues & viewMaterialValues() const;

	//	View the Material Maps.
	const MaterialMaps & viewMaterialMaps() const;

private:

	//	The Material Values associated with this Material.
	MaterialValues materialValues;

	//	The Material Maps associated with this Material.
	MaterialMaps materialMaps;
};
