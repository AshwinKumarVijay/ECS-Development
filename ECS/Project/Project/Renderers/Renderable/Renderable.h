#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm\glm.hpp"

class Renderable
{

public:

	//	Add Comments - TO DO
	Renderable(const long int & newRenderableID);

	//	Add Comments - TO DO
	virtual ~Renderable();
	

	//	Add Comments - TO DO
	void activate();
	//	Add Comments - TO DO
	bool getActive() const;

	//	Add Comments - TO DO
	void deactivate();
	
	//	Add Comments - TO DO
	bool getInactive() const;


	//	Add Comments - TO DO
	virtual long int getRenderableID() const;

	//	Add Comments - TO DO
	virtual void setGeometryType(const std::string & newGeometryType);
	//	Add Comments - TO DO
	virtual std::string getGeometryType() const;

	//	Add Comments - TO DO
	virtual void setMaterialType(const std::string & newMaterialType);
	//	Add Comments - TO DO
	virtual std::string getMaterialType() const;

	//	Add Comments - TO DO
	virtual void setShaderType(const std::string & newShaderType);
	//	Add Comments - TO DO
	virtual std::string getShaderType() const;

	//	Add Comments - TO DO
	virtual glm::mat4 getTransformMatrix() const;
	//	Add Comments - TO DO
	virtual void setTransformMatrix(const glm::mat4 & newModelMatrix);


private:

	//	The Name of the Geometry associated with this Renderable.
	std::string geometryType;

	//	The Name of the Material associated with this Renderable.
	std::string materialType;

	//	The ShaderType associated with this Renderable.
	std::string shaderType;

	//	The Transform Matrix associated with this Renderable.
	glm::mat4 transformMatrix;

	//	The Renderable ID.
	long int renderableID;

	//	The Active Flag.
	bool activeFlag;

};

