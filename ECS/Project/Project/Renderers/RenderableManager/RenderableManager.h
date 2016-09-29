#pragma once

#include <vector>
#include <map>
#include <memory>

#include "glm\glm.hpp"
#include "../ShadingType.h"

class Renderable;

class RenderableManager
{

public:
	
	//	Default RenderableManager Constructor.
	RenderableManager();

	//	Default RenderableManager Destructor.
	virtual ~RenderableManager();

	//	Create the Renderable and return the associated RenderableID.
	long int createRenderable();

	//	Return the Renderable associated with the specified RenderableID.
	std::shared_ptr<const Renderable> viewRenderable(const long int & currentRenderableID) const;

	//	Return the Renderable associated with the specified RenderableID.
	std::shared_ptr<Renderable> getRenderable(const long int & currentRenderableID);

	//	Return the map of the ShadingType to the Geometry Types.
	const std::map<ShadingTypes::ShadingType, std::vector<std::string>> & getShadingTypesAndGeometryTypes();

	//	Return the number of Renderables that use the Shading Type.
	int getShadingTypeRenderableNumber(ShadingTypes::ShadingType requestedShadingType);

	//	Return the number of Renderables that use both the Shading Type and the Renderables.
	int getShadingTypeGeometryTypeRenderableNumber(ShadingTypes::ShadingType requestedShadingType, const std::string & requestedGeometryType);

	//	Update the Shading Type associated with the specified Renderable ID.
	virtual void updateShadingType(const long int & currentRenderableID, ShadingTypes::ShadingType newShadingType);

	//	Update the Geometry Type associated with the specified Renderable ID.
	virtual void updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType);

	//	Update the Material Type associated with the specified Renderable ID.
	virtual void updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType);
	
	//	Update the Transform Matrix associated with the specified Renderable Id.
	virtual void updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix);

	//	View Renderables of Shading Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> viewRenderablesOfShadingTypeAndGeometryType(ShadingTypes::ShadingType newShadingType, const std::string & newGeometryType) const;
	
	//	View Materials of Shading Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<std::string>> viewMaterialsOfShadingTypeAndGeometryType(ShadingTypes::ShadingType newShadingType, const std::string & newGeometryType) const;

	//	View Transforms of Shading Type and the Geometry Type.
	virtual std::shared_ptr<const std::vector<glm::mat4>> viewTransformsOfShadingTypeAndGeometryType(ShadingTypes::ShadingType newShadingType, const std::string & newGeometryType) const;

	//	Remove the Renderable specified by the Renderable ID.
	virtual void removeRenderable(const long int & currentRenderableID);

	//	Return the Renderables List.
	virtual std::shared_ptr<std::vector<std::shared_ptr<Renderable>>> getRenderablesList(std::pair<ShadingTypes::ShadingType, std::string> ShadingTypeAndGeometryType);

	//	Return the Materials List.
	virtual std::shared_ptr<std::vector<std::string>> getMaterialsList(std::pair<ShadingTypes::ShadingType, std::string> ShadingTypeAndGeometryType);

	//	Return the Transforms List.
	virtual std::shared_ptr<std::vector<glm::mat4>> getTransformsList(std::pair<ShadingTypes::ShadingType, std::string> ShadingTypeAndGeometryType);


private:

	//	Add a Renderable to Renderable Storage.
	virtual void addRenderableToStorage(const long int & currentRenderableID);

	//	Remove a Renderable from Renderable Storage.
	virtual void removeRenderableFromStorage(const long int & currentRenderableID);

	//	Add a Geometry Type to the Shading Type Map.
	virtual void addGeometryTypeToShadingTypeMap(const ShadingTypes::ShadingType requestedShadingType, const std::string & newGeometryType);

	//	Clean the Geometry Type to the Shading Type Map.
	virtual void cleanGeometryTypeToShadingTypeMap();

	//	Clean the Material Type to the Shading Type Map.
	virtual void cleanMaterialTypeToShadingTypeMap();

	//	A reference to the list of active renderables.
	std::vector<long int> activeRenderableIDs;

	//	A reference to the list of destroyed renderables.
	std::vector<long int> destroyedRenderableIDs;

	//	The last RenderableID.
	long int lastRenderableID;

	//	Map of IDs to Renderables.
	std::map<long int, std::shared_ptr<Renderable>> mapIDToRenderable;

	//	Map of the ShadingType to the Geometry that is used by the Renderables that have that Shading.
	std::map<ShadingTypes::ShadingType, std::vector<std::string>> mapShadingTypeToGeometryTypes;

	//	Map the ShadingType and the Geometry Type to the Renderables that use both.
	std::map<std::pair<ShadingTypes::ShadingType, std::string>, std::shared_ptr<std::vector<std::shared_ptr<Renderable>>>> mapShadingTypeAndGeometryTypeToRenderables;

	//	Map the ShadingType and the Geometry Type to the Materials of the Renderables that use both.
	std::map<std::pair<ShadingTypes::ShadingType, std::string>, std::shared_ptr<std::vector<std::string>>> mapShadingTypeAndGeometryTypeToMaterials;

	//	Map the ShadingType and the Geometry Type to the Transforms of the Renderables that use both.
	std::map<std::pair<ShadingTypes::ShadingType, std::string>, std::shared_ptr<std::vector<glm::mat4>>> mapShadingTypeAndGeometryTypeToTransforms;
};

