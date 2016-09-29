#pragma once

#include <memory>
#include <vector>

#include "../ECS/Component/Component.h"
#include "../Renderers/ShadingType.h"

class Renderable;

class RenderingComponent : public Component
{

public:

	//	Default RenderingComponent Constructor
	RenderingComponent();

	//	Default RenderingComponent Destructor
	virtual ~RenderingComponent();

	//	Set the RenderableID associated with this RenderingComponent.
	virtual void setRenderableID(const long int & newRenderableID);
	//	Return the Renderable ID.
	virtual long int getRenderableID() const;


	//	Set the Material associated with this Renderable.
	virtual void setMaterialType(const std::string & newMaterialType);
	//	Return the Material associated with this Renderable.
	virtual std::string getMaterialType() const;



	//	Set the Shader Type associated with this batch.
	virtual void setShadingType(ShadingTypes::ShadingType newShadingType);
	//	Return a string associated with the ShaderType.
	virtual ShadingTypes::ShadingType getShadingType() const;


private:

	//	Renderable associated with this component
	long int renderableID;

	//	The ShadingType.
	ShadingTypes::ShadingType shadingType;

	//	The Material associated with the Component.
	std::string materialType;
};

