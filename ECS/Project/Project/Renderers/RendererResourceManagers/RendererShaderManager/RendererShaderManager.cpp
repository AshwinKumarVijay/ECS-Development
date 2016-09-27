#include "RendererShaderManager.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"

//	Default RendererShaderManager Constructor
RendererShaderManager::RendererShaderManager()
{
	activeShaderName = "NONE";
}

//	Default RendererShaderManager Destructor
RendererShaderManager::~RendererShaderManager()
{

}

//	Add a new Shader to the RendererShaderManager.
void RendererShaderManager::addShader(std::shared_ptr<const ShaderData> newShader)
{
	//	Find the Shader.
	auto shaderIterator = mapNameToShaderData.find(newShader->getShaderProgramName());

	//	Check if it already 
	if (shaderIterator != mapNameToShaderData.end())
	{
		//	TO DO
		//	Throw Shader Already Exists Error.
	}
	else
	{

		//	Construct Renderer Shader Data.
		std::shared_ptr<RendererShaderData> newRendererShaderData = std::make_shared<RendererShaderData>();

		//	Create the ShaderProgram ID.
		GLuint shaderID = glCreateProgram();
		newRendererShaderData->shaderID = shaderID;
		newRendererShaderData->shaderType = newShader->getShaderProgramName();

		//	Get the Vertex Shader ID. Geometry Shader ID, Fragment Shader ID.
		
		if (newShader->getVertexShaderFileName() != "NONE")
		{
			GLuint vertexShaderID = readShaderStageFromFile(GL_VERTEX_SHADER, newShader->getVertexShaderFileName());
			glAttachShader(shaderID, vertexShaderID);
			newRendererShaderData->vertexShaderID = vertexShaderID;
		}

		if (newShader->getGeometryShaderFileName() != "NONE")
		{
			GLuint geometryShaderID = readShaderStageFromFile(GL_GEOMETRY_SHADER, newShader->getGeometryShaderFileName());
			glAttachShader(shaderID, geometryShaderID);
			newRendererShaderData->geometryShaderID = geometryShaderID;
		}
		
		if (newShader->getFragmentShaderFileName() != "NONE")
		{

			GLuint fragmentShaderID = readShaderStageFromFile(GL_FRAGMENT_SHADER, newShader->getFragmentShaderFileName());
			glAttachShader(shaderID, fragmentShaderID);
			newRendererShaderData->fragmentShaderID = fragmentShaderID;
		}

		//	Link the Shader.
		glLinkProgram(shaderID);

		newRendererShaderData->shaderProperties = std::map<std::string, std::string>(newShader->getMapShaderPropertyToValue());

		//	Set the Shader Uniform Locations.
		generateShaderUniformLocations(shaderID, newRendererShaderData->shaderUniforms);

		//	Insert the Shader into the Map in the appropriate location.
		mapNameToShaderData.insert(std::make_pair(newShader->getShaderProgramName(), newRendererShaderData));
	}

}

//	Set the active shader.
void RendererShaderManager::setActiveShader(const std::string & newActiveShader)
{
	//	Find the Shader specified by name.
	auto shaderIterator = mapNameToShaderData.find(newActiveShader);

	//	Check if the Shader exists.
	if (shaderIterator != mapNameToShaderData.end())
	{
		activeShaderName = newActiveShader;
		glUseProgram(shaderIterator->second->shaderID);
	}
	else
	{
		//	TO DO
		//	Throw Exception if Shader is Not Found.
	}
}

//	Return the currently active shader name.
std::string RendererShaderManager::getActiveShaderName()
{
	return activeShaderName;
}

//	View the Shader Data by name.
std::shared_ptr<const RendererShaderData> RendererShaderManager::viewShaderData(const std::string & requestedShaderName) const
{
	//	Find the Shader specified by name.
	auto shaderIterator = mapNameToShaderData.find(requestedShaderName);

	//	Check if the Shader exists.
	if (shaderIterator != mapNameToShaderData.end())
	{
		//	Return the Shader Data.
		return shaderIterator->second;
	}
	else
	{
		return NULL;
	}

}

//	Return the Shader Geometry Description Requirement Representation.
int RendererShaderManager::getShaderGeometryDescriptionRepresentation(const std::string & requestedShader) const
{
	//	Find the shader.
	auto shaderIterator = mapNameToShaderData.find(activeShaderName);

	//	Check if the Shader exists.
	if (shaderIterator != mapNameToShaderData.end())
	{
		int shaderGeometryDescriptionRepresentation = 0;

		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Basic Data.
		auto shaderPropertiesIterator = shaderIterator->second->shaderProperties.find("Require Vertex Basic Data");
		if (shaderPropertiesIterator != shaderIterator->second->shaderProperties.end())
		{
			if (shaderPropertiesIterator->second == "TRUE")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 1;
			}
		}

		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Tandgent and Bitangent Data.
		shaderPropertiesIterator = shaderIterator->second->shaderProperties.find("Require Vertex Tangent Bitangent Data");
		if (shaderPropertiesIterator != shaderIterator->second->shaderProperties.end())
		{
			if (shaderPropertiesIterator->second == "TRUE")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 2;
			}
		}

		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Texture Coordinates.
		shaderPropertiesIterator = shaderIterator->second->shaderProperties.find("Require Vertex Texture Coordinates Data");
		if (shaderPropertiesIterator != shaderIterator->second->shaderProperties.end())
		{
			if (shaderPropertiesIterator->second == "TRUE")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 4;
			}
		}

		//	
		return shaderGeometryDescriptionRepresentation;

	}
	else
	{
		//	TO DO
		//	Throw Exception if Shader is Not Found.
		return 0;
	}
}

//	Return the GLuint shader program ID.
GLuint RendererShaderManager::getActiveShader()
{
	//	Find the shader.
	auto shaderIterator = mapNameToShaderData.find(activeShaderName);

	//	Check if the Shader exists.
	if (shaderIterator != mapNameToShaderData.end())
	{
		//	Return the active shader ID.
		return shaderIterator->second->shaderID;
	}
	else
	{
		//	TO DO
		//	Throw Exception if Shader is Not Found.
		return 0;
	}
}

//	Delete the Shader by name.
void RendererShaderManager::deleteShader(const std::string & deadShader)
{
	//	Find the shader by name.
	auto shaderIterator = mapNameToShaderData.find(activeShaderName);

	//	Check if the Shader exists.
	if (shaderIterator != mapNameToShaderData.end())
	{
		//	Delete the Shader program.
		glDeleteProgram(shaderIterator->second->shaderID);

		//	Erase the Shader.
		mapNameToShaderData.erase(shaderIterator);
	}
	else
	{
		//	TO DO
		//	Throw Exception if Shader is Not Found.
	}
}

//	Read the Shader Stage in from the file.
GLuint RendererShaderManager::readShaderStageFromFile(GLenum shaderType, std::string filepath)
{
	//	Initialize the Shader Reference.
	GLuint shaderReference = 0;

	//	The Shader String.
	std::string shaderFileString = "";

	//	Open the file.
	std::ifstream sourceFile(filepath, std::ifstream::in);

	//	Open the SourceFile.
	if (sourceFile.is_open())
	{
		//	Create the Shader.
		shaderReference = glCreateShader(shaderType);

		//	
		std::string line = "";

		//	Read the Shader in line by line.
		while (!sourceFile.eof())
		{
			getline(sourceFile, line);
			shaderFileString.append(line + " \n");
		}

		//	C style version of the Shader File.
		const GLchar * shaderSource = shaderFileString.c_str();

		//	Assign the Shader Source.
		glShaderSource(shaderReference, 1, (const GLchar **)& shaderSource, NULL);

		//	Compile the Shader Source.
		glCompileShader(shaderReference);

		//	Check shader for errors 
		GLint shaderCompiled = GL_FALSE;

		//	Check if the Shader has been complied.
		glGetShaderiv(shaderReference, GL_COMPILE_STATUS, &shaderCompiled);

		//	
		if (shaderCompiled != GL_TRUE)
		{
			//	Print an error if the Shader failed to complie.
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderReference, shaderSource);

			//	Delete the Shader.
			glDeleteShader(shaderReference);

			//	Set the Shader to be 0.
			shaderReference = 0;
		}
	}
	else
	{
		//	Mark it as unable to be open.
		printf("Unable to open shader. \n");

	}

	//	Return the Shader Reference.
	return shaderReference;
}

//	Generate the Uniform Locations for the provided shader.
void RendererShaderManager::generateShaderUniformLocations(GLuint newShader, RendererShaderUniforms & newShaderUniforms)
{
	{
		//	AMBIENT LIGHT DATA, AND LIGHT ARRAY
		newShaderUniforms.environmentDataUniforms.u_backgroundEnvironmentIntensities = glGetUniformLocation(newShader, "u_environmentMapIntensities");
		newShaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapOne = glGetUniformLocation(newShader, "u_backgroundEnvironmentCubeMapOne");
		newShaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapTwo = glGetUniformLocation(newShader, "u_backgroundEnvironmentCubeMapTwo");
		newShaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapThree = glGetUniformLocation(newShader, "u_backgroundEnvironmentCubeMapThree");
		newShaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapFour = glGetUniformLocation(newShader, "u_backgroundEnvironmentCubeMapFour");
	}

	{
		//	UNIT SQUARE AND HEMISPHERE SAMPLES.
		newShaderUniforms.samplingDataUniforms.u_screenSize = glGetUniformLocation(newShader, "u_screenSize");
		newShaderUniforms.samplingDataUniforms.u_unitSquareSamples = glGetUniformLocation(newShader, "u_unitSquareSamples");
		newShaderUniforms.samplingDataUniforms.u_hemisphereSamples = glGetUniformLocation(newShader, "u_hemisphereSamples");
		newShaderUniforms.samplingDataUniforms.u_hemisphereRadius = glGetUniformLocation(newShader, "u_hemisphereRadius");
	}

	{
		//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
		newShaderUniforms.cameraDataUniforms.u_worldCameraPosition = glGetUniformLocation(newShader, "u_worldCameraPosition");
		newShaderUniforms.cameraDataUniforms.u_cameraPerspectiveMatrix = glGetUniformLocation(newShader, "u_cameraPerspectiveMatrix");
		newShaderUniforms.cameraDataUniforms.u_cameraViewMatrix = glGetUniformLocation(newShader, "u_cameraViewMatrix");
		newShaderUniforms.cameraDataUniforms.u_inverseTransposeCameraViewMatrix = glGetUniformLocation(newShader, "u_inverseTransposeCameraViewMatrix");
		newShaderUniforms.cameraDataUniforms.u_screenSpaceViewMatrix = glGetUniformLocation(newShader, "u_screenSpaceViewMatrix");
		newShaderUniforms.cameraDataUniforms.u_cameraNearFarPlaneDistance = glGetUniformLocation(newShader, "u_cameraNearFarPlaneDistance");
	}

	{
		newShaderUniforms.lightDataUniforms.u_ambientLight = glGetUniformLocation(newShader, "u_ambientLight");
		newShaderUniforms.lightDataUniforms.u_lights = glGetUniformLocation(newShader, "u_lights");
	}

	{
		//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
		newShaderUniforms.modelDataUniforms.u_modelMatrix = glGetUniformLocation(newShader, "u_modelMatrix");
		newShaderUniforms.modelDataUniforms.u_inverseTransposeModelMatrix = glGetUniformLocation(newShader, "u_inverseTransposeModelMatrix");
		newShaderUniforms.modelDataUniforms.u_modelViewMatrix = glGetUniformLocation(newShader, "u_modelViewMatrix");
		newShaderUniforms.modelDataUniforms.u_inverseTransposeModelViewMatrix = glGetUniformLocation(newShader, "u_inverseTransposeModelViewMatrix");
	}

	{
		//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
		newShaderUniforms.materialValuesUniforms.u_diffuseAlbedo = glGetUniformLocation(newShader, "u_diffuseAlbedo");
		newShaderUniforms.materialValuesUniforms.u_specularAlbedo = glGetUniformLocation(newShader, "u_specularAlbedo");
		newShaderUniforms.materialValuesUniforms.u_emissiveColor = glGetUniformLocation(newShader, "u_emssionColorAndIntensity");
		newShaderUniforms.materialValuesUniforms.u_metallicnessRoughnessFresnelOpacity = glGetUniformLocation(newShader, "u_metallicnessRoughnessFresnelOpacity");
	}

	{
		//	G BUFFER - VERTEX POSITION AND DEPTH, VERTEX NORMAL, VERTEX TEXTURE COORDINATES
		//	DIFFUSE ALBEDO AND METALLICNESS, SPECULAR ALBEDO AND ROUGHNESS, EMISSIVE COLOR AND INTENSITY.
		newShaderUniforms.gBufferInputUniforms.g_worldSpaceVertexPosition = glGetUniformLocation(newShader, "g_worldSpaceVertexPosition");
		newShaderUniforms.gBufferInputUniforms.g_worldSpaceVertexNormal = glGetUniformLocation(newShader, "g_worldSpaceVertexNormal");
		newShaderUniforms.gBufferInputUniforms.g_viewSpaceVertexPositionAndDepth = glGetUniformLocation(newShader, "g_viewSpaceVertexPositionAndDepth");
		newShaderUniforms.gBufferInputUniforms.g_viewSpaceVertexNormal = glGetUniformLocation(newShader, "g_viewSpaceVertexNormal");
		newShaderUniforms.gBufferInputUniforms.g_diffuseAlbedo = glGetUniformLocation(newShader, "g_diffuseAlbedo");
		newShaderUniforms.gBufferInputUniforms.g_specularAlbedo = glGetUniformLocation(newShader, "g_specularAlbedo");
		newShaderUniforms.gBufferInputUniforms.g_emissionColorAndIntensity = glGetUniformLocation(newShader, "g_emissionColorAndIntensity");
		newShaderUniforms.gBufferInputUniforms.g_metallicnessRoughnessFresnelOpacity = glGetUniformLocation(newShader, "g_metallicnessRoughnessFresnelOpacity");
	}

	{
		//	ENVIRONMENT MAP CUBE TEXTURE, DIFFUSE ALBEDO MAP TEXTURE, SPECULAR ALBEDO MAP TEXTURE
		//	EMISSIVE COLOR AND INTENSITY TEXTURE, METALLIC, ROUGHNESS, FRESNEL AND OPACITY TEXTURE.
		newShaderUniforms.textureDataUniforms.u_diffuseAlbedoMap = glGetUniformLocation(newShader, "u_diffuseAlbedoMap");
		newShaderUniforms.textureDataUniforms.u_specularAlbedoMap = glGetUniformLocation(newShader, "u_specularAlbedoMap");
		newShaderUniforms.textureDataUniforms.u_emssionColorAndIntensityMap = glGetUniformLocation(newShader, "u_emssionColorAndIntensityMap");
		newShaderUniforms.textureDataUniforms.u_metallicnessRoughnessFresnelOpacityMap = glGetUniformLocation(newShader, "u_metallicnessRoughnessFresnelOpacityMap");
	}

	{
		//	POST PROCESS INPUT TEXTURES.
		newShaderUniforms.postProcessInputUniforms.pp_inputTextureOne = glGetUniformLocation(newShader, "pp_inputTextureOne");
		newShaderUniforms.postProcessInputUniforms.pp_inputTextureTwo = glGetUniformLocation(newShader, "pp_inputTextureTwo");
		newShaderUniforms.postProcessInputUniforms.pp_inputTextureThree = glGetUniformLocation(newShader, "pp_inputTextureThree");
		newShaderUniforms.postProcessInputUniforms.pp_inputTextureFour = glGetUniformLocation(newShader, "pp_inputTextureFour");

	}

	{
		//	NOISE TEXTURES.
		newShaderUniforms.noiseTexturesUniforms.t_noiseTextureOne = glGetUniformLocation(newShader, "t_noiseTextureOne");
		newShaderUniforms.noiseTexturesUniforms.t_noiseTextureTwo = glGetUniformLocation(newShader, "t_noiseTextureTwo");
		newShaderUniforms.noiseTexturesUniforms.t_noiseTextureThree = glGetUniformLocation(newShader, "t_noiseTextureThree");
		newShaderUniforms.noiseTexturesUniforms.t_noiseTextureFour = glGetUniformLocation(newShader, "t_noiseTextureFour");
	}


}
