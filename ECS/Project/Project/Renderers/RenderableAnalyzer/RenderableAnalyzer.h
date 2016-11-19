#pragma once

#include <memory>
#include <map>
#include <set>
#include <vector>

#include "glm\glm.hpp"

#include "../RenderablesMetaData.h"

class Renderable;


struct AssociatedMaterialTypes
{
	std::set<std::string> materialsTypes;
};

struct AssociatedGeometryMaterialTypes
{
	std::map<std::string, AssociatedMaterialTypes> geometryTypeAssociatedMaterialTypes;
};

struct SortedRenderablesTypes
{
	std::map<std::string, AssociatedGeometryMaterialTypes> shaderTypeAssociatedGeometryMaterialTypes;
};


class RenderableAnalyzer
{

public:

	//	Default RenderableAnalyzer Constructor.
	RenderableAnalyzer();

	//	Default RenderableAnalyzer Destructor.
	virtual ~RenderableAnalyzer();

	//	Return the ID of the newly created renderable.
	virtual long int createRenderable();

	//	Add a new renderable to the list of renderables.
	virtual void addRenderable(const long int & currentRenderableID);

	//	Return the const Renderable associated with the specified RenderableID
	std::shared_ptr<const Renderable> viewRenderable(const long int & currentRenderableID) const;

	//	Return the set of the Renderables Type Keys.
	const std::set<RenderableType> & viewRenderablesTypes() const;
	const SortedRenderablesTypes & viewSortedRenderablesTypes() const;

	//	Return the Renderable associated with the current Renderable ID.
	std::shared_ptr<RenderableMetaData> getRenderableInfo(const long int & currentRenderableID);

	//	Update the Shading Type associated with the specified Renderable ID.
	virtual void updateShadingType(const long int & currentRenderableID, const std::string & newShadingType);

	//	Update the Geometry Type associated with the specified Renderable ID.
	virtual void updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType);

	//	Update the Material Type associated with the specified Renderable ID.
	virtual void updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType);

	//	Update the Transform Matrix associated with the specified Renderable Id.
	virtual void updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix);

	//	Return the Renderables that use this Renderable Type Keys.
	std::shared_ptr<const RenderablesOfType> viewRenderablesOfType(const RenderableType & renderableTypeKeys) const;

	//	Remove the Renderable specified by the Renderable ID.
	virtual void removeRenderable(const long int & deadRenderable);


private:

	//	Return the Renderables that use this Renderable Type Keys.
	std::shared_ptr<RenderablesOfType> getRenderablesOfType(const RenderableType & renderableTypeKeys);

	//	Add the Renderables to the appropriate list.
	virtual void addRenderableInfoToList(const std::shared_ptr<RenderableMetaData> newRenderableInfo);

	//	Remove the Renderables From its list.
	virtual void removeRenderableInfoFromList(const long int & currentRenderableID);

	//	The Map of the Type Key Renderables to the Type Analyzed Renderables.
	std::map<RenderableType, std::shared_ptr<RenderablesOfType>> mapRenderableTypeToRenderables;

	//	The Map of the Renderable IDs to the Renderable Type and its position in that list.
	std::map<long int, std::shared_ptr<RenderableMetaData>> mapRenderableIDToRenderableInfo;

	//	The Set of Type Key Renderables that have been used.
	std::set<RenderableType> renderableTypes;
	SortedRenderablesTypes sortedRenderableTypes;

	//	The list of active renderable IDs.
	std::vector<long int> activeRenderables;

	//	The list of inactive renderable IDs.
	std::vector<long int> inactiveRenderables;

	//	The default initialization values for the Shader, Geometry and Material Types.
	std::string defaultShaderType;
	std::string defaultGeometryType;
	std::string defaultMaterialType;
};

