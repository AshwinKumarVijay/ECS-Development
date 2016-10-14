#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>

#include "GL\glew.h"

//	
class ShaderData;

//	
struct SamplingDataUniforms
{
	//	SCREEN SIZE UNIFORM.
	GLuint u_screenSize = -1;

	//	UNIT SQUARE SAMPLES UNIFORM.
	GLuint u_unitSquareSamples = -1;

	//	HEMISPHERE SAMPLES UNIFORM.
	GLuint u_hemisphereSamples = -1;

	//	HEMISPHERE RADIUS.
	GLuint u_hemisphereRadius = -1;
};

//
struct NoiseTexturesUniforms
{
	//	NOISE TEXTURES

	//	Noise Texture One Uniform.
	GLuint t_noiseTextureOne = -1;

	//	Noise Texture Two Uniform.
	GLuint t_noiseTextureTwo = -1;

	//	Noise Texture Three Uniform.
	GLuint t_noiseTextureThree = -1;

	//	Noise Texture Four Uniform.
	GLuint t_noiseTextureFour = -1;
};

//	
struct PrimaryPostProcessInputUniforms
{
	//	Post Process Texture Input Uniforms.
	GLuint pp_inputTextureOne = -1;
	GLuint pp_inputTextureTwo = -1;
	GLuint pp_inputTextureThree = -1;
	GLuint pp_inputTextureFour = -1;
};

struct SecondaryPostProcessInputUniforms
{
	//	Post Process Texture Input Uniforms.
	GLuint pp_inputTextureFive = -1;
	GLuint pp_inputTextureSix = -1;
	GLuint pp_inputTextureSeven = -1;
	GLuint pp_inputTextureEight = -1;
};

//	
struct EnvironmentDataUniforms
{
	//	Background ENvironment Intensities.
	GLuint u_backgroundEnvironmentIntensities = -1;

	//	The Background Environment Cube Maps.
	GLuint u_backgroundEnvironmentCubeMapOne = -1;
	GLuint u_backgroundEnvironmentCubeMapTwo = -1;
	GLuint u_backgroundEnvironmentCubeMapThree = -1;
	GLuint u_backgroundEnvironmentCubeMapFour = -1;
};


//	
struct LightDataUniforms
{
	//	AMBIENT LIGHT DATA, AND LIGHT ARRAY
	GLuint u_ambientLight = -1;
	GLuint u_lights = -1;
};


//	
struct TextureDataUniforms
{
	//	ENVIRONMENT MAP CUBE MAP, DIFFUSE ALBEDO MAP, SPECULAR ALBEDO MAP, EMISSIVE COLOR AND INTENSITY MAP, METALLIC, ROUGHNESS, FRESNEL AND OPACITY MAP.
	GLuint u_diffuseAlbedoMap = -1;
	GLuint u_specularAlbedoMap = -1;
	GLuint u_emssionColorAndIntensityMap = -1;
	GLuint u_metallicnessRoughnessFresnelOpacityMap = -1;
};

//	
struct CameraDataUniforms
{
	//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX, CAMERA NEAR AND FAR DISTANCE.
	GLuint u_worldCameraPosition = -1;
	GLuint u_cameraPerspectiveMatrix = -1;
	GLuint u_cameraViewMatrix = -1;
	GLuint u_inverseTransposeCameraViewMatrix = -1;
	GLuint u_screenSpaceViewMatrix = -1;
	GLuint u_cameraNearFarPlaneDistance = -1;
};


//	
struct ModelDataUniforms
{
	//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
	GLuint u_modelMatrix = -1;
	GLuint u_inverseTransposeModelMatrix = -1;
	GLuint u_modelViewMatrix = -1;
	GLuint u_inverseTransposeModelViewMatrix = -1;
};


//	
struct MaterialValuesUniforms
{
	//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
	GLuint u_diffuseAlbedo = -1;
	GLuint u_specularAlbedo = -1;
	GLuint u_emissiveColor = -1;
	GLuint u_metallicnessRoughnessFresnelOpacity = -1;
};


//	
struct GBufferInputUniforms
{
	//	G BUFFER - VERTEX POSITION AND DEPTH, VERTEX NORMAL, VERTEX TEXTURE COORDINATES
	//	DIFFUSE ALBEDO AND METALLICNESS, SPECULAR ALBEDO AND ROUGHNESS, EMISSIVE COLOR AND INTENSITY.
	GLuint g_worldSpaceVertexPosition;
	GLuint g_worldSpaceVertexNormal;
	GLuint g_viewSpaceVertexPositionAndDepth;
	GLuint g_viewSpaceVertexNormal;
	GLuint g_diffuseAlbedo;
	GLuint g_specularAlbedo;
	GLuint g_emissionColorAndIntensity;
	GLuint g_metallicnessRoughnessFresnelOpacity;
};



struct RendererShaderUniforms
{
	//	The CAMERA DATA, MODEL DATA, MATERIAL DATA, GBUFFER INPUT, TEXTURE DATA, LIGHT DATA.
	SamplingDataUniforms samplingDataUniforms;
	EnvironmentDataUniforms environmentDataUniforms;
	CameraDataUniforms cameraDataUniforms;
	ModelDataUniforms modelDataUniforms;
	MaterialValuesUniforms materialValuesUniforms;
	LightDataUniforms lightDataUniforms;
	TextureDataUniforms textureDataUniforms;
	GBufferInputUniforms gBufferInputUniforms;
	PrimaryPostProcessInputUniforms primaryPostProcessInputUniforms;
	SecondaryPostProcessInputUniforms secondaryPostProcessInputUniforms;
	NoiseTexturesUniforms noiseTexturesUniforms;
};


struct RendererShaderData
{
	//	Shader Name.
	std::string shaderType = "";

	//	Linked Shader ID.
	GLuint shaderID = -1;

	//	The Vertex, Geometry and Fragment Shader.
	GLuint vertexShaderID = -1;
	GLuint geometryShaderID = -1;
	GLuint fragmentShaderID = -1;

	//	The Names and Values of the Shader properties.
	std::map<std::string, std::string> shaderProperties;

	//	The RendererShaderUniforms.
	RendererShaderUniforms shaderUniforms;
};


class RendererShaderManager
{
public:

	//	Default RendererShaderManager Constructor.
	RendererShaderManager();

	//	Default RendererShaderManager Destructor.
	virtual ~RendererShaderManager();

	//	Add a Shader to the RendererShaderManager.
	virtual void addShader(std::shared_ptr<const ShaderData> newShader);

	//	Set the Active Shader, by name.
	virtual void setActiveShader(const std::string & newActiveShader);

	//	Get the Active Shader ID.
	virtual GLuint getActiveShader();

	//	Get the Active Shader Name.
	virtual std::string getActiveShaderName();

	//	Return the RendererShaderData associated with the shaderType.
	virtual std::shared_ptr<const RendererShaderData> viewShaderData(const std::string & requestedShaderName) const;

	// Return the Shader Geometry Description Representation - The Type of the Geometry = 0 - NO VERTEX INFORMATION, 1 - VERTEX BASIC DATA, 2 - VERTEX TANGENT BITANGENT DATA, 4 - VERTEX TEXTURE COORDINATES.
	int getShaderGeometryDescriptionRepresentation(const std::string & requestedShader) const;

	//	Delete the Shader with the specified name.
	virtual void deleteShader(const std::string & deadShader);

private:

	//	Reads the Shader source code from a file.
	GLuint readShaderStageFromFile(GLenum shaderType, std::string filepath);

	//	Generate the Shader Uniform Locations.
	void generateShaderUniformLocations(GLuint newShader, RendererShaderUniforms & newRendererShaderUniforms);

	//	The Active Shader Name.
	std::string activeShaderName;

	//	Map the Name to the ShaderData.
	std::map<std::string, std::shared_ptr<RendererShaderData>> mapNameToShaderData;

};

