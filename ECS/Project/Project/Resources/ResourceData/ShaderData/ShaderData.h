#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "../ResourceData.h"

class ShaderData : public ResourceData
{ 

public:

	//	Default ShaderData Constructor.
	ShaderData(const std::map<std::string, std::string> & newMapShaderPropertyToValue);

	//	Default ShaderData Destructor.
	virtual ~ShaderData();

	//	Return the Vertex Shader FileName.
	std::string getVertexShaderFileName() const;

	//	Return the Fragment Shader FileName.
	std::string getFragmentShaderFileName() const;

	//	Return the Name of the Linked Program.
	std::string getShaderProgramName() const;

	//	Return the map of the Shader Property to the Value.
	const std::map<std::string, std::string> & getMapShaderPropertyToValue() const;

private:

	//	The Name of the Vertex Shader Filename.
	std::string vertexShaderSourceName;

	//	The Name of the Fragment Shader Filename.
	std::string fragmentShaderSourceName;

	//	The name to assign to the linked Program.
	std::string shaderProgramName;

	//	Map the Shader Property to the Shader Value;
	std::map<std::string, std::string> mapShaderPropertyToValue;
};

