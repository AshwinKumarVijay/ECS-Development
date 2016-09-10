#pragma once

#include <memory>
#include <vector>

#include "../ECS/Component/Component.h"

class Renderable;

class RenderingComponent : public Component
{

public:

	/**

	Name: RenderingComponent
	Parameters: -
	Purpose: Default RenderingComponent Constructor
	Return Value: -
	Other Output: -

	*/
	RenderingComponent();


	/**

	Name: ~RenderingComponent
	Parameters: -
	Purpose: Default RenderingComponent Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~RenderingComponent();


	/**

	Name: setRenderableID
	Parameters:
	- "newRenderableID" - (long int) (const) (&) - The new Renderable ID.
	Purpose: Set the geometry associated with this Renderable.
	Return Value: -
	Other Output: -

	*/
	virtual void setRenderableID(const long int & newRenderableID);


	/**

	Name: getRenderableID
	Parameters:
	Purpose: Return the Renderable ID.
	Return Value:
	- (long int) - The Renderable ID.
	Other Output: -

	*/
	virtual long int getRenderableID() const;


	/**

	Name: setMaterialType
	Parameters:
	- "newMaterialType" - (string) (const) (&) - The new Material type.
	Purpose: Set the Material associated with this Renderable.
	Return Value: -
	Other Output: -

	*/
	virtual void setMaterialType(const std::string & newMaterialType);


	/**

	Name: getMaterialType
	Parameters:
	Purpose: Return the Material associated with this Renderable.
	Return Value:
	- (std::string) - The type of the Material associated.
	Other Output: -

	*/
	virtual std::string getMaterialType() const;



	/**

	Name: setShaderType
	Parameters:
	- "newShaderType" - (string) (const) (&) - Set the new Shader Type.
	Purpose: Set the Shader Type associated with this batch.
	Return Value: -
	Other Output: -

	*/
	virtual void setShaderType(const std::string & newShaderType);


	/**

	Name: getShaderType
	Parameters: -
	Purpose: Return the string associated with the ShaderType.
	Return Value:
	- (string) - Return a string associated with the ShaderType.
	Other Output: -

	*/
	virtual std::string getShaderType() const;



private:

	//	Renderable associated with this component
	long int renderableID;

	//	The Material associated with the Component.
	std::string materialType;

	//	The string associated with the ShaderType.
	std::string shaderType;

};

