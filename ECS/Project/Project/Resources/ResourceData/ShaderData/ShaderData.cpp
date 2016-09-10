#include "ShaderData.h"


//	Default ShaderData Constructor
ShaderData::ShaderData(const std::map<std::string, std::string> & newMapShaderPropertyToValue)
{
	//	Construct the Map from the given Map.
	mapShaderPropertyToValue = std::map<std::string, std::string>(newMapShaderPropertyToValue);

	//	Find the Shader Type.
	auto shaderPropertiesIterator = mapShaderPropertyToValue.find("Shader Type");
	if (shaderPropertiesIterator != mapShaderPropertyToValue.end()) 
		shaderProgramName = shaderPropertiesIterator->second;
	else
		shaderProgramName = "ERROR";

	//	Find the Vertex Shader Source.
	shaderPropertiesIterator = mapShaderPropertyToValue.find("Vertex Shader Source");
	if (shaderPropertiesIterator != mapShaderPropertyToValue.end()) 
		vertexShaderSourceName = shaderPropertiesIterator->second;
	else
		vertexShaderSourceName = "ERROR";

	//	Find the Fragment Shader Source.
	shaderPropertiesIterator = mapShaderPropertyToValue.find("Fragment Shader Source");
	if (shaderPropertiesIterator != mapShaderPropertyToValue.end())
		fragmentShaderSourceName = shaderPropertiesIterator->second;
	else
		fragmentShaderSourceName = "ERROR";

}

//	Default ShaderData Destructor
ShaderData::~ShaderData()
{

}

//	Return the Vertex Shader File Name associated with this Shader.
std::string ShaderData::getVertexShaderFileName() const
{
	return vertexShaderSourceName;
}

//	Return the Fragment Shader File Name associated with this Shader.
std::string ShaderData::getFragmentShaderFileName() const
{
	return fragmentShaderSourceName;
}

//	Return the Program Name.
std::string ShaderData::getShaderProgramName() const
{
	return shaderProgramName;
}

//	Return the map of the Shader Property to the Value.
const std::map<std::string, std::string>& ShaderData::getMapShaderPropertyToValue() const
{
	return mapShaderPropertyToValue;
}