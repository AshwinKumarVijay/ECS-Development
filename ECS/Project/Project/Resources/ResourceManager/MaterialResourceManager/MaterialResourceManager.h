#pragma once


#include <map>
#include <memory>

#include "../ResourceManager.h"

class ResourceData;
class MaterialData;

class MaterialResourceManager : public ResourceManager
{
public:
	
	//	Default MaterialResourceManager Constructor.
	MaterialResourceManager(std::shared_ptr<EventQueue> newEventQueue);

	//	Default MaterialResourceManager Destructor.
	virtual ~MaterialResourceManager();

	//	Add a Material to the MaterialResourceManager.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<MaterialData> newMaterialData);

	//	Update Material in the MaterialResourceManager.
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<MaterialData> newMaterialData);

	//	Return a Material in the MaterialResourceManager.
	virtual std::shared_ptr<MaterialData> getMaterial(std::string currentMaterialName);

	//	Return a const Material in the MaterialResourceManager.
	virtual std::shared_ptr<const MaterialData> viewMaterial(std::string currentMaterialName) const;

	//	Delete a Material in the MaterialResourceManager.
	virtual void deleteMaterial(std::string deadMaterialName);


private:

	//	Map the Name to the Texture Data.
	std::map<std::string, std::shared_ptr<MaterialData>> mapNameToMaterialData;

};

