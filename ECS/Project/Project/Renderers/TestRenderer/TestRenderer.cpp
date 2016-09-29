#include "TestRenderer.h"

#include "../Configuration/Configuration.h"
#include "../Transform/Transform.h"
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"
#include "../RendererResourceManagers/RendererLightManager/RendererLightManager.h"

//	Default TestRenderer Constructor
TestRenderer::TestRenderer()
{

}

//	Default TestRenderer Destructor
TestRenderer::~TestRenderer()
{

}

//	Initialize the Deferred Renderer.
void TestRenderer::initializeRenderer()
{
	//	Create the Active Camera to use.
	activeCamera = std::make_shared<Camera>();

	//	Initialize the Rendering Hints.
	initializeRenderingHints();

	//	Initialize the Environment Maps.
	initializeBackgroundEnvironment();

	//	Initialize Deferred Rendering Textures.
	initializeDeferredRenderingTextures();

	//	Initialize Deferred Rendering Framebuffers.
	initializeDeferredRenderingFramebuffers();

	//	Initialize Sampling Values.
	initializeSamplingValues();

	//	Initialize Noise Textures.
	initializeNoiseTextures();

	//	Initialize Lights.
	initializeLights();
}

//	Initialize the Rendering Hints.
void TestRenderer::initializeRenderingHints()
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

//	Initialize the Background Data.
void TestRenderer::initializeBackgroundEnvironment()
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

//	Initialize the Deferred Rendering Textures.
void TestRenderer::initializeDeferredRenderingTextures()
{
	//	Create the Texture for the Deferred Lighting Pass Texture.
	std::string newDeferredLightingPassTextureName = "DEFERRED_LIGHTING_PASS_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newDeferredLightingPassTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newDeferredLightingPassTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newDeferredLightingPassTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Deferred Lighting Pass.
	rendererPipelineTextures[newDeferredLightingPassTextureName] = newDeferredLightingPassTexture;


	//	Create the Deferred Lighting Depth Stencil Texture for the G Buffer.
	std::string newDeferredLightingDepthStencilTextureName = "DEFERRED_LIGHTING_DEPTH_STENCIL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newDeferredLightingDepthStencilTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the Deferred Lighting Depth Stencil Texture of the Texture ID.
	glGenTextures(1, &newDeferredLightingDepthStencilTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newDeferredLightingDepthStencilTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Depth Stencil Texture for the G Buffer for the name.
	rendererPipelineTextures[newDeferredLightingDepthStencilTextureName] = newDeferredLightingDepthStencilTexture;

	//	-----------------------------------------------------------------------------------------------------------------------------------	//

	initializeDeferredRenderingGBufferTextures();
}

//	Initialize the Deferred Rendering G Buffers.
void TestRenderer::initializeDeferredRenderingGBufferTextures()
{

	//	Create the World Space Vertex Position Texture for the G Buffer.
	std::string newWSVPTextureName = "G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newWSVPTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newWSVPTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newWSVPTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the World Space Vertex Position Texture for the G Buffer for the name.
	rendererPipelineTextures[newWSVPTextureName] = newWSVPTexture;


	//	Create the World Space Vertex Normal Texture for the G Buffer.
	std::string newWSVNTextureName = "G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newWSVNTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newWSVNTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newWSVNTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the World Space Vertex Normal Texture for the G Buffer for the name.
	rendererPipelineTextures[newWSVNTextureName] = newWSVNTexture;


	//	Create the View Space Vertex Position Texture for the G Buffer.
	std::string newVSVPTextureName = "G_BUFFER_VIEW_SPACE_VERTEX_POSITION_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newVSVPTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newVSVPTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newVSVPTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the View Space Vertex Position Texture for the G Buffer for the name.
	rendererPipelineTextures[newVSVPTextureName] = newVSVPTexture;


	//	Create the View Space Normal Texture for the G Buffer.
	std::string newVSVNTextureName = "G_BUFFER_VIEW_SPACE_VERTEX_NORMAL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newVSVNTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newVSVNTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newVSVNTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the View Space Normal Texture for the G Buffer for the name.
	rendererPipelineTextures[newVSVNTextureName] = newVSVNTexture;

	//	Create the Diffuse Albedo Texture for the G Buffer.
	std::string newDATextureName = "G_BUFFER_DIFFUSE_ALBEDO_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newDATexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newDATexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newDATexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Diffuse Albedo Texture for the G Buffer for the name.
	rendererPipelineTextures[newDATextureName] = newDATexture;

	//	Create the Specular Albedo Texture for the G Buffer.
	std::string newSATextureName = "G_BUFFER_SPECULAR_ALBEDO_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newSATexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newSATexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newSATexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Specular Albedo Texture for the G Buffer for the name.
	rendererPipelineTextures[newSATextureName] = newSATexture;

	//	Create the Emissive Color and Intensity Texture for the G Buffer.
	std::string newEMCITextureName = "G_BUFFER_EMISSIVE_COLOR_INTENSITIY_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newEMCITexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newEMCITexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newEMCITexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Emissive Color and Intensity Texture for the G Buffer for the name.
	rendererPipelineTextures[newEMCITextureName] = newEMCITexture;

	//	Create the Metallicness Roughness Fresnel Opacity Texture for the G Buffer.
	std::string newMRFOTextureName = "G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newMRFOTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newMRFOTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newMRFOTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Emissive Color and Intensity Texture for the G Buffer for the name.
	rendererPipelineTextures[newMRFOTextureName] = newMRFOTexture;

	//	Create the Depth Stencil Texture for the G Buffer.
	std::string newGBufferDepthStencilTextureName = "G_BUFFER_DEPTH_STENCIL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newGBufferDepthStencilTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newGBufferDepthStencilTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newGBufferDepthStencilTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Depth Stencil Texture for the G Buffer for the name.
	rendererPipelineTextures[newGBufferDepthStencilTextureName] = newGBufferDepthStencilTexture;
}

//	Initialize the Deferred Rendering Framebuffers.
void TestRenderer::initializeDeferredRenderingFramebuffers()
{
	//	Create an Entry for the Default Framebuffer.
	std::string newFramebufferName = "DEFAULT_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	newRendererFramebuffer->framebufferID = 0;
	rendererPipelineFramebuffers[newFramebufferName] = newRendererFramebuffer;

	//	Create the Entries for the  Deferred Rendering G Buffer Framebuffer.
	initializeDeferredRenderingGBufferFramebuffer();


	//	Create an Entry for the Light Depth Framebuffer.
	std::string lightdepthFramebufferName = "LIGHT_DEPTH_MAP_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newLightDepthMapFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	glGenFramebuffers(1, &newLightDepthMapFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newLightDepthMapFramebuffer->framebufferID);
	GLenum LightDepthMapBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };

	glDrawBuffers(1, LightDepthMapBuffers);
	rendererPipelineFramebuffers[lightdepthFramebufferName] = newLightDepthMapFramebuffer;


	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
}

//	Initialize the Deferred Rendering G Buffer Framebuffer.
void TestRenderer::initializeDeferredRenderingGBufferFramebuffer()
{
	//	Create an Entry for the Render to G Buffer Framebuffer.
	std::string newGBufferFramebufferName = "RENDER_TO_G_BUFFER_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newGBufferRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	//	Generate the Framebuffer to the G Buffer.
	glGenFramebuffers(1, &newGBufferRendererFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newGBufferRendererFramebuffer->framebufferID);

	//	Associate the Textures of the G Buffer with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_POSITION_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 3, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 4, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DIFFUSE_ALBEDO_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 5, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_SPECULAR_ALBEDO_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 6, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_EMISSIVE_COLOR_INTENSITIY_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 7, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE"]->textureID, 0);

	//	Associate the Depth Stencil Texture with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DEPTH_STENCIL_TEXTURE"]->textureID, 0);

	//	Check if the Framebuffer is complete.
	checkFramebufferStatus();

	//	Set up the 8 G Buffered Draw Buffers.
	GLenum GBufferedDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0, GL_COLOR_ATTACHMENT0 + 1, GL_COLOR_ATTACHMENT0 + 2, GL_COLOR_ATTACHMENT0 + 3, GL_COLOR_ATTACHMENT0 + 4, GL_COLOR_ATTACHMENT0 + 5,  GL_COLOR_ATTACHMENT0 + 6,  GL_COLOR_ATTACHMENT0 + 7 };
	glDrawBuffers(8, GBufferedDrawBuffers);

	//	Add the G Buffer Framebuffer.
	rendererPipelineFramebuffers[newGBufferFramebufferName] = newGBufferRendererFramebuffer;


	//	Create the Entry for the Deferred Lighting Pass Framebuffer.
	std::string newDeferredLightingPassFramebufferName = "DEFERRED_LIGHTING_PASS_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newDeferredLightingPassFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	//	Geneate the Framebuiffer for the Deferred Lighting Pass.
	glGenFramebuffers(1, &newDeferredLightingPassFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newDeferredLightingPassFramebuffer->framebufferID);

	//	Attach the Deferred Lighting Texture, and the Depth Stencil Texture.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["DEFERRED_LIGHTING_PASS_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["DEFERRED_LIGHTING_DEPTH_STENCIL_TEXTURE"]->textureID, 0);

	//	Check if the Framebuffer is complete.
	checkFramebufferStatus();

	GLenum DeferredLightingPass[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, DeferredLightingPass);

	//	Add the Deferred Lighting Pass Framebuffer.
	rendererPipelineFramebuffers[newDeferredLightingPassFramebufferName] = newDeferredLightingPassFramebuffer;



	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
}

//	Initialize Sampling Values.
void TestRenderer::initializeSamplingValues()
{
	sampler = std::make_shared<Sampler>(256);

}

//	Initialize The Noise Textures.
void TestRenderer::initializeNoiseTextures()
{
	GLubyte * pixelData = new GLubyte[windowScreenWidth * windowScreenHeight * 4];

	//	------------------------------------------------------------------------------------------------------------------------------	//
	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < windowScreenHeight; i++)
	{
		for (int j = 0; j < windowScreenWidth; j++)
		{
			pixelData[((i * windowScreenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}

	//	Generate the New Texture.
	glGenTextures(1, &rendererNoiseTextures.noiseTextureOneID);
	glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureOneID);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < windowScreenHeight; i++)
	{
		for (int j = 0; j < windowScreenWidth; j++)
		{
			pixelData[((i * windowScreenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}

	glGenTextures(1, &rendererNoiseTextures.noiseTextureTwoID);
	glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureTwoID);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < windowScreenHeight; i++)
	{
		for (int j = 0; j < windowScreenWidth; j++)
		{
			pixelData[((i * windowScreenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}



	glGenTextures(1, &rendererNoiseTextures.noiseTextureThreeID);
	glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureThreeID);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);


	//	------------------------------------------------------------------------------------------------------------------------------	//

	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < windowScreenHeight; i++)
	{
		for (int j = 0; j < windowScreenWidth; j++)
		{
			pixelData[((i * windowScreenWidth + j) * 4) + 0] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 1] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 2] = (GLubyte)RNGs::doubleRand(0.0, 255.0);

			pixelData[((i * windowScreenWidth + j) * 4) + 3] = (GLubyte)RNGs::doubleRand(0.0, 255.0);
		}
	}


	glGenTextures(1, &rendererNoiseTextures.noiseTextureFourID);
	glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureFourID);

	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	Set the Texture parameters.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//	Bind it to the appropriate location.
	glBindTexture(GL_TEXTURE_2D, 0);

	//	------------------------------------------------------------------------------------------------------------------------------	//

}

//	Initialize the Lights.
void TestRenderer::initializeLights()
{
	//	Set the default texture light names.
	for (int i = 0; i < 16; i++)
	{
		activeLightNames.push_back("NONE");
	}

	//	Add the appropriate textures to the lights.
	for (int i = 0; i < activeLightNames.size(); i++)
	{
		//	Push Back NULL.
		activeLights.push_back(NULL);

		LightShadowMapDescription lightShadowMapDescription;
		lightShadowMaps.push_back(lightShadowMapDescription);

		//	Set the Default Color and Depth Maps to be 0.
		lightShadowMaps[i].mainLightColorMap = 0;
		lightShadowMaps[i].mainLightDepthMap = 0;
		lightShadowMaps[i].lightColorCubeMap = 0;
		lightShadowMaps[i].lightDepthCubeMap = 0;

		//	Set the Active Texture 0.
		glActiveTexture(GL_TEXTURE0);

		//	Generate the 2D Light Color Map Texture.
		glGenTextures(1, &lightShadowMaps[i].mainLightColorMap);
		glBindTexture(GL_TEXTURE_2D, lightShadowMaps[i].mainLightColorMap);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 2048, 2048, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

		//	Generate the 2D Light Depth Map Texture.
		glGenTextures(1, &lightShadowMaps[i].mainLightDepthMap);
		glBindTexture(GL_TEXTURE_2D, lightShadowMaps[i].mainLightDepthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 2048, 2048, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

		//	Generate the CubeMap Color Map Texture.
		glGenTextures(1, &lightShadowMaps[i].lightColorCubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, lightShadowMaps[i].lightColorCubeMap);

		for (int j = 0; j < 6; j++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, 0, GL_RGBA32F, 2048, 2048, 0, GL_RGBA, GL_FLOAT, NULL);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		//	Generate the CubeMap Depth Map Texture.
		glGenTextures(1, &lightShadowMaps[i].lightDepthCubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, lightShadowMaps[i].lightDepthCubeMap);

		for (int j = 0; j < 6; j++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, 0, GL_DEPTH24_STENCIL8, 2048, 2048, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	//	Initialize to NO ERRORs.
	GLenum err = GL_NO_ERROR;

	//	Check for any errors.
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "ERROR : " << err << " ! " << std::endl;
	}
}

//	Create the Renderable and return the RenderableID.
long int TestRenderer::createRenderable()
{
	return renderableManager.createRenderable();
}

//	Return the const Renderable.
std::shared_ptr<const Renderable> TestRenderer::viewRenderable(const long int & renderableID) const
{
	return renderableManager.viewRenderable(renderableID);
}

//	Update the Renderable Shader Type.
void TestRenderer::updateShadingType(const long int & renderableID, ShadingTypes::ShadingType newShadingType)
{
	renderableManager.updateShadingType(renderableID, newShadingType);
}

//	Update the Renderable Geometry Type.
void TestRenderer::updateGeometryType(const long int & renderableID, const std::string & newGeometryName)
{
	renderableManager.updateGeometryType(renderableID, newGeometryName);
}

//	Update the Renderable Material Type.
void TestRenderer::updateMaterialType(const long int & renderableID, const std::string & newMaterialName)
{
	renderableManager.updateMaterialType(renderableID, newMaterialName);
}

//	Update the Renderable Transform Matrix.
void TestRenderer::updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix)
{
	renderableManager.updateTransformMatrix(renderableID, newModelMatrix);
}

//	Update the Camera.
void TestRenderer::updateCamera(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	activeCamera->updateCamera();
}

//	Render.
void TestRenderer::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Get the list of the ShaderTypes and associated GeometryTypes.
	const std::map<ShadingTypes::ShadingType, std::vector<std::string>> shaderAndGeometryTypes = renderableManager.getShadingTypesAndGeometryTypes();

	//	Initialize to NO ERRORs.
	GLenum err = GL_NO_ERROR;

	//	Check for any errors.
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "ERROR : " << err << " ! " << std::endl;
	}

	//	Render the Shadow Maps.
	renderShadowMaps(deltaFrameTime, currentFrameTime, lastFrameTime);

	//	Disable Blending.
	glDisable(GL_BLEND);

	//	Render the Deferred Rendering Pipeline.
	//	renderDeferredRenderingPipeline(deltaFrameTime, currentFrameTime, lastFrameTime);

	//	Enable Blending.
	glEnable(GL_BLEND);

	//	Render the Foward Rendering Pipeline.
	//	renderForwardRenderingPipeline(deltaFrameTime, currentFrameTime, lastFrameTime);

	//	Render the Post Process Pipeline.
	//	renderPostProcessPipeline(deltaFrameTime, currentFrameTime, lastFrameTime);
}

//	Render the Shadow Maps.
void TestRenderer::renderShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{

	//	Set the Viewport.
	glDisable(GL_CULL_FACE);

	//	Set the shader for the Point Light Shadow Map Rendering.
	getShaderManager()->setActiveShader("POINT LIGHT SHADOW MAP SHADER");
	std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData("POINT LIGHT SHADOW MAP SHADER");

	//	Initialize the errors to no errors.
	GLenum err1 = GL_NO_ERROR;

	//	Check for any errors.
	while ((err1 = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "OpenGL Pre-Shadowing Pass Error -> " << err1 << " ! " << std::endl;
	}

	//	Bind the Light Depth Map Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	for (int i = 0; i < 1; i++)
	{
		if (activeLightNames[i] != "NONE")
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		}
	}

	//	
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error -> " << err2 << std::endl;
	}


	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	glEnable(GL_CULL_FACE);
}

//	Render the Background.
void TestRenderer::renderBackgroundEnvironment(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
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

//	Render the Renderables that have to go through the Deferred Rendering Pipeline.
void TestRenderer::renderDeferredRenderingPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Bind the G Buffer Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["RENDER_TO_G_BUFFER_FRAMEBUFFER"]->framebufferID);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	//	
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Deferred Rendering First Pass Error -> " << err << std::endl;
	}

}

//	Render the Renderables that have to go through the Forward Rendering pipeline.
void TestRenderer::renderForwardRenderingPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Clear the Forward Rendering Buffer.

}

//	Render the Post Process Pipeline.
void TestRenderer::renderPostProcessPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	getShaderManager()->setActiveShader("COPY TEXTURE SHADER");
	std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData("COPY TEXTURE SHADER");

	//	Upload the Camera Data, the Noise Textures, the Sampling Data, and the Post Process Textures.
	uploadCameraData(*rendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
	uploadNoiseTextures(*rendererShaderData);
	uploadSamplingData(*rendererShaderData);
	uploadPostProcessTextures(*rendererShaderData, lightShadowMaps[0].mainLightColorMap, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_POSITION_TEXTURE"]->textureID, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post Process Error -> " << err << std::endl;
	}

}

//	Render all the Renderables using the ShaderType.
void TestRenderer::renderRenderablesOfShaderType(const RendererShaderData & rendererShaderData, const glm::mat4 & currentViewMatrix, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;

	//	Get the Required Geometry Description for the Shader Type.
	int currentShaderTypeRequirements = getShaderManager()->getShaderGeometryDescriptionRepresentation(rendererShaderData.shaderType);

	//	Get the Map of VAO Types to their VAOs.
	const std::map<int, std::shared_ptr<std::vector<VAOStorage>>> & mapVAOTypeToVAOs = vaoManager.viewMapVAOTypeToVAOs();
}

//	Remove the Renderable.
void TestRenderer::removeRenderable(const long int & renderableID)
{
	renderableManager.removeRenderable(renderableID);
}

//	Clean Up the Renderer.
void TestRenderer::cleanUpRenderer()
{

}

//	Set the Active Camera.
void TestRenderer::setActiveCamera(std::shared_ptr<const Camera> newActiveCamera)
{
	*activeCamera = *newActiveCamera;
}

//	Return the Active Camera.
std::shared_ptr<Camera> TestRenderer::getActiveCamera()
{
	return activeCamera;
}

//	Add the Material to the Renderer for use, under the Material Name.
void TestRenderer::addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::addMaterial(newMaterialName, newMaterialData);
}

//	Update the Material in the Renderer, specified by the Material Name.
void TestRenderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void TestRenderer::deleteMaterial(std::string deadMaterialName)
{
	Renderer::deleteMaterial(deadMaterialName);
}

//	Add the Geometry to the Renderer for use, under the Geometry Name.
void TestRenderer::addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::addGeometry(newGeometryName, newGeometryData);
	vaoManager.addGeometryToVAOStorage(getGeometryManager()->getGeometry(newGeometryName));
}

//	Update the Geometry in the Renderer, specified by the Geometry Name.
void TestRenderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::updateGeometry(currentGeometryName, newGeometryData);
	vaoManager.updateGeometry(getGeometryManager()->getGeometry(currentGeometryName));
}

//	Delete the Geometry.
void TestRenderer::deleteGeometry(std::string deadGeometryName)
{
	vaoManager.removeGeometryFromVAOStorage(deadGeometryName);
	Renderer::deleteGeometry(deadGeometryName);
}

//	Add Shader to the Renderer.
void TestRenderer::addShader(std::shared_ptr<ShaderData> newShaderData)
{
	Renderer::addShader(newShaderData);
}

//	Delete the Shader in the Renderer.
void TestRenderer::deleteShader(std::string deadShaderName)
{
	Renderer::deleteShader(deadShaderName);
}

//	Add the Light to the Renderer, under the name.
void TestRenderer::addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData)
{
	//	Add the LightData under the specified name.
	Renderer::addLight(newLightName, newLightData);

	//	Iterate over the lights.
	for (int i = 0; i < activeLightNames.size(); i++)
	{
		if (activeLightNames[i] == "NONE")
		{
			activeLightNames[i] = newLightName;
			activeLights[i] = getLightManager()->viewLight(newLightName);
			break;
		}
	}

}

//	Update the Light, as specified by the LightData.
void TestRenderer::updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData)
{
	Renderer::updateLight(currentLightName, newLightData);
}

//	Delete the Light.
void TestRenderer::deleteLight(std::string deadLightName)
{
	//	Iterate over the lights.
	for (int i = 0; i < activeLights.size(); i++)
	{
		if (activeLightNames[i] == deadLightName)
		{
			activeLightNames[i] = "NONE";
			activeLights[i] = NULL;
		}
	}

	//	Delete the Light from the Lights.
	Renderer::deleteLight(deadLightName);
}

//	Add the Texture to the Renderer, under the name.
void TestRenderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::addTexture(newTextureName, newTextureData);
}

//	Update the Texture in the Renderer, specified by name.
void TestRenderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::updateTexture(currentTextureName, newTextureData);
}

//	Delete the Texture in the Renderer.
void TestRenderer::deleteTexture(std::string deadTextureName)
{
	Renderer::deleteTexture(deadTextureName);
}

//	Bind the Environment Maps.
void TestRenderer::uploadBackgroundEnviroment(const RendererShaderData & rendererShaderData)
{
	//	-------------------------------------------------------------------------------------------------------------------------------------------	//
	glUniform4fv(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentIntensities, 1, glm::value_ptr(backgroundEnvironmentData.backgroundEnvironmentCubeMapsIntensities));

	//	The Active Texture 0.
	std::shared_ptr<const RendererTextureData> textureDataOne = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(textureDataOne->textureType, textureDataOne->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapOne, 0);
		glActiveTexture(GL_TEXTURE0);

	}

	//	The Active Texture 1.
	std::shared_ptr<const RendererTextureData> textureDataTwo = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(textureDataTwo->textureType, textureDataTwo->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapTwo, 1);
		glActiveTexture(GL_TEXTURE0);
	}

	//	The Active Texture 2.
	std::shared_ptr<const RendererTextureData> textureDataThree = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(textureDataThree->textureType, textureDataThree->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapThree, 2);
		glActiveTexture(GL_TEXTURE0);
	}

	//	The Active Texture 3.
	std::shared_ptr<const RendererTextureData> textureDataFour = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3] != "NONE")
	{
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(textureDataFour->textureType, textureDataFour->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapFour, 3);
		glActiveTexture(GL_TEXTURE0);
	}

	//	-------------------------------------------------------------------------------------------------------------------------------------------	//
}

//	Upload the Camera Data to the Shader Pipeline.
void TestRenderer::uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance)
{
	//	Upload the Camera Position.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_worldCameraPosition, 1, glm::value_ptr(worldCameraPosition));

	//	Upload the Camera Perspective Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

	//	Upload the Camera View Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//	Upload the Camera View Matrix without Translation.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_screenSpaceViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(activeCamera->getViewMatrix()))));

	//	Upload the Camera Near and Far Distance.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraNearFarPlaneDistance, 1, glm::value_ptr(cameraNearFarPlaneDistance));
}

//	Upload the Model Data to the Shader Pipeline.
void TestRenderer::uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix)
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

//	Upload the Material Data to the Shader Pipeline.
void TestRenderer::uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity)
{
	//	Upload the Diffuse Albedo.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_diffuseAlbedo, 1, glm::value_ptr(diffuseAlbedo));

	//	Upload the Specular Albedo.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_specularAlbedo, 1, glm::value_ptr(specularAlbedo));

	//	Upload the Emissive Color And Intensity.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_emissiveColor, 1, glm::value_ptr(emissiveColor));

	//	Upload the Material Properties.
	glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_metallicnessRoughnessFresnelOpacity, 1, glm::value_ptr(metallicnessRoughnessFresnelOpacity));
}

//	Update the Material Texture Data.
void TestRenderer::uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap)
{
	//	Check for Diffuse Albedo Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_diffuseAlbedoMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 5);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(diffuseAlbedoMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_diffuseAlbedoMap, 5);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Specular Albedo Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_specularAlbedoMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 6);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(specularAlbedoMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_specularAlbedoMap, 6);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Emssive Color and Intensity Map.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_emssionColorAndIntensityMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 7);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(MRFOMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_emssionColorAndIntensityMap, 7);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	//	Check for Metallicness, Roughness and Fresnel and Opacity.
	if (rendererShaderData.shaderUniforms.textureDataUniforms.u_metallicnessRoughnessFresnelOpacityMap != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 8);
		std::shared_ptr<const RendererTextureData> textureData = getTextureManager()->viewTexture(MRFOMap);
		glBindTexture(textureData->textureType, textureData->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.textureDataUniforms.u_metallicnessRoughnessFresnelOpacityMap, 8);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}


}

//	Upload the Shader Lights Data to the Shader Pipeline.
void TestRenderer::uploadLightsData(const RendererShaderData & rendererShaderData)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;
	GLuint currentLightAttributeLocation = -1;
	glUniform4fv(rendererShaderData.shaderUniforms.lightDataUniforms.u_ambientLight, 1, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));

	//	Iterate over the active lights.
	for (int lightNumber = 0; lightNumber < activeLightNames.size(); lightNumber++)
	{
		if (activeLightNames[lightNumber] != "NONE")
		{
			//	
			std::shared_ptr<const RendererLightData> lightData = activeLights[lightNumber];

			//	
			std::string lightPrefix = "u_lights";
			std::string currentLightAttribute = "";
			GLuint currentLightAttributeLocation = -1;

			//	
			currentLightAttribute = "lightEnabledShadowLightType";
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


				glActiveTexture(GL_TEXTURE0 + 40 + lightNumber);
				glBindTexture(GL_TEXTURE_2D, lightShadowMaps[lightNumber].mainLightColorMap);
				glBindTexture(GL_TEXTURE_CUBE_MAP, lightShadowMaps[lightNumber].lightColorCubeMap);

				currentLightAttribute = "mainLightColorMap";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform1i(currentLightAttributeLocation, 40 + lightNumber);

				currentLightAttribute = "lightColorCubeMap";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform1i(currentLightAttributeLocation, 40 + lightNumber);
			}
		}
		else
		{

			//	
			std::string lightPrefix = "u_lights";
			std::string currentLightAttribute = "";
			GLuint currentLightAttributeLocation = -1;

			//	
			currentLightAttribute = "lightEnabledShadowLightType";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(glm::vec4(0.0)));
		}
	}
}

//	Upload the Sampling Data.
void TestRenderer::uploadSamplingData(const RendererShaderData & rendererShaderData)
{
	//	Upload the Hemisphere Uniforms.
	glUniform4fv(rendererShaderData.shaderUniforms.samplingDataUniforms.u_hemisphereSamples, (int)sampler->viewHemisphereKernel().size(), glm::value_ptr(*sampler->viewHemisphereKernel().data()));

	//	Window Screen Size.
	glUniform2fv(rendererShaderData.shaderUniforms.samplingDataUniforms.u_screenSize, 1, glm::value_ptr(glm::vec2(windowScreenWidth, windowScreenHeight)));

	//	Upload the Hemisphere Radius.
	glUniform1f(rendererShaderData.shaderUniforms.samplingDataUniforms.u_hemisphereRadius, 2.0f);

	//	Upload the Unit Square Samples.
	glUniform4fv(rendererShaderData.shaderUniforms.samplingDataUniforms.u_unitSquareSamples, (int)sampler->viewUnitSquareSamples().size(), glm::value_ptr(*sampler->viewUnitSquareSamples().data()));

}

//	Upload the Noise Textures.
void TestRenderer::uploadNoiseTextures(const RendererShaderData & rendererShaderData)
{
	if (rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureOne != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 15);
		glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureOneID);
		glUniform1i(rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureOne, 15);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureTwo != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 16);
		glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureTwoID);
		glUniform1i(rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureTwo, 16);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureThree != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 17);
		glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureThreeID);
		glUniform1i(rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureThree, 17);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureOne != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 18);
		glBindTexture(GL_TEXTURE_2D, rendererNoiseTextures.noiseTextureFourID);
		glUniform1i(rendererShaderData.shaderUniforms.noiseTexturesUniforms.t_noiseTextureFour, 18);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Upload the G Buffer Data Textures.
void TestRenderer::uploadGBufferDataTextures(const RendererShaderData & rendererShaderData)
{

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexPosition != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 20);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexPosition, 20);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexNormal != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 21);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexNormal, 21);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_viewSpaceVertexPositionAndDepth != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 22);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_POSITION_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_viewSpaceVertexPositionAndDepth, 22);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_viewSpaceVertexNormal != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 23);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_VIEW_SPACE_VERTEX_NORMAL_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_viewSpaceVertexNormal, 23);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_diffuseAlbedo != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 24);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DIFFUSE_ALBEDO_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_diffuseAlbedo, 24);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_specularAlbedo != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 25);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_specularAlbedo, 25);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_emissionColorAndIntensity != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 26);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_SPECULAR_ALBEDO_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_emissionColorAndIntensity, 26);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_metallicnessRoughnessFresnelOpacity != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 27);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_metallicnessRoughnessFresnelOpacity, 27);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Upload the Post Process Textures.
void TestRenderer::uploadPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureOneID, GLuint postProcessTextureTwoID, GLuint postProcessTextureThreeID, GLuint postProcessTextureFourID)
{
	if (rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureOne != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 35);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureOneID);
		glUniform1i(rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureOne, 35);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureTwo != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 36);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureTwoID);
		glUniform1i(rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureTwo, 36);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureThree != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 37);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureThreeID);
		glUniform1i(rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureThree, 37);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureFour != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 38);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureFourID);
		glUniform1i(rendererShaderData.shaderUniforms.postProcessInputUniforms.pp_inputTextureFour, 38);
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Check the Framebuffer Status.
void TestRenderer::checkFramebufferStatus()
{

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch (status) {
	case GL_FRAMEBUFFER_COMPLETE:
		return;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		std::cout << "An attachment could not be bound to frame buffer object!" << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		std::cout << "Attachments are missing! At least one image (texture) must be bound to the frame buffer object!" << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		std::cout << "The dimensions of the buffers attached to the currently used frame buffer object do not match!" << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		std::cout << "The formats of the currently used frame buffer object are not supported or do not fit together!" << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		std::cout << "A Draw buffer is incomplete or undefinied. All draw buffers must specify attachment points that have images attached." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		std::cout << "A Read buffer is incomplete or undefinied. All read buffers must specify attachment points that have images attached." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		std::cout << "All images must have the same number of multisample samples." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
		std::cout << "If a layered image is attached to one attachment, then all attachments must be layered attachments. The attached layers do not have to have the same number of layers, nor do the layers have to come from the same kind of texture." << std::endl;
		break;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		std::cout << "Attempt to use an unsupported format combinaton!" << std::endl;
		break;

	default:
		std::cout << "Unknown error while attempting to create frame buffer object!" << std::endl;
		break;
	}
}

//	Destroy the Background Environment.
void TestRenderer::destroyBackgroundEnvironment()
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

//	Destroy the Noise Textures.
void TestRenderer::destroyNoiseTextures()
{
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureOneID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureTwoID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureThreeID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureFourID);
}

