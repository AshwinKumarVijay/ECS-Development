#include "Renderable.h"


//	Default Renderable Constructor
Renderable::Renderable(const long int & newRenderableID)
{
	geometryType = "DEFAULT GEOMETRY";
	materialType = "DEFAULT MATERIAL";
	shadingType = ShadingTypes::OPAQUE_BASIC;
	activeFlag = true;
	renderableID = newRenderableID;
}

//	Default Renderable Destructor
Renderable::~Renderable()
{

}

//	Activate the Renderable.
void Renderable::activate()
{
	activeFlag = true;
}

//	Return whether the Renderable is active.
bool Renderable::getActive() const
{
	return activeFlag;
}

//	Deactive the Renderable.
void Renderable::deactivate()
{
	activeFlag = false;
}

//	Return whether the Renderable is inactive.
bool Renderable::getInactive() const
{
	return !activeFlag;
}

//	Return the RenderableID.
long int Renderable::getRenderableID() const
{
	return renderableID;
}

//	Set the Geometry Name associated with this Renderable.
void Renderable::setGeometryType(const std::string & newGeometryType)
{
	geometryType = newGeometryType;
}

//	Return the Geometry. 
std::string Renderable::getGeometryType() const
{
	return geometryType;
}

//	Set the Material Name associated with this Renderable.
void Renderable::setMaterialType(const std::string & newMaterialType)
{
	materialType = newMaterialType;
}

//	Return the Material.
std::string Renderable::getMaterialType() const
{
	return materialType;
}

//	Set the Shading Type.
void Renderable::setShadingType(ShadingTypes::ShadingType newShadingType)
{
	shadingType = newShadingType;
}

//	Return the Shading Type.
ShadingTypes::ShadingType Renderable::getShadingType() const
{
	return shadingType;
}

//	Return the Model Matrix.
glm::mat4 Renderable::getTransformMatrix() const
{
	return transformMatrix;
}

//	Set the Model Matrix.
void Renderable::setTransformMatrix(const glm::mat4 & newModelMatrix)
{
	transformMatrix = newModelMatrix;
}
