#include "BasicRenderer.h"

#include "../Configuration/Configuration.h"
#include "../Transform/Transform.h"
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"

//	Default BasicRenderer Constructor.
BasicRenderer::BasicRenderer()
{

}

//	Default BasicRenderer Destrcutor.
BasicRenderer::~BasicRenderer()
{

}

//	Initialize the Overall Renderer, including the VR Rendering portion.
void BasicRenderer::initializeRenderer()
{
	//	Create the Active Camera to use.
	activeCamera = std::make_shared<Camera>();

	//	Initialize the Rendering Hints.
	initializeRenderingHints();

	//	Initialize the Environment Maps.
	initializeBackgroundEnvironment();
}

//	Initialize the Rendering Hins.
void BasicRenderer::initializeRenderingHints()
{

	//	Enable Face Culling.
	glEnable(GL_CULL_FACE);

	//	Enable Depth Testing.
	glEnable(GL_DEPTH_TEST);

	//	Receive the Screen Width from the Configuration object.
	std::string screenWidthString = "";
	Configuration::getConfiguration().getProperty("RESOLUTION WIDTH", screenWidthString);
	int screenWidth = 0;
	std::istringstream(screenWidthString) >> screenWidth;

	//	Receive the Screen Height from the Configuration object.
	std::string screenHeightString = "";
	Configuration::getConfiguration().getProperty("RESOLUTION HEIGHT", screenHeightString);
	int screenHeight = 0;
	std::istringstream(screenHeightString) >> screenHeight;

	//	Set the Window Screen Width, and the Window Screen Height.
	windowScreenWidth = screenWidth;
	windowScreenHeight = screenHeight;

	//	Enable Blending
	glEnable(GL_BLEND);

	//	Set the Blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//	Set the GL Viewport.
	glViewport(0, 0, windowScreenWidth, windowScreenHeight);

	//	Set the pixel size.
	glPointSize(5.0f);
}

//	Initialize the Environment Maps.
void BasicRenderer::initializeBackgroundEnvironment()
{

	//	Receive the Environment Map Name from the Configuration object.
	std::string backgroundEnvironmentMap = "NONE";
	backgroundEnvironmentMap = "NONE";
	Configuration::getConfiguration().getConfiguration().getProperty("BACKGROUND ENVIRONMENT MAP ONE", backgroundEnvironmentMap);
	backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0] = backgroundEnvironmentMap;

	backgroundEnvironmentMap = "NONE";
	Configuration::getConfiguration().getConfiguration().getProperty("BACKGROUND ENVIRONMENT MAP TWO", backgroundEnvironmentMap);
	backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1] = backgroundEnvironmentMap;

	backgroundEnvironmentMap = "NONE";
	Configuration::getConfiguration().getConfiguration().getProperty("BACKGROUND ENVIRONMENT MAP THREE", backgroundEnvironmentMap);
	backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2] = backgroundEnvironmentMap;

	backgroundEnvironmentMap = "NONE";
	Configuration::getConfiguration().getConfiguration().getProperty("BACKGROUND ENVIRONMENT MAP FOUR", backgroundEnvironmentMap);
	backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3] = backgroundEnvironmentMap;

	backgroundEnvironmentData.backgroundEnvironmentCubeMapsIntensities = glm::vec4(1.0, 1.0, 1.0, 1.0);

	//	Create the new vertex.
	Vertex newVertex;

	//	----------------------------- Side 1 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	----------------------------- Side 2 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	----------------------------- Side 3 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	----------------------------- Side 4 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	----------------------------- Side 5 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	----------------------------- Side 6 -------------------------	//

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, -1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	Set the new position.
	newVertex.position = glm::vec4(1.0f, -1.0f, 1.0f, 1.0);
	//	Add it to the list of vertices of the Skybox.
	backgroundEnvironmentData.skyboxVertices.push_back(newVertex);

	//	--------------------------------------------------------------	//


	//	Generate the Environment Map VAO.
	glGenVertexArrays(1, &backgroundEnvironmentData.backgroundEnvironmentVAO);
	//	Bind the Vertex Array Object.
	glBindVertexArray(backgroundEnvironmentData.backgroundEnvironmentVAO);

	//	Generate the Environment Map VBO.
	glGenBuffers(1, &backgroundEnvironmentData.backgroundEnvironmentCubeMapVBO);

	//	Bind the Vertex Buffer Object.
	glBindBuffer(GL_ARRAY_BUFFER, backgroundEnvironmentData.backgroundEnvironmentCubeMapVBO);

	//	Fill the Buffer Object with the Skybox Vertices.
	glBufferData(GL_ARRAY_BUFFER, backgroundEnvironmentData.skyboxVertices.size() * sizeof(Vertex), backgroundEnvironmentData.skyboxVertices.data(), GL_STATIC_DRAW);

	//	Enable the Appropriate Vertex Attribute Array.
	glEnableVertexAttribArray(0);
	//	Set it to interpret the Buffer as a vec4.
	glVertexAttribFormat(0, 4, GL_FLOAT, false, 0);
	//	Bind it to the appropriate binding location.
	glVertexAttribBinding(0, 0);

	// Bind the Vertex Object to the appropriate location.
	glBindVertexBuffer(0, backgroundEnvironmentData.backgroundEnvironmentCubeMapVBO, 0, sizeof(Vertex));
}

//	Create a Renderable and return the Renderable ID.
long int BasicRenderer::createRenderable()
{
	return renderableManager.createRenderable();
}

//	View the Renderable associated with the specified Renderable ID.
std::shared_ptr<const Renderable> BasicRenderer::viewRenderable(const long int & renderableID) const
{
	return renderableManager.viewRenderable(renderableID);
}

//	Update the Shader Type associated with the specified RenderableID.
void BasicRenderer::updateShaderType(const long int & renderableID, const std::string & newShaderType)
{
	renderableManager.updateShaderType(renderableID, newShaderType);
}

//	Update the Geometry Type associated with the specified RenderableID.
void BasicRenderer::updateGeometryType(const long int & renderableID, const std::string & newGeometryType)
{
	renderableManager.updateGeometryType(renderableID, newGeometryType);
}

//	Update the Material Type associated with the specified RenderableID.
void BasicRenderer::updateMaterialType(const long int & renderableID, const std::string & newMaterialType)
{
	renderableManager.updateMaterialType(renderableID, newMaterialType);
}

//	Update the Transform Matrix associated with the specified RenderableID.
void BasicRenderer::updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix)
{
	renderableManager.updateTransformMatrix(renderableID, newModelMatrix);
}

//	Update the Camera.
void BasicRenderer::updateCamera(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Compute the View and Perspective Matrix.
	activeCamera->updateCamera();
}

//	Render the Scene.
void BasicRenderer::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "ERROR" << std::endl;
	}

	//	Update the associated Camera.
	updateCamera(deltaFrameTime, currentFrameTime, lastFrameTime);

	// Render the Scene to the Window, Eye parameter does not matter.
	renderScene(deltaFrameTime, currentFrameTime, lastFrameTime);
}

//	Render the Scene.
void BasicRenderer::renderScene(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Clear the Color.
	glClearColor(0, 0, 0, 1);

	//	Clear the Color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Render the Environment Maps.
	renderBackgroundEnvironment(deltaFrameTime, currentFrameTime, lastFrameTime);

	//	Get the list of the ShaderTypes and associated GeometryTypes.
	const std::map<std::string, std::vector<std::string>> shaderAndGeometryTypes = renderableManager.getShaderAndGeometryTypes();

	//	Render all the Renderables of the Shader Type. Opaque pass.
	for (auto shaderTypeIterator = shaderAndGeometryTypes.begin(); shaderTypeIterator != shaderAndGeometryTypes.end(); shaderTypeIterator++)
	{
		//	Check if there are any renderables using this shader.
		if (renderableManager.getShaderTypeRenderableNumber(shaderTypeIterator->first) != 0)
		{
			std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData(shaderTypeIterator->first);

			auto opacityFinder = rendererShaderData->shaderProperties.find("Output Opacity");

			if (opacityFinder != rendererShaderData->shaderProperties.end())
			{
				if (opacityFinder->second != "TRUE")
				{
					//	Bind the correct shader, get the Active Shader ID and the associated RendererShaderData.
					getShaderManager()->setActiveShader(shaderTypeIterator->first);

					//	Render the Renderables that use the Shader Data specified by the Renderer.
					renderRenderablesOfShaderType(*rendererShaderData, deltaFrameTime, currentFrameTime, lastFrameTime);
				}
			}
		}
	}

	//	Render all the Renderables of the Shader Type. Translucent pass.
	for (auto shaderTypeIterator = shaderAndGeometryTypes.begin(); shaderTypeIterator != shaderAndGeometryTypes.end(); shaderTypeIterator++)
	{
		//	Check if there are any renderables using this shader.
		if (renderableManager.getShaderTypeRenderableNumber(shaderTypeIterator->first) != 0)
		{
			std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData(shaderTypeIterator->first);

			auto opacityFinder = rendererShaderData->shaderProperties.find("Output Opacity");

			if (opacityFinder != rendererShaderData->shaderProperties.end())
			{
				if (opacityFinder->second == "TRUE")
				{
					//	Bind the correct shader, get the Active Shader ID and the associated RendererShaderData.
					getShaderManager()->setActiveShader(shaderTypeIterator->first);

					//	Render the Renderables that use the Shader Data specified by the Renderer.
					renderRenderablesOfShaderType(*rendererShaderData, deltaFrameTime, currentFrameTime, lastFrameTime);
				}
			}
		}
	}
}

//	Render the Environment Maps.
void BasicRenderer::renderBackgroundEnvironment(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	-----------------------------------------------------------------------------------------------------------------------------------------------------------	//

	//	Set the currently active shader to be the Environment Cubemap Shader.
	getShaderManager()->setActiveShader("ENVIRONMENT CUBE MAP SHADER");

	//	Set the currently active shader program.
	GLuint currentShaderProgramID = getShaderManager()->getActiveShader();
	std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData("ENVIRONMENT CUBE MAP SHADER");

	//	Upload the Camera Data.
	uploadCameraData(*rendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));

	//	Upload the Background Environment.
	uploadBackgroundEnviroment(*rendererShaderData);

	//	Bind the Vertex Array Object.
	glBindVertexArray(backgroundEnvironmentData.backgroundEnvironmentVAO);

	//	Bind the Vertex Buffer Object.
	glBindBuffer(GL_ARRAY_BUFFER, backgroundEnvironmentData.backgroundEnvironmentCubeMapVBO);

	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	//	Draw the Skybox.
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	//	Unbind the Vertex Buffer Object.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	Unbind the Vertex Array Object.
	glBindVertexArray(0);


	//	-----------------------------------------------------------------------------------------------------------------------------------------------------------	//

}

//	Render all the Renderables using the ShaderType.
void BasicRenderer::renderRenderablesOfShaderType(const RendererShaderData & rendererShaderData, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
		GLuint currentShaderProgramID = rendererShaderData.shaderID;

		//	Bind the Background Environment Maps.
		uploadBackgroundEnviroment(rendererShaderData);

		//	Upload the Camera Data.
		uploadCameraData(rendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));

		//	Update the Lights.
		uploadLightsData(rendererShaderData);

		//	Get the Required Geometry Description for the Shader Type.
		int currentShaderTypeRequirements = getShaderManager()->getShaderGeometryDescriptionRepresentation(rendererShaderData.shaderType);

		//	Get the Map of VAO Types to their VAOs.
		const std::map<int, std::shared_ptr<std::vector<VAOStorage>>> & mapVAOTypeToVAOs = vaoManager.viewMapVAOTypeToVAOs();

		//	Iterate over the VAO Types.
		for (auto vaoTypeIterator = mapVAOTypeToVAOs.begin(); vaoTypeIterator != mapVAOTypeToVAOs.end(); vaoTypeIterator++)
		{
			//	Check if the VAO Type fits with the Shader Type. 
			if ((vaoTypeIterator->first & currentShaderTypeRequirements) == currentShaderTypeRequirements)
			{
				//	Get the VAOs that match this type.
				std::shared_ptr<const std::vector<VAOStorage>> currentVAOStorages = vaoTypeIterator->second;

				//	Check if there are any VAOStorages.
				if (currentVAOStorages != NULL)
				{
					//	Iterate over the available VAOs.
					for (int currentVAONumber = 0; currentVAONumber < currentVAOStorages->size(); currentVAONumber++)
					{
						//	Bind the Vertex Array Object.
						glBindVertexArray((*currentVAOStorages)[currentVAONumber].getVAOID());

						//	Get the list of Geometry associated with the current VAO.
						const std::vector<std::string> geometryTypes = (*currentVAOStorages)[currentVAONumber].viewGeometryNames();

						//	Get the list of Geometry Data associated with the current VAO.
						const std::vector<std::shared_ptr<RendererGeometryData>> rendererGeometryDataList = (*currentVAOStorages)[currentVAONumber].viewGeometryDatas();

						//	Iterate over the Geometry in this VAO.
						for (int currentGeometryTypeNumber = 0; currentGeometryTypeNumber < geometryTypes.size(); currentGeometryTypeNumber++)
						{
							//	Get the Current Geometry Type.
							std::string currentGeometryType = geometryTypes[currentGeometryTypeNumber];

							//	Check if there are any available Renderables.
							if (renderableManager.getShaderTypeGeometryTypeRenderableNumber(rendererShaderData.shaderType, currentGeometryType) != 0)
							{								
								{
									//	Bind the correct Element and Array Buffer.
									glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererGeometryDataList[currentGeometryTypeNumber]->EBO);

									glBindVertexBuffer(0, rendererGeometryDataList[currentGeometryTypeNumber]->vertexVBO, 0, sizeof(Vertex));
									glBindVertexBuffer(1, rendererGeometryDataList[currentGeometryTypeNumber]->vertexVBO, offsetof(Vertex, normal), sizeof(Vertex));
									glBindVertexBuffer(2, rendererGeometryDataList[currentGeometryTypeNumber]->vertexVBO, offsetof(Vertex, color), sizeof(Vertex));
								}

								//	Check if the current shader requires the vertex normal data.
								if ((currentShaderTypeRequirements & 2) == 2)
								{
									glBindVertexBuffer(3, rendererGeometryDataList[currentGeometryTypeNumber]->vertexNormalVBO, 0, sizeof(VertexNormalData));
									glBindVertexBuffer(4, rendererGeometryDataList[currentGeometryTypeNumber]->vertexNormalVBO, offsetof(VertexNormalData, bitangent), sizeof(VertexNormalData));
								}


								//	Check if the current shader requires the vertex texture data.
								if ((currentShaderTypeRequirements & 4) == 4)
								{
									glBindVertexBuffer(5, rendererGeometryDataList[currentGeometryTypeNumber]->vertexTextureVBO, 0, sizeof(VertexTextureData));
									glBindVertexBuffer(6, rendererGeometryDataList[currentGeometryTypeNumber]->vertexTextureVBO, offsetof(VertexTextureData, textureCoordinates2), sizeof(VertexTextureData));
								}

								//	Get the list of the Renderables.
								std::shared_ptr<const std::vector<std::shared_ptr<Renderable>>> renderableList = renderableManager.viewRenderablesOfShaderTypeAndGeometryType(rendererShaderData.shaderType, currentGeometryType);

								//	Get the list of the Transforms.
								std::shared_ptr<const std::vector<glm::mat4>> transformMatrixList = renderableManager.viewTransformsOfShaderTypeAndGeometryType(rendererShaderData.shaderType, currentGeometryType);

								//	Get the list of the Materials.
								std::shared_ptr<const std::vector<std::string>> materialsList = renderableManager.viewMaterialsOfShaderTypeAndGeometryType(rendererShaderData.shaderType, currentGeometryType);

								//	Iterate over the Renderables that use both this Shader and Geometry.
								for (int i = 0; i < renderableList->size(); i++)
								{
									//	Update the Transform Matrix.
									uploadModelData(rendererShaderData, activeCamera->getViewMatrix(), (*transformMatrixList)[i]);

									//	Get the Current Material Data.
									std::shared_ptr<const std::pair<RendererMaterialValues, RendererMaterialMaps>> currentMaterialData = getMaterialManager()->viewMaterial((*materialsList)[i]);

									//	Upload the Shader Material Data.
									uploadMaterialData(rendererShaderData, currentMaterialData->first.diffuseAlbedo, currentMaterialData->first.specularAlbedo, currentMaterialData->first.emissiveColor, currentMaterialData->first.metallicRoughnessFresnelOpacity);

									//	Upload the Shader Material Texture Data.
									uploadMaterialTextureData(rendererShaderData, currentMaterialData->second.DiffuseAlbedoMap, currentMaterialData->second.SpecularAlbedoMap, currentMaterialData->second.MRFOMap, currentMaterialData->second.NormalMap, currentMaterialData->second.OcclusionMap);

									//	Draw the Elements.
									glDrawElements(rendererGeometryDataList[currentGeometryTypeNumber]->geometryDrawType, (GLsizei)rendererGeometryDataList[currentGeometryTypeNumber]->indicesArray.size(), GL_UNSIGNED_INT, 0);
								}
							}
						}

						//	Unbind the Vertex Array Object.
						glBindVertexArray(0);
					}
				}
			}
		}
}

//	Remove the Renderable specified by renderable ID.
void BasicRenderer::removeRenderable(const long int & renderableID)
{
	renderableManager.removeRenderable(renderableID);
}

//	Clean up the Renderer, especially the VRRendering Portion.
void BasicRenderer::cleanUpRenderer()
{


}

//	Set the Active Camera associated with this Renderer.
void BasicRenderer::setActiveCamera(std::shared_ptr<const Camera> activeCamera)
{

}

//	Return the Active Camera associated with this Renderer.
std::shared_ptr<Camera> BasicRenderer::getActiveCamera()
{
	return NULL;
}

//	Shut Down the Environment Maps.
void BasicRenderer::destroyBackgroundEnvironment()
{
	//	Unbind the Array
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	Delete the Vertex Buffer Object.
	glDeleteBuffers(1, &backgroundEnvironmentData.backgroundEnvironmentCubeMapVBO);

	//	Delete the Vertex Buffer Array.
	glDeleteVertexArrays(1, &backgroundEnvironmentData.backgroundEnvironmentVAO);

	//	Unbind the VAO.
	glBindVertexArray(0);
}

//	Add a Material to the Renderer.
void BasicRenderer::addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::addMaterial(newMaterialName, newMaterialData);
}

//	Update the Material in the Renderer.
void BasicRenderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void BasicRenderer::deleteMaterial(std::string deadMaterialName)
{
	Renderer::deleteMaterial(deadMaterialName);
}

//	Add the Geometry in the Renderer.
void BasicRenderer::addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::addGeometry(newGeometryName, newGeometryData);
	vaoManager.addGeometryToVAOStorage(getGeometryManager()->getGeometry(newGeometryName));
}

//	Update the Geometry in the Renderer.
void BasicRenderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::updateGeometry(currentGeometryName, newGeometryData);
	vaoManager.updateGeometry(getGeometryManager()->getGeometry(currentGeometryName));
}

//	Delete the Geometry in the Renderer.
void BasicRenderer::deleteGeometry(std::string deadGeometryName)
{
	vaoManager.removeGeometryFromVAOStorage(deadGeometryName);
	Renderer::deleteGeometry(deadGeometryName);
}

//	Add a shader to the Renderer.
void BasicRenderer::addShader(std::shared_ptr<ShaderData> newShaderData)
{
	Renderer::addShader(newShaderData);
}

//	Delete a Shader in the Renderer.
void BasicRenderer::deleteShader(std::string deadShaderName)
{
	Renderer::deleteShader(deadShaderName);
}

//	Add a Light to the Renderer.
void BasicRenderer::addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData)
{
	if (activeLights.size() < 16)
	{
		activeLights.push_back(newLightName);
	}

	Renderer::addLight(newLightName, newLightData);
}

//	Update the Light in the Renderer.
void BasicRenderer::updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData)
{
	Renderer::updateLight(currentLightName, newLightData);
}

//	Delete the Light in the Renderer.
void BasicRenderer::deleteLight(std::string deadLightName)
{
	for (int i = 0; i < activeLights.size(); i++)
	{
		if (activeLights[i] == deadLightName)
		{
			activeLights.erase(activeLights.begin() + i);
		}
	}

	Renderer::deleteLight(deadLightName);
}

//	Add a Texture to the Renderer.
void BasicRenderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::addTexture(newTextureName, newTextureData);
}

//	Update a Texture in the Renderer.
void BasicRenderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::updateTexture(currentTextureName, newTextureData);
}

//	Delete a Texture in the Renderer.
void BasicRenderer::deleteTexture(std::string deadTextureName)
{
	Renderer::deleteTexture(deadTextureName);
}

//	Bind the Environment Maps.
void BasicRenderer::uploadBackgroundEnviroment(const RendererShaderData & rendererShaderData)
{
  	//	-------------------------------------------------------------------------------------------------------------------------------------------	//
	glUniform4fv(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentIntensities, 1, glm::value_ptr(backgroundEnvironmentData.backgroundEnvironmentCubeMapsIntensities));

	//	The Active Texture 0.
	std::shared_ptr<const RendererTextureData> textureDataOne = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(textureDataOne->textureType, textureDataOne->textureID);
	}

	//	The Active Texture 1.
	std::shared_ptr<const RendererTextureData> textureDataTwo = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(textureDataTwo->textureType, textureDataTwo->textureID);
	}

	//	The Active Texture 2.
	std::shared_ptr<const RendererTextureData> textureDataThree = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(textureDataThree->textureType, textureDataThree->textureID);
	}

	//	The Active Texture 3.
	std::shared_ptr<const RendererTextureData> textureDataFour = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(textureDataFour->textureType, textureDataFour->textureID);
	}

	//	-------------------------------------------------------------------------------------------------------------------------------------------	//
}

//	Update the Camera Data.
void BasicRenderer::uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance)
{
	//	Upload the Camera Position.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_worldCameraPosition, 1, glm::value_ptr(worldCameraPosition));

	//	Upload the Camera Perspective Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

	//	Upload the Camera View Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//	Upload the Camera View Matrix without Translation.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_screenSpaceViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(activeCamera->getViewMatrix()))));

	//	Upload the Inverse Tranpose Camera View Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_inverseTransposeCameraViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(activeCamera->getViewMatrix())));

	//	Upload the Camera Near and Far Distance.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraNearFarPlaneDistance, 1, glm::value_ptr(cameraNearFarPlaneDistance));
}

//	Update the Model Data.
void BasicRenderer::uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix)
{
	//	Upload the Model Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//	Upload the Inverse Transpose Model Matrix.
	glUniformMatrix3fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(modelMatrix))));

	//	Upload the ModelView Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_modelViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix * modelMatrix));

	//	Upload the Inverse Transpose Model View Matrix.
	glUniformMatrix3fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(viewMatrix * modelMatrix))));
}

//	Update the Material Data.
void BasicRenderer::uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor,  const glm::vec4 & metallicnessRoughnessFresnelOpacity)
{
	//	Upload the Diffuse Albedo.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_diffuseAlbedo, 1, glm::value_ptr(diffuseAlbedo));

	//	Upload the Specular Albedo.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_specularAlbedo, 1, glm::value_ptr(specularAlbedo));

	//	Upload the Emissive COlor.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_emissiveColor, 1, glm::value_ptr(emissiveColor));

	//	Upload the Diffuse Albedo.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_metallicnessRoughnessFresnelOpacity, 1, glm::value_ptr(metallicnessRoughnessFresnelOpacity));
	
}

//	Update the Material Texture Data.
void BasicRenderer::uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap)
{
	//	Check for Diffuse Albedo Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_diffuseAlbedoMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE5);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(diffuseAlbedoMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_diffuseAlbedoMap, 5);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Specular Albedo Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_specularAlbedoMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE6);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(specularAlbedoMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_specularAlbedoMap, 6);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Emssive Color and Intensity Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_emssionColorAndIntensityMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE7);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(MRFOMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_emssionColorAndIntensityMap, 7);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Metallicness, Roughness and Fresnel and Opacity.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_metallicnessRoughnessFresnelOpacityMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE8);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(MRFOMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		//	Reset to the default active texture.
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_metallicnessRoughnessFresnelOpacityMap, 8);
		glActiveTexture(GL_TEXTURE0);
	}


}

//	Update the Lights.
void BasicRenderer::uploadLightsData(const RendererShaderData & rendererShaderData)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;
	GLuint currentLightAttributeLocation = -1;
	currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, ("u_ambientLight"));
	glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));

	//	Iterate over the active lights.
	for (int lightNumber = 0; lightNumber < 16; lightNumber++)
	{
		if (lightNumber < activeLights.size())
		{
			//	
			std::string currentLight = activeLights[lightNumber];
			std::shared_ptr<const RendererLightData> lightData = getLightManager()->viewLight(currentLight);

			//	
			std::string lightPrefix = "u_lights";
			std::string currentLightAttribute = "";
			GLuint currentLightAttributeLocation = -1;

			//	
			currentLightAttribute = "lightEnabledLocalLightType";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightEnabledShadowLightType));

			//	If the Current Light is not enabled, do not bother uploading all the other stuff.
			if (lightData->lightEnabledShadowLightType[0] == 1.0)
			{
				//	CurrentLight - Color
				currentLightAttribute = "lightColorAndLightIntensity";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightColorAndLightIntensity));

				//	CurrentLight - Position
				currentLightAttribute = "lightPosition";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightPosition));

				//	CurrentLight -	Attenuation
				currentLightAttribute = "lightConeDirection";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightConeDirection));

				//	CurrentLight -	spotCosCutOffAndExponent
				currentLightAttribute = "lightSpotCosCutOffAndExponent";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->spotCosCutOffAndExponent));
			}
		}
		else
		{

			//	
			std::string lightPrefix = "u_lights";
			std::string currentLightAttribute = "";
			GLuint currentLightAttributeLocation = -1;

			//	
			currentLightAttribute = "lightEnabledLocalLightType";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(glm::vec4(0.0)));
		}
	}

}
