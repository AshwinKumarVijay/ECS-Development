#pragma once

#include <map>
#include <memory>

#include "../ResourceManager.h"

class LightData;

class LightResourceManager : public ResourceManager
{
public:


	//	Default LightResourceManager Constructor
	LightResourceManager(std::shared_ptr<EventQueue> newEventQueue);


	//	Default LightResourceManager Destructor
	virtual ~LightResourceManager();


	//	Add Comments - TO DO
	virtual void addLight(std::string newLightName, std::shared_ptr<LightData> newLightData);

	//	Add Comments - TO DO
	virtual void updateLight(std::string currentLightName, std::shared_ptr<LightData> newLightData);

	//	Add Comments - TO OD
	std::shared_ptr<LightData> getLight(std::string currentLightName);

	//	Add Comments - TO DO
	std::shared_ptr<const LightData> viewLight(std::string currentLightName) const;

	//	Add Comments - TO DO
	virtual void deleteLight(std::string deadLightName);


private:

	//	Map the Name to the Texture Data.
	std::map<std::string, std::shared_ptr<LightData>> mapNameToLightData;

};

