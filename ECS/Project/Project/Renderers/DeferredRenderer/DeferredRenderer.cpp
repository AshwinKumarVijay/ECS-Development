#include "DeferredRenderer.h"

#include "../Configuration/Configuration.h"
#include "../Transform/Transform.h"
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"
#include "../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../RenderableManager/RenderableManager.h"

//	Default DeferredRenderer Constructor
DeferredRenderer::DeferredRenderer()
{

}

//	Default DeferredRenderer Destructor
DeferredRenderer::~DeferredRenderer()
{

}

//	Initialize the Deferred Renderer.
void DeferredRenderer::initializeRenderer()
{
	//	The Renderable Manager.
	renderableManager = std::make_shared<RenderableManager>();

	//	Initialize the Rendering Hints.
	initializeRenderingHints();

	//	Initialize the Environment Maps.
	initializeBackgroundEnvironment();

	//	Initialize Deferred Rendering Textures.
	initializeDeferredRenderingTextures();

	//	Initialize Deferred Rendering Framebuffers.
	initializeDeferredRenderingFramebuffers();

	//	Initialize the MSAA Textures and Framebuffers.
	initializeMSAATexturesAndFramebuffers();

	//	Initialize the Post Process Textures.
	initializePostProcessTextures();

	//	Initialize the Post Process Framebuffers.
	initializePostProcessFramebuffers();

	//	Initialize Sampling Values.
	initializeSamplingValues();

	//	Initialize Noise Textures.
	initializeNoiseTextures();

	//	Initialize Lights.
	initializeLights();


//	createAmbientOcclusionFramebufferObjectsAndTextures();
//	createBloomFramebufferObjectsAndTextures();
//	createHDRFrambufferObjectsAndTextures();
	createGaussianBlurFramebufferObjectsAndTextures();
}

//	Initialize the Rendering Hints.
void DeferredRenderer::initializeRenderingHints()
{
	//	Print some details.
	printf("%s\n", glGetString(GL_VENDOR));
	printf("%s\n", glGetString(GL_RENDERER));
	printf("%s\n", glGetString(GL_VERSION));
	printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

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

	//	The Shadow Map Resolution.
	shadowMapResolution = 2048;
}

//	Initialize the Background Data.
void DeferredRenderer::initializeBackgroundEnvironment()
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
void DeferredRenderer::initializeDeferredRenderingTextures()
{
	//	-----------------------------------------------------------------------------------------------------------------------------------	//

	//	Create the Deferred Rendering Lighting Pass Color Texture.
	std::string newDRLPCTextureName = "DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newDRLPCTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newDRLPCTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newDRLPCTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the World Space Vertex Position Texture for the G Buffer for the name.
	rendererPipelineTextures[newDRLPCTextureName] = newDRLPCTexture;

	//	-----------------------------------------------------------------------------------------------------------------------------------	//

	//	Create the Deferred Rendering Lighting Pass Depth Texture.
	std::string newDRLPDSTextureName = "DEFERRED_RENDERING_LIGHTING_PASS_DEPTH_STENCIL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newDRLPDSTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newDRLPDSTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newDRLPDSTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Add the Depth Stencil Texture for the G Buffer for the name.
	rendererPipelineTextures[newDRLPDSTextureName] = newDRLPDSTexture;

	//	-----------------------------------------------------------------------------------------------------------------------------------	//
	initializeDeferredRenderingGBufferTextures();
}

//	Initialize the Deferred Rendering Framebuffers.
void DeferredRenderer::initializeDeferredRenderingFramebuffers()
{
	//	Create an Entry for the Default Framebuffer.
	std::string newFramebufferName = "DEFAULT_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	newRendererFramebuffer->framebufferID = 0;
	rendererPipelineFramebuffers[newFramebufferName] = newRendererFramebuffer;

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);


	//	---------------------------------------------------------------------------------------------------------------------------------------------------------------------	//


	//	Create an Entry for the Deferred Rendering Lighting Pass Framebuffer.
	std::string newDeferredLightingFramebuffer = "RENDER_DEFERRED_LIGHTING_PASS_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newDeferredLightingRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	//	Generate the Framebuffer for the Deferred Rendering Lighting Pass.
	glGenFramebuffers(1, &newDeferredLightingRendererFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newDeferredLightingRendererFramebuffer->framebufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["DEFERRED_RENDERING_LIGHTING_PASS_DEPTH_STENCIL_TEXTURE"]->textureID, 0);

	//	
	GLenum DeferredLightingDrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DeferredLightingDrawBuffers);

	checkFramebufferStatus();

	//	Add the Deferred Lighting Framebuffer.
	rendererPipelineFramebuffers[newDeferredLightingFramebuffer] = newDeferredLightingRendererFramebuffer;

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);


	//	---------------------------------------------------------------------------------------------------------------------------------------------------------------------	//

	//	Create the Entries for the  Deferred Rendering G Buffer Framebuffer.
	initializeDeferredRenderingGBufferFramebuffer();
}

//	Initialize the Deferred Rendering G Buffers.
void DeferredRenderer::initializeDeferredRenderingGBufferTextures()
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
	std::string newWSVNTextureName = "G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_AND_DEPTH_TEXTURE";
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


	//	Create the Diffuse Albedo Texture for the G Buffer.
	std::string newDATextureName = "G_BUFFER_DIFFUSE_ALBEDO_AND_LIT_TYPE_TEXTURE";
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
	std::string newSATextureName = "G_BUFFER_SPECULAR_ALBEDO_AND_LIGHTING_TYPE_TEXTURE";
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

//	Initialize the Deferred Rendering G Buffer Framebuffer.
void DeferredRenderer::initializeDeferredRenderingGBufferFramebuffer()
{
	//	Create an Entry for the Render to G Buffer Framebuffer.
	std::string newGBufferFramebufferName = "RENDER_TO_G_BUFFER_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newGBufferRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	//	Generate the Framebuffer to the G Buffer.
	glGenFramebuffers(1, &newGBufferRendererFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newGBufferRendererFramebuffer->framebufferID);

	//	Associate the Textures of the G Buffer with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_AND_DEPTH_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DIFFUSE_ALBEDO_AND_LIT_TYPE_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 3, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_SPECULAR_ALBEDO_AND_LIGHTING_TYPE_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 4, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_EMISSIVE_COLOR_INTENSITIY_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 5, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE"]->textureID, 0);

	//	Associate the Depth Stencil Texture with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DEPTH_STENCIL_TEXTURE"]->textureID, 0);

	//	Check if the Framebuffer is complete.
	checkFramebufferStatus();

	//	Set up the 8 G Buffered Draw Buffers.
	GLenum GBufferedDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0, GL_COLOR_ATTACHMENT0 + 1, GL_COLOR_ATTACHMENT0 + 2, GL_COLOR_ATTACHMENT0 + 3, GL_COLOR_ATTACHMENT0 + 4, GL_COLOR_ATTACHMENT0 + 5 };
	glDrawBuffers(6, GBufferedDrawBuffers);

	//	Add the G Buffer Framebuffer.
	rendererPipelineFramebuffers[newGBufferFramebufferName] = newGBufferRendererFramebuffer;

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

}

//	Initialize the MSAA Textures and Framebuffers.
void DeferredRenderer::initializeMSAATexturesAndFramebuffers()
{
	//	-----------------------------------------------------------------------------------------------------------------------------------	//

	//	Create the Deferred Rendering Lighting Pass Color Texture.
	std::string newMSAADRLPCTextureName = "MSAA_DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newMSAADRLPCTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newMSAADRLPCTexture->textureID);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, newMSAADRLPCTexture->textureID);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 2, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	//	Add the World Space Vertex Position Texture for the G Buffer for the name.
	rendererPipelineTextures[newMSAADRLPCTextureName] = newMSAADRLPCTexture;

	//	-----------------------------------------------------------------------------------------------------------------------------------	//

	//	Create the Deferred Rendering Lighting Pass Depth Texture.
	std::string newMSAADRLPDSTextureName = "MSAA_DEFERRED_RENDERING_LIGHTING_PASS_DEPTH_STENCIL_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newMSAADRLPDSTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the G Buffer of the Texture ID.
	glGenTextures(1, &newMSAADRLPDSTexture->textureID);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, newMSAADRLPDSTexture->textureID);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 2, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	//	Add the Depth Stencil Texture for the G Buffer for the name.
	rendererPipelineTextures[newMSAADRLPDSTextureName] = newMSAADRLPDSTexture;

	//	-----------------------------------------------------------------------------------------------------------------------------------	//


	//	Create an Entry for the MSAA Deferred Rendering Lighting Pass Framebuffer.
	std::string newMSAADeferredLightingFramebuffer = "MSAA_RENDER_DEFERRED_LIGHTING_PASS_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newMSAADeferredLightingRendererFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	//	Generate the Framebuffer for the Deferred Rendering Lighting Pass.
	glGenFramebuffers(1, &newMSAADeferredLightingRendererFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newMSAADeferredLightingRendererFramebuffer->framebufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D_MULTISAMPLE, rendererPipelineTextures["MSAA_DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, rendererPipelineTextures["MSAA_DEFERRED_RENDERING_LIGHTING_PASS_DEPTH_STENCIL_TEXTURE"]->textureID, 0);
	checkFramebufferStatus();

	//	
	GLenum MSAADeferredLightingDrawBuffers[] = { GL_COLOR_ATTACHMENT0 };


	//	Add the Deferred Lighting Framebuffer.
	rendererPipelineFramebuffers[newMSAADeferredLightingFramebuffer] = newMSAADeferredLightingRendererFramebuffer;

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
}

//	Initialize the Post Process Textures.
void DeferredRenderer::initializePostProcessTextures()
{
	//	Ambient Color Pass Texture.
	std::string newAmbientColorPassTextureName = "AMBIENT_COLOR_PASS_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newAmbientColorPassTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newAmbientColorPassTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newAmbientColorPassTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Color Pass Texture.
	rendererPipelineTextures[newAmbientColorPassTextureName] = newAmbientColorPassTexture;

	//	Ambient Color Pass Texture.
	std::string newAmbientDepthPassTextureName = "AMBIENT_DEPTH_PASS_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newAmbientDepthPassTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newAmbientDepthPassTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newAmbientDepthPassTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Color Pass Texture.
	rendererPipelineTextures[newAmbientDepthPassTextureName] = newAmbientDepthPassTexture;

	//	Ambient Occlusion Color Texture.
	std::string newAmbientOcclusionColorTextureName = "AMBIENT_OCCLUSION_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newAmbientOcclusionColorTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newAmbientOcclusionColorTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newAmbientOcclusionColorTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Color Texture.
	rendererPipelineTextures[newAmbientOcclusionColorTextureName] = newAmbientOcclusionColorTexture;

	//	Ambient Occlusion Depth Texture.
	std::string newAmbientOcclusionDepthTextureName = "AMBIENT_OCCLUSION_DEPTH_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newAmbientOcclusionDepthTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newAmbientOcclusionDepthTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newAmbientOcclusionDepthTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Depth Texture.
	rendererPipelineTextures[newAmbientOcclusionDepthTextureName] = newAmbientOcclusionDepthTexture;



	//	FXAA Color Texture.
	std::string newFXAAColorTextureName = "FXAA_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newFXAAColorTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newFXAAColorTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newFXAAColorTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Color Texture.
	rendererPipelineTextures[newFXAAColorTextureName] = newFXAAColorTexture;

	//	FXAA  Depth Texture.
	std::string newFXAADepthTextureName = "FXAA_DEPTH_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newFXAADepthTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newFXAADepthTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newFXAADepthTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Depth Texture.
	rendererPipelineTextures[newFXAADepthTextureName] = newFXAADepthTexture;


	//	Bloom Extraction Color Texture.
	std::string newBloomExtractionColorTextureName = "BLOOM_EXTRACTION_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newBloomExtractionColorTexture = std::make_shared<RendererPipelineTexture>();

	//	Bloom Extraction Depth Texture.
	glGenTextures(1, &newBloomExtractionColorTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newBloomExtractionColorTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Depth Texture.
	rendererPipelineTextures[newBloomExtractionColorTextureName] = newBloomExtractionColorTexture;


	//	Bloom Extraction Depth Texture.
	std::string newBloomExtractionDepthTextureName = "BLOOM_EXTRACTION_DEPTH_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newBloomExtractionDepthTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newBloomExtractionDepthTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newBloomExtractionDepthTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Bloom Extraction Depth Texture.
	rendererPipelineTextures[newBloomExtractionDepthTextureName] = newBloomExtractionDepthTexture;


	//	Bloom Extraction Color Texture.
	std::string newBloomColorTextureName = "BLOOM_COLOR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newBloomColorTexture = std::make_shared<RendererPipelineTexture>();

	//	Bloom Extraction Depth Texture.
	glGenTextures(1, &newBloomColorTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newBloomColorTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Entry for the Ambient Occlusion Depth Texture.
	rendererPipelineTextures[newBloomColorTextureName] = newBloomColorTexture;

	//	Bloom Extraction Depth Texture.
	std::string newBloomDepthTextureName = "BLOOM_DEPTH_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newBloomDepthTexture = std::make_shared<RendererPipelineTexture>();

	//	Generate the texture details.
	glGenTextures(1, &newBloomDepthTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newBloomDepthTexture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Bloom Extraction Depth Texture.
	rendererPipelineTextures[newBloomDepthTextureName] = newBloomDepthTexture;


}

//	Initialize the Post Prcesss Framebuffers.
void DeferredRenderer::initializePostProcessFramebuffers()
{
	//	Create an Entry for the Light Depth Framebuffer.
	std::string newPostProcessFramebufferName = "SINGLE_TEXTURE_OUTPUT_POST_PROCESS_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newPostProcessFramebuffer = std::make_shared<RendererPipelineFramebuffer>();

	glGenFramebuffers(1, &newPostProcessFramebuffer->framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, newPostProcessFramebuffer->framebufferID);

	GLenum PostProcessBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };

	glDrawBuffers(1, PostProcessBuffers);
	rendererPipelineFramebuffers[newPostProcessFramebufferName] = newPostProcessFramebuffer;

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

}

//	Initialize Sampling Values.
void DeferredRenderer::initializeSamplingValues()
{
	sampler = std::make_shared<Sampler>(16);

}

//	Initialize The Noise Textures.
void DeferredRenderer::initializeNoiseTextures()
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
void DeferredRenderer::initializeLights()
{
	//	Set the default texture light names.
	for (int i = 0; i < 16; i++)
	{
		activeLightNames.push_back("NONE");
		activeLights.push_back(NULL);
	}

	//	Create the Shadow Mapping Frambuffers and Textures.
	createShadowMappingFramebuffersAndTextures();

	//	Initialize to NO ERRORs.
	GLenum err = GL_NO_ERROR;

	//	Check for any errors.
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "ERROR : " << err << " ! " << std::endl;
	}
}

//	Create the Gaussian Blur Framebuffer Object.
void DeferredRenderer::createGaussianBlurFramebufferObjectsAndTextures()
{
	//	
	GLenum err1 = GL_NO_ERROR;
	while ((err1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre - Gaussian Blur - Creation Error -> " << err1 << std::endl;
	}

	//	Create the Copy Framebuffer for the Gaussian Blur.
	std::string newGaussianBlurFramebufferCopyName = "GAUSSIAN_BLUR_FRAMEBUFFER_COPY";
	std::shared_ptr<RendererPipelineFramebuffer> newGaussianBlurFramebufferCopy = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newGaussianBlurFramebufferCopy->framebufferID);

	GLenum GaussianBlurCopyDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newGaussianBlurFramebufferCopy->framebufferID, 1, GaussianBlurCopyDrawBuffers);
	rendererPipelineFramebuffers[newGaussianBlurFramebufferCopyName] = newGaussianBlurFramebufferCopy;

	//	Create the first Texture for Gaussian Blur.
	std::string newGaussianBlurTextureOneName = "GAUSSIAN_BLUR_TEXTURE_ONE";
	std::shared_ptr<RendererPipelineTexture> newGaussianBlurTextureOne = std::make_shared<RendererPipelineTexture>();

	glGenTextures(1, &newGaussianBlurTextureOne->textureID);
	glBindTexture(GL_TEXTURE_2D, newGaussianBlurTextureOne->textureID);
	glTextureImage2DEXT(newGaussianBlurTextureOne->textureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTextureParameteri(newGaussianBlurTextureOne->textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(newGaussianBlurTextureOne->textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	rendererPipelineTextures[newGaussianBlurTextureOneName] = newGaussianBlurTextureOne;

	//	Create the second Texture for Gaussian Blur.
	std::string newGaussianBlurTextureTwoName = "GAUSSIAN_BLUR_TEXTURE_TWO";
	std::shared_ptr<RendererPipelineTexture> newGaussianBlurTextureTwo = std::make_shared<RendererPipelineTexture>();

	glGenTextures(1, &newGaussianBlurTextureTwo->textureID);
	glBindTexture(GL_TEXTURE_2D, newGaussianBlurTextureOne->textureID);
	glTextureImage2DEXT(newGaussianBlurTextureTwo->textureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTextureParameteri(newGaussianBlurTextureTwo->textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(newGaussianBlurTextureTwo->textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	rendererPipelineTextures[newGaussianBlurTextureTwoName] = newGaussianBlurTextureTwo;


	//	Create the first Frambuffer for the Gaussian Blur.
	std::string newGaussianBlurFramebufferOneName = "GAUSSIAN_BLUR_FRAMEBUFFER_ONE";
	std::shared_ptr<RendererPipelineFramebuffer> newGaussianBlurFramebufferOne = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newGaussianBlurFramebufferOne->framebufferID);
	glNamedFramebufferTexture2DEXT(newGaussianBlurFramebufferOne->framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newGaussianBlurTextureTwo->textureID, 0);

	GLenum GaussianBlurOneDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newGaussianBlurFramebufferOne->framebufferID, 1, GaussianBlurOneDrawBuffers);
	rendererPipelineFramebuffers[newGaussianBlurFramebufferOneName] = newGaussianBlurFramebufferOne;

	//	Create the second Frambuffer for the Gaussian Blur.
	std::string newGaussianBlurFramebufferTwoName = "GAUSSIAN_BLUR_FRAMEBUFFER_TWO";
	std::shared_ptr<RendererPipelineFramebuffer> newGaussianBlurFramebufferTwo = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newGaussianBlurFramebufferTwo->framebufferID);
	glNamedFramebufferTexture2DEXT(newGaussianBlurFramebufferTwo->framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newGaussianBlurTextureOne->textureID, 0);

	GLenum GaussianBlurTwoDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newGaussianBlurFramebufferTwo->framebufferID, 1, GaussianBlurTwoDrawBuffers);
	rendererPipelineFramebuffers[newGaussianBlurFramebufferTwoName] = newGaussianBlurFramebufferTwo;

}

//	Create the Framebuffer Objects And Textures for the Ambient Occlusion pass.
void DeferredRenderer::createAmbientOcclusionFramebufferObjectsAndTextures()
{
	//	Create the Texture for Ambient Occlusion.
	std::string newAmbientOcclusionTextureName = "AMBIENT_OCCLUSION_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newAmbientOcclusionTexture = std::make_shared<RendererPipelineTexture>();

	glGenTextures(1, &newAmbientOcclusionTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newAmbientOcclusionTexture->textureID);
	glTextureImage2DEXT(newAmbientOcclusionTexture->textureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	rendererPipelineTextures[newAmbientOcclusionTextureName] = newAmbientOcclusionTexture;
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Framebuffer for Ambient Occlusion.
	std::string newAmbientOcclusionFramebufferName = "AMBIENT_OCCLUSION_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newAmbientOcclusionFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newAmbientOcclusionFramebuffer->framebufferID);
	glNamedFramebufferTexture2DEXT(newAmbientOcclusionFramebuffer->framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newAmbientOcclusionTexture->textureID, 0);

	GLenum AmbientOcclusionDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newAmbientOcclusionFramebuffer->framebufferID, 1, AmbientOcclusionDrawBuffers);

}

//	Create the HDR Framebuffers and Textures.
void DeferredRenderer::createHDRFrambufferObjectsAndTextures()
{
	//	Create the Texture for HDR
	std::string newHDRTextureName = "HDR_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newHDRTexture = std::make_shared<RendererPipelineTexture>();

	glGenTextures(1, &newHDRTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newHDRTexture->textureID);
	glTextureImage2DEXT(newHDRTexture->textureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	rendererPipelineTextures[newHDRTextureName] = newHDRTexture;
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Framebuffer for HDR.
	std::string newHDRFramebufferName = "HDR_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newHDRFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newHDRFramebuffer->framebufferID);
	glNamedFramebufferTexture2DEXT(newHDRFramebuffer->framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newHDRTexture->textureID, 0);

	GLenum HDRDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newHDRFramebuffer->framebufferID, 1, HDRDrawBuffers);
}

//	Create the Bloom Framebuffers and Textures.
void DeferredRenderer::createBloomFramebufferObjectsAndTextures()
{
	//	Create the Texture for HDR
	std::string newBloomTextureName = "BLOOM_TEXTURE";
	std::shared_ptr<RendererPipelineTexture> newBloomTexture = std::make_shared<RendererPipelineTexture>();

	glGenTextures(1, &newBloomTexture->textureID);
	glBindTexture(GL_TEXTURE_2D, newBloomTexture->textureID);
	glTextureImage2DEXT(newBloomTexture->textureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	rendererPipelineTextures[newBloomTextureName] = newBloomTexture;
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Create the Framebuffer for HDR.
	std::string newBloomFramebufferName = "BLOOM_FRAMEBUFFER";
	std::shared_ptr<RendererPipelineFramebuffer> newBloomFramebuffer = std::make_shared<RendererPipelineFramebuffer>();
	glCreateFramebuffers(1, &newBloomFramebuffer->framebufferID);
	glNamedFramebufferTexture2DEXT(newBloomFramebuffer->framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newBloomTexture->textureID, 0);

	GLenum BloomDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glNamedFramebufferDrawBuffers(newBloomFramebuffer->framebufferID, 1, BloomDrawBuffers);

}

//	Create Shadow Mapping Framebuffers and Textures. 
void DeferredRenderer::createShadowMappingFramebuffersAndTextures()
{

	pointLightDepthCubeMaps.lightColorCubeMap = 0;
	pointLightDepthCubeMaps.lightDepthCubeMap = 0;

	glGenTextures(1, &pointLightDepthCubeMaps.lightColorCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightColorCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glGenTextures(1, &pointLightDepthCubeMaps.lightDepthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightDepthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glTextureParameteri(pointLightDepthCubeMaps.lightColorCubeMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(pointLightDepthCubeMaps.lightColorCubeMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(pointLightDepthCubeMaps.lightColorCubeMap, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTextureParameteri(pointLightDepthCubeMaps.lightColorCubeMap, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTextureParameteri(pointLightDepthCubeMaps.lightColorCubeMap, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	glTextureParameteri(pointLightDepthCubeMaps.lightDepthCubeMap, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(pointLightDepthCubeMaps.lightDepthCubeMap, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(pointLightDepthCubeMaps.lightDepthCubeMap, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTextureParameteri(pointLightDepthCubeMaps.lightDepthCubeMap, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTextureParameteri(pointLightDepthCubeMaps.lightDepthCubeMap, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	//	May be Deprecated.
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightColorCubeMap);
	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA32F, shadowMapResolution, shadowMapResolution, 0, GL_RGBA, GL_FLOAT, NULL);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	//	May be Deprecated.
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightDepthCubeMap);
	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH24_STENCIL8, shadowMapResolution, shadowMapResolution, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	//	Add the appropriate textures to the lights.
	for (int currentLightNumber = 0; currentLightNumber < activeLightNames.size(); currentLightNumber++)
	{
		unsigned int newLightColorMapTextureID = 0;
		
		glGenTextures(1, &newLightColorMapTextureID);
		glBindTexture(GL_TEXTURE_2D, newLightColorMapTextureID);
		glTextureImage2DEXT(newLightColorMapTextureID, GL_TEXTURE_2D, 0, GL_RGBA32F, windowScreenWidth, windowScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTextureParameteri(newLightColorMapTextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(newLightColorMapTextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		unsigned int newLightDepthMapTextureID = 0;

		glGenTextures(1, &newLightDepthMapTextureID);
		glBindTexture(GL_TEXTURE_2D, newLightDepthMapTextureID);
		glBindTexture(GL_TEXTURE_2D, 0);

		glTextureImage2DEXT(newLightDepthMapTextureID, GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, windowScreenWidth, windowScreenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glTextureParameteri(newLightDepthMapTextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(newLightDepthMapTextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		LightMetaData newLightMetaData;
		newLightMetaData.currentViewLightColorMap = newLightColorMapTextureID;
		newLightMetaData.currentViewLightDepthMap = newLightDepthMapTextureID;

		for (int i = 0; i < 6; i++)
		{
			glCreateFramebuffers(1, &newLightMetaData.lightFramebufferObjects[i]);
			glNamedFramebufferTexture2DEXT(newLightMetaData.lightFramebufferObjects[i], GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, pointLightDepthCubeMaps.lightColorCubeMap, 0);
			glNamedFramebufferTexture2DEXT(newLightMetaData.lightFramebufferObjects[i], GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, pointLightDepthCubeMaps.lightDepthCubeMap, 0);

			GLenum lightFramebufferDrawBuffers = { GL_COLOR_ATTACHMENT0 + 0};
			glNamedFramebufferDrawBuffers(newLightMetaData.lightFramebufferObjects[i], 1, &lightFramebufferDrawBuffers);

		}

		glCreateFramebuffers(1, &newLightMetaData.currentViewFramebufferObject);
		glNamedFramebufferTexture2DEXT(newLightMetaData.currentViewFramebufferObject, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, newLightMetaData.currentViewLightColorMap, 0);
		glNamedFramebufferTexture2DEXT(newLightMetaData.currentViewFramebufferObject, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, newLightMetaData.currentViewLightDepthMap, 0);

		GLenum currentViewLightFramebufferObject = { GL_COLOR_ATTACHMENT0 + 0 };
		glNamedFramebufferDrawBuffers(newLightMetaData.currentViewFramebufferObject, 1, &currentViewLightFramebufferObject);

		activeLightDatas.push_back(newLightMetaData);
	}
}

//	Create the Renderable and return the RenderableID.
long int DeferredRenderer::createRenderable()
{
	return renderableManager->createRenderable();
}

//	Return the const Renderable.
std::shared_ptr<const Renderable> DeferredRenderer::viewRenderable(const long int & renderableID) const
{
	return renderableManager->viewRenderable(renderableID);
}

//	Update the Renderable Shader Type.
void DeferredRenderer::updateShadingType(const long int & renderableID, const std::string & newShaderType)
{
	renderableManager->updateShadingType(renderableID, newShaderType);
}

//	Update the Renderable Geometry Type.
void DeferredRenderer::updateGeometryType(const long int & renderableID, const std::string & newGeometryName)
{
	renderableManager->updateGeometryType(renderableID, newGeometryName);
}

//	Update the Renderable Material Type.
void DeferredRenderer::updateMaterialType(const long int & renderableID, const std::string & newMaterialName)
{
	renderableManager->updateMaterialType(renderableID, newMaterialName);
}

//	Update the Renderable Transform Matrix.
void DeferredRenderer::updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix)
{
	renderableManager->updateTransformMatrix(renderableID, newModelMatrix);
}

//	Render!
void DeferredRenderer::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Initialize to NO ERRORs.
	GLenum preerr = GL_NO_ERROR;

	//	Check for any errors.
	while ((preerr = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "OpenGL Pre - Rendering Error : " << preerr << " ! " << std::endl;
	}

	glEnable(GL_DEBUG_OUTPUT);
	std::string dg = "DBG_DG";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, 7, dg.c_str());
	//	Render the Deferred Rendering Pipeline.
	renderDeferredRenderingGBufferPass(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
	glPopDebugGroup();


	//	Render the Shadow Maps.
	std::string sm = "DBG_SM";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, 7, sm.c_str());
	renderShadowMaps(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
	glPopDebugGroup();

	//	Render the Ambient Occlusion Pass.
	std::string ao = "DBG_AO";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 2, 7, ao.c_str());
	renderAmbientOcclusionPass(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
	glPopDebugGroup();

	std::string dl = "DBG_DL";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 3, 7, dl.c_str());
	//	Render the Deferred Rendering Lighting Pipeline.
	renderDeferredRenderingLightingPass(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
	glPopDebugGroup();

	//	Render the Foward Rendering Pipeline.
	//	renderForwardRenderingPipeline(deltaFrameTime, currentFrameTime, lastFrameTime);


	std::string pp = "DBG_PP";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 4, 7, pp.c_str());
	//	Render the Post Process Pipeline.
	renderPostProcessPipeline(deltaFrameTime, currentFrameTime, lastFrameTime, activeCamera);
	glPopDebugGroup();


	//	Initialize to NO ERRORs.
	GLenum posterror = GL_NO_ERROR;

	//	Check for any errors.
	while ((posterror = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		std::cout << "OpenGL Post - Rendering Error : " << posterror << " ! " << std::endl;
	}


}

//	Render the Background.
void DeferredRenderer::renderBackgroundEnvironment(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	-----------------------------------------------------------------------------------------------------------------------------------------------------------	//

	//	Set the currently active shader to be the Environment Cubemap Shader.
	std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->setActiveShader("ENVIRONMENT CUBE MAP SHADER");
	GLuint currentShaderProgramID = rendererShaderData->shaderID;

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

//	Render the Renderables that have to go through the Deferred Rendering Pipeline in to the G Buffer.
void DeferredRenderer::renderDeferredRenderingGBufferPass(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Deferred Renderer - First Pass - Render to the G Buffer.

	//	Check for Errors.
	GLenum err1 = GL_NO_ERROR;
	while ((err1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre - Deferred Rendering G Buffer Pass Error -> " << err1 << std::endl;
	}

	//	Disable Blending.
	glDisable(GL_BLEND);

	//	Bind the G Buffer Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["RENDER_TO_G_BUFFER_FRAMEBUFFER"]->framebufferID);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Check the Framebuffer Status.
	checkFramebufferStatus();

	//	
	const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = renderableManager->getRenderableTypeBatchMetaDatas();

	for (auto currentRenderableType = renderableBatchTypes.begin(); currentRenderableType != renderableBatchTypes.end(); currentRenderableType++)
	{
		if (currentRenderableType->renderableTypeBatch->getIsValidRenderableType())
		{
			std::shared_ptr<const RendererShaderData> currentRendererShaderData = getRendererShaderDataForRenderableShadingType(currentRenderableType->renderableType.shaderType);
			getShaderManager()->setActiveShader(currentRendererShaderData->shaderType);

			//	Upload the Background, and Camera Data.
			uploadBackgroundEnviroment(*currentRendererShaderData);
			uploadCameraData(*currentRendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));

			std::string shaderType = getRendererShaderDataForRenderableShadingType(currentRenderableType->renderableType.shaderType)->shaderType;
			auto shaderOutputOpacity = getShaderManager()->viewShaderData(shaderType)->shaderProperties.find("Shader Output Opacity");

			if (shaderOutputOpacity != getShaderManager()->viewShaderData(shaderType)->shaderProperties.end())
			{
				if (shaderOutputOpacity->second != "True")
				{
					//	Render the Renderables that use the Shader Data specified by the Renderer.
					renderRenderablesOfShaderType(currentRenderableType->renderableType.shaderType, *currentRendererShaderData, activeCamera->getViewMatrix(), deltaFrameTime, currentFrameTime, lastFrameTime);

				}
			}
		}
	}


	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	//	Enable Blending.
	glEnable(GL_BLEND);


	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Deferred Rendering G Buffer Pass Error -> " << err2 << std::endl;
	}
}

//	Render the Shadow Maps.
void DeferredRenderer::renderShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre - Shadowing Pass Error -> " << err << std::endl;
	}

	//	Iterate over the Lights.
	for (int currentLightNumber = 0; currentLightNumber < activeLightNames.size(); currentLightNumber++)
	{

		//	Check if we are at an active light.
		bool shadowing = (activeLightNames[currentLightNumber] != "NONE");

		if (shadowing)
		{
			shadowing = (((activeLights[currentLightNumber]->lightEnabledShadowLightType[1] == 1.0)) && shadowing);
		}

		if (shadowing)
		{
			//	---------------------------------------------------------------------------------------------------------------	//

			//	
			GLenum err1 = GL_NO_ERROR;
			while ((err1 = glGetError()) != GL_NO_ERROR)
			{
				std::cout << "OpenGL Pre - Active Light Shadowing Pass Error -> " << err1 << std::endl;
			}

			//	Set the Blending, the Viewport and the Culling. 
			glEnable(GL_BLEND);
			glViewport(0, 0, shadowMapResolution, shadowMapResolution);
			glCullFace(GL_FRONT);

			//	Set the shader for the Point Light Shadow Map Rendering.
			getShaderManager()->setActiveShader("Point Light Shadow Map Shader");
			std::shared_ptr<const RendererShaderData> pointLightShadowMapRendererShaderData = getShaderManager()->viewShaderData("Point Light Shadow Map Shader");

			
			//	Render the Shadow Maps.

			//	Create the Shadow Projection Matrix.
			GLfloat aspectRatio = 1.0f;
			GLfloat nearClip = 0.01f;
			GLfloat farClip = 1000.0f;
			glm::mat4 shadowProjectionMatrix = glm::perspective(glm::pi<float>() / 2.0f, aspectRatio, nearClip, farClip);

			//	Generate the Light View Matrices.
			glm::mat4 lightViewMatrices[6];
			lightViewMatrices[0] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
			lightViewMatrices[1] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
			lightViewMatrices[2] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
			lightViewMatrices[3] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
			lightViewMatrices[4] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
			lightViewMatrices[5] = glm::lookAt(glm::vec3(activeLights[currentLightNumber]->lightPosition), glm::vec3(activeLights[currentLightNumber]->lightPosition) + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));

			//	Render to each side of the cube face.
			for (int i = 0; i < 6; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, activeLightDatas[currentLightNumber].lightFramebufferObjects[i]);

				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

				//	Upload the Camera Data.
				uploadCameraData(*pointLightShadowMapRendererShaderData, activeLights[currentLightNumber]->lightPosition, shadowProjectionMatrix, lightViewMatrices[i], glm::vec4(nearClip, farClip, 0.0, 0.0));

				//	
				const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = renderableManager->getRenderableTypeBatchMetaDatas();

				for (auto currentRenderableType = renderableBatchTypes.begin(); currentRenderableType != renderableBatchTypes.end(); currentRenderableType++)
				{
					if (currentRenderableType->renderableTypeBatch->getIsValidRenderableType())
					{
						std::string shaderType = getRendererShaderDataForRenderableShadingType(currentRenderableType->renderableType.shaderType)->shaderType;
						auto shaderOutputOpacity = getShaderManager()->viewShaderData(shaderType)->shaderProperties.find("Shader Output Opacity");

						if (shaderOutputOpacity != getShaderManager()->viewShaderData(shaderType)->shaderProperties.end())
						{
							if (shaderOutputOpacity->second != "True")
							{
								//	Render the Renderables that use the Shader Data specified by the Renderer.
								renderRenderablesOfShaderType(currentRenderableType->renderableType.shaderType, *pointLightShadowMapRendererShaderData, activeCamera->getViewMatrix(), deltaFrameTime, currentFrameTime, lastFrameTime);

							}
						}
					}
				}
			}



			//	---------------------------------------------------------------------------------------------------------------	//

			//	Set the Blending, the Viewport and the Culling. 
			glDisable(GL_BLEND);
			glViewport(0, 0, windowScreenWidth, windowScreenHeight);
			glCullFace(GL_BACK);

			//	Set the shader for the Deferred Lighting Shadowing Rendering.
			getShaderManager()->setActiveShader("Current View Shadow Map Shader");
			std::shared_ptr<const RendererShaderData> currentViewShadowMapRendererShaderData = getShaderManager()->viewShaderData("Current View Shadow Map Shader");

			//	Upload the Camera, the G Buffer and the Light Number Data.
			uploadCameraData(*currentViewShadowMapRendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
			uploadGBufferDataTextures(*currentViewShadowMapRendererShaderData);
			uploadSingleLightsData(*currentViewShadowMapRendererShaderData, currentLightNumber);
			uploadPointLightShadowCubeMapData(*currentViewShadowMapRendererShaderData);

			//	Deferred Renderer - Second Pass - Render the Lighting Pass.
			glBindFramebuffer(GL_FRAMEBUFFER, activeLightDatas[currentLightNumber].currentViewFramebufferObject);

			//	Clear the Color and the Depth Buffer.
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			checkFramebufferStatus();

			//	Draw the Arrays.
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			//	Blur the Shadow Map.
			//	renderGaussianBlur(deltaFrameTime, currentFrameTime, lastFrameTime, activeLightDatas[currentLightNumber].currentViewLightColorMap, 8);

			//	Bind the Default Framebuffer.
			glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

			//	Renable Blending.
			glEnable(GL_BLEND);

			//	
			GLenum err2 = GL_NO_ERROR;
			while ((err2 = glGetError()) != GL_NO_ERROR)
			{
				std::cout << "OpenGL Post - Active Light Shadowing Pass Error -> " << err2 << std::endl;
			}

		}
		else
		{
			//	---------------------------------------------------------------------------------------------------------------	//
			//	Set the Culling, the Viewport and the Blending.
			glCullFace(GL_BACK);
			glViewport(0, 0, windowScreenWidth, windowScreenHeight);
			glDisable(GL_BLEND);

			//	Deferred Renderer - Second Pass - Render the Lighting Pass.
			glBindFramebuffer(GL_FRAMEBUFFER, activeLightDatas[currentLightNumber].currentViewFramebufferObject);

			//	Check the Current Framebuffer Status.
			checkFramebufferStatus();

			//	Clear the Color and the Depth Buffer.
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//	Bind the Default Framebuffer.
			glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
			//	---------------------------------------------------------------------------------------------------------------	//

		}


	}

}

//	Render the Lighting Pass for the G Buffer.
void DeferredRenderer::renderDeferredRenderingLightingPass(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTIme, std::shared_ptr<const Camera> activeCamera)
{
	//	
	GLenum err1 = GL_NO_ERROR;
	while ((err1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Pre - Deferred Lighting Pass Error -> " << err1 << std::endl;
	}

	//	Disable Blending.
	glDisable(GL_BLEND);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Deferred Rendering Lighting Pass Error -> " << err << std::endl;
	}

	getShaderManager()->setActiveShader("Basic Deferred Lighting Pass Shader");
	std::shared_ptr<const RendererShaderData> currentRendererShaderData = getShaderManager()->viewShaderData("Basic Deferred Lighting Pass Shader");


	//	Upload the Background, Camera, Lights and G Buffer Texture Data.
	uploadBackgroundEnviroment(*currentRendererShaderData);
	uploadCameraData(*currentRendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
	uploadLightsData(*currentRendererShaderData);
	uploadGBufferDataTextures(*currentRendererShaderData);
	uploadPrimaryPostProcessTextures(*currentRendererShaderData, rendererPipelineTextures["AMBIENT_OCCLUSION_COLOR_TEXTURE"]->textureID, 0, 0, 0);

	//	Bind the G Buffer Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["MSAA_RENDER_DEFERRED_LIGHTING_PASS_FRAMEBUFFER"]->framebufferID);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	//	Check the Framebuffer Status.
	checkFramebufferStatus();

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	Enable Blending.
	glEnable(GL_BLEND);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, rendererPipelineFramebuffers["RENDER_DEFERRED_LIGHTING_PASS_FRAMEBUFFER"]->framebufferID);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, rendererPipelineFramebuffers["MSAA_RENDER_DEFERRED_LIGHTING_PASS_FRAMEBUFFER"]->framebufferID);
	glBlitFramebuffer(0, 0, windowScreenWidth, windowScreenHeight, 0, 0, windowScreenWidth, windowScreenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	//	
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Deferred Lighting Pass Error -> " << err2 << std::endl;
	}

}

//	Render the Point Light Shadow Maps.
void DeferredRenderer::renderPointLightShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{

}

//	Render the Directional Light Shadow Maps.
void DeferredRenderer::renderDirectionalLightShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{


}

//	Render the Spot Light Shadow Maps.
void DeferredRenderer::renderSpotLightShadowMaps(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{


}

//	Render the Renderables that have to go through the Forward Rendering pipeline.
void DeferredRenderer::renderForwardRenderingPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Clear the Forward Rendering Buffer.

}

//	Render the Ambient Occlusion Pass.
void DeferredRenderer::renderAmbientOcclusionPass(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["SINGLE_TEXTURE_OUTPUT_POST_PROCESS_FRAMEBUFFER"]->framebufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["AMBIENT_COLOR_PASS_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["AMBIENT_DEPTH_PASS_TEXTURE"]->textureID, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Set the shader for the Point Light Shadow Map Rendering.
	getShaderManager()->setActiveShader("Ambient Color Shader");
	std::shared_ptr<const RendererShaderData> currentRendererShaderData = getShaderManager()->viewShaderData("Ambient Color Shader");

	//	Check the Framebuffer Status.
	checkFramebufferStatus();

	//	Upload the Background, Camera and Lights Data.
	uploadBackgroundEnviroment(*currentRendererShaderData);
	uploadCameraData(*currentRendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
	uploadAmbientLightData(*currentRendererShaderData);


	//	
	const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = renderableManager->getRenderableTypeBatchMetaDatas();

	for (auto currentRenderableType = renderableBatchTypes.begin(); currentRenderableType != renderableBatchTypes.end(); currentRenderableType++)
	{
		if (currentRenderableType->renderableTypeBatch->getIsValidRenderableType())
		{
			std::string shaderType = getRendererShaderDataForRenderableShadingType(currentRenderableType->renderableType.shaderType)->shaderType;
			auto shaderOutputOpacity = getShaderManager()->viewShaderData(shaderType)->shaderProperties.find("Shader Output Opacity");

			if (shaderOutputOpacity != getShaderManager()->viewShaderData(shaderType)->shaderProperties.end())
			{
				if (shaderOutputOpacity->second != "True")
				{
					//	Render the Renderables that use the Shader Data specified by the Renderer.
					renderRenderablesOfShaderType(currentRenderableType->renderableType.shaderType, *currentRendererShaderData, activeCamera->getViewMatrix(), deltaFrameTime, currentFrameTime, lastFrameTime);

				}
			}
		}
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["AMBIENT_OCCLUSION_COLOR_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["AMBIENT_OCCLUSION_DEPTH_TEXTURE"]->textureID, 0);


	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	getShaderManager()->setActiveShader("SSAO Shader");
	std::shared_ptr<const RendererShaderData> rendererShaderData = getShaderManager()->viewShaderData("SSAO Shader");

	//	Upload the Camera Data, the Noise Textures, the Sampling Data, and the Post Process Textures.
	uploadCameraData(*rendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
	uploadNoiseTextures(*rendererShaderData);
	uploadSamplingData(*rendererShaderData);

	uploadPrimaryPostProcessTextures(*rendererShaderData, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_AND_DEPTH_TEXTURE"]->textureID, 0, 0);
	uploadSecondaryPostProcessTextures(*rendererShaderData, rendererPipelineTextures["AMBIENT_COLOR_PASS_TEXTURE"]->textureID, rendererPipelineTextures["AMBIENT_DEPTH_PASS_TEXTURE"]->textureID, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
}

//	Run the Gaussian Blur on the Texture.
void DeferredRenderer::renderGaussianBlur(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, GLuint textureID, int blurAmount)
{
	std::string gb = "DBG_GB";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, 7, gb.c_str());

	std::shared_ptr<const RendererShaderData> copyTextureRendererShaderData = getShaderManager()->viewShaderData("Copy Texture Shader");
	std::shared_ptr<const RendererShaderData> gaussianBlurRendererShaderData = getShaderManager()->viewShaderData("Gaussian Blur Shader");

	//	Bind the Framebuffer for Texture Copy.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["GAUSSIAN_BLUR_FRAMEBUFFER_COPY"]->framebufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["GAUSSIAN_BLUR_TEXTURE_ONE"]->textureID, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Set the Active Shader To be the Copy Texture Shader.
	getShaderManager()->setActiveShader("Copy Texture Shader");

	//	Check the Framebuffer Status.
	checkFramebufferStatus();
	
	//	
	uploadPrimaryPostProcessTextures(*copyTextureRendererShaderData, textureID, 0, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	getShaderManager()->setActiveShader("Gaussian Blur Shader");

	bool isHorizontal = true;

	//	
	for (int i = 0; i < blurAmount; i++)
	{
		glUniform1i(glGetUniformLocation(gaussianBlurRendererShaderData->shaderID, "isBlurHorizontal"), isHorizontal);
		glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["GAUSSIAN_BLUR_FRAMEBUFFER_ONE"]->framebufferID);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		uploadPrimaryPostProcessTextures(*gaussianBlurRendererShaderData, rendererPipelineTextures["GAUSSIAN_BLUR_TEXTURE_ONE"]->textureID, 0, 0, 0);

		//	Draw the Arrays.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		isHorizontal = !isHorizontal;

		glUniform1i(glGetUniformLocation(gaussianBlurRendererShaderData->shaderID, "isBlurHorizontal"), isHorizontal);
		glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["GAUSSIAN_BLUR_FRAMEBUFFER_TWO"]->framebufferID);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		uploadPrimaryPostProcessTextures(*gaussianBlurRendererShaderData, rendererPipelineTextures["GAUSSIAN_BLUR_TEXTURE_TWO"]->textureID, 0, 0, 0);

		//	Draw the Arrays.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	//	Bind the Framebuffer for Texture Copy.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["GAUSSIAN_BLUR_FRAMEBUFFER_COPY"]->framebufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, textureID, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Set the Active Shader To be the Copy Texture Shader.
	getShaderManager()->setActiveShader("Copy Texture Shader");

	//	Check the Framebuffer Status.
	checkFramebufferStatus();

	//	
	uploadPrimaryPostProcessTextures(*copyTextureRendererShaderData, rendererPipelineTextures["GAUSSIAN_BLUR_TEXTURE_ONE"]->textureID, 0, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glPopDebugGroup();
}

//	Render the Post Process Pipeline.
void DeferredRenderer::renderPostProcessPipeline(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{

	////	------------------------------------------------------------------------------------------------------------------------------------------------------	//
	////	Render the FXAA Shader.
	//glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["SINGLE_TEXTURE_OUTPUT_POST_PROCESS_FRAMEBUFFER"]->framebufferID);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["FXAA_COLOR_TEXTURE"]->textureID, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["FXAA_DEPTH_TEXTURE"]->textureID, 0);

	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	////	
	//getShaderManager()->setActiveShader("FXAA Shader");
	//std::shared_ptr<const RendererShaderData> fxaarendererShaderData = getShaderManager()->viewShaderData("FXAA Shader");

	////	Upload the Post Process Textures.
	//uploadPrimaryPostProcessTextures(*fxaarendererShaderData, rendererPipelineTextures["DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE"]->textureID, 0, 0, 0);

	////	Draw the Arrays.
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//


	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["SINGLE_TEXTURE_OUTPUT_POST_PROCESS_FRAMEBUFFER"]->framebufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["BLOOM_EXTRACTION_COLOR_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["BLOOM_EXTRACTION_DEPTH_TEXTURE"]->textureID, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	getShaderManager()->setActiveShader("Bloom Extraction Shader");
	std::shared_ptr<const RendererShaderData> bloomRendererShaderData = getShaderManager()->viewShaderData("Bloom Extraction Shader");

	glUniform1f(glGetUniformLocation(bloomRendererShaderData->shaderID, "u_extractionValue"), 1.00);

	//	Upload the Post Process Textures.
	uploadPrimaryPostProcessTextures(*bloomRendererShaderData, rendererPipelineTextures["FXAA_COLOR_TEXTURE"]->textureID, 0, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);
	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//


	//	Gaussian Blur the place.
	//	renderGaussianBlur(deltaFrameTime, currentFrameTime, lastFrameTime, rendererPipelineTextures["BLOOM_EXTRACTION_COLOR_TEXTURE"]->textureID, 4);


	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//

	//	Render the Bloom Shader.
	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["SINGLE_TEXTURE_OUTPUT_POST_PROCESS_FRAMEBUFFER"]->framebufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, rendererPipelineTextures["BLOOM_COLOR_TEXTURE"]->textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rendererPipelineTextures["BLOOM_DEPTH_TEXTURE"]->textureID, 0);

	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	getShaderManager()->setActiveShader("Additive Blend Shader");
	std::shared_ptr<const RendererShaderData> additiveBlendRendererShader = getShaderManager()->viewShaderData("Additive Blend Shader");

	//	Upload the Camera Data, the Noise Textures, the Sampling Data, and the Post Process Textures.
	uploadPrimaryPostProcessTextures(*additiveBlendRendererShader, rendererPipelineTextures["BLOOM_EXTRACTION_COLOR_TEXTURE"]->textureID, rendererPipelineTextures["FXAA_COLOR_TEXTURE"]->textureID, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//
	//	renderGaussianBlur(deltaFrameTime, currentFrameTime, lastFrameTime, rendererPipelineTextures["DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE"]->textureID, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, rendererPipelineFramebuffers["DEFAULT_FRAMEBUFFER"]->framebufferID);

	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	getShaderManager()->setActiveShader("HDR Shader");
	std::shared_ptr<const RendererShaderData> hdrRendererShader = getShaderManager()->viewShaderData("HDR Shader");

	//	Upload the Camera Data, the Noise Textures, the Sampling Data, and the Post Process Textures.
	uploadPrimaryPostProcessTextures(*hdrRendererShader, rendererPipelineTextures["DEFERRED_RENDERING_LIGHTING_PASS_COLOR_TEXTURE"]->textureID, 0, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	------------------------------------------------------------------------------------------------------------------------------------------------------	//

	//	
	GLenum cerr = GL_NO_ERROR;
	while ((cerr = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post Process Error -> " << cerr << std::endl;
	}
}

//	Render the Renderables of the Shader Type.
void DeferredRenderer::renderRenderablesOfShaderType(const std::string & shaderType, const RendererShaderData & rendererShaderData, const glm::mat4 & currentViewMatrix, const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	
	std::string PROFILE_RENDER_RENDERABLES_OF_SHADER_TYPE = "PROFILE_RRST";
	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, 12, PROFILE_RENDER_RENDERABLES_OF_SHADER_TYPE.c_str());

	//	Get the Current Shader Program.
	GLuint currentShaderProgramID = rendererShaderData.shaderID;

	//	Get the Required Geometry Description for the Shader Type.
	int currentShaderTypeRequirements = getShaderManager()->getGeometryVertexRequirementsForShader(rendererShaderData.shaderType);

	//	Get the Renderable Batch Types.
	const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = renderableManager->getRenderableTypeBatchMetaDatas();

	unsigned int currentVAO = 0;
	glBindVertexArray(currentVAO);

	//	
	for (auto currentRenderableTypeBatch = renderableBatchTypes.begin(); currentRenderableTypeBatch != renderableBatchTypes.end(); currentRenderableTypeBatch++)
	{
		if (currentRenderableTypeBatch->renderableTypeBatch->getIsValidRenderableType())
		{
			if (currentRenderableTypeBatch->renderableType.shaderType == shaderType)
			{
				currentVAO = currentRenderableTypeBatch->geometryTypeMetaData->vaoMetaData.lock()->vaoID;
				
				if (currentVAO != 0)
				{
					glBindVertexArray(currentVAO);

					//	All of this should be replaced with a single glBindVertexArray.
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentRenderableTypeBatch->geometryTypeMetaData->EBO);

					//	Get the Current Material Data.
					std::shared_ptr<const std::pair<RendererMaterialValues, RendererMaterialMaps>> currentMaterialData = getMaterialManager()->viewMaterial(currentRenderableTypeBatch->renderableType.materialType);

					//	Upload the Shader Material Data.
					uploadMaterialData(rendererShaderData, currentMaterialData->first.diffuseAlbedo, currentMaterialData->first.specularAlbedo, currentMaterialData->first.emissiveColor, currentMaterialData->first.metallicRoughnessFresnelOpacity);

					//	Upload the Shader Material Texture Data.
					uploadMaterialTextureData(rendererShaderData, currentMaterialData->second.DiffuseAlbedoMap, currentMaterialData->second.SpecularAlbedoMap, currentMaterialData->second.MRFOMap, currentMaterialData->second.NormalMap, currentMaterialData->second.OcclusionMap);
					
					//	
					for (int i = 0; i < currentRenderableTypeBatch->renderableTypeBatch->getTransformMatrices().size(); i++)
					{
						//	Update the Transform Matrix.
						uploadModelData(rendererShaderData, currentViewMatrix, currentRenderableTypeBatch->renderableTypeBatch->getTransformMatrices()[i]);

						//	Draw the Elements.
						glDrawElements(currentRenderableTypeBatch->geometryTypeMetaData->rendererGeometryData->geometryDrawType, currentRenderableTypeBatch->geometryTypeMetaData->rendererGeometryData->indicesArray.size(), GL_UNSIGNED_INT, 0);
					}
				}
			}
		}
	}

	glBindVertexArray(0);

	glPopDebugGroup();
}

//	Return the RendererShaderData for the Shading Type.
std::shared_ptr<const RendererShaderData> DeferredRenderer::getRendererShaderDataForRenderableShadingType(const std::string & shaderType)
{
	//	RETURN THE OPAQUE SHADER DATA. 
	if (shaderType == "OPAQUE_BASIC")
	{
		return getShaderManager()->viewShaderData("Basic Deferred G Buffer Shader");
	}

	return NULL;
}

//	Remove the Renderable.
void DeferredRenderer::removeRenderable(const long int & renderableID)
{
	renderableManager->removeRenderable(renderableID);
}

//	Clean Up the Renderer.
void DeferredRenderer::cleanUpRenderer()
{

	//	Delete the Textures of the G Buffer.
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_AND_DEPTH_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_DIFFUSE_ALBEDO_AND_LIT_TYPE_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_SPECULAR_ALBEDO_AND_LIGHTING_TYPE_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_EMISSIVE_COLOR_INTENSITIY_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE"]->textureID);
	glDeleteTextures(1, &rendererPipelineTextures["G_BUFFER_DEPTH_STENCIL_TEXTURE"]->textureID);


	//	Delete the Noise Textures.
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureOneID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureTwoID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureThreeID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureFourID);


	//	Delete the Point Light Depth Cube Maps.
	glDeleteTextures(1, &pointLightDepthCubeMaps.lightColorCubeMap);
	glDeleteTextures(1, &pointLightDepthCubeMaps.lightDepthCubeMap);


	//	Iterate over the Lights.
	for (int currentLightNumber = 0; currentLightNumber < activeLightNames.size(); currentLightNumber++)
	{
		glDeleteTextures(1, &activeLightDatas[currentLightNumber].currentViewLightColorMap);
		glDeleteTextures(1, &activeLightDatas[currentLightNumber].currentViewLightDepthMap);
	}

}

//	Add the Material to the Renderer for use, under the Material Name.
void DeferredRenderer::addMaterial(std::string newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::addMaterial(newMaterialName, newMaterialData);
	renderableManager->addMaterialType(newMaterialName);
}

//	Update the Material in the Renderer, specified by the Material Name.
void DeferredRenderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	Renderer::updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void DeferredRenderer::deleteMaterial(std::string deadMaterialName)
{
	renderableManager->removeMaterialType(deadMaterialName);
	Renderer::deleteMaterial(deadMaterialName);
}

//	Add the Geometry to the Renderer for use, under the Geometry Name.
void DeferredRenderer::addGeometry(std::string newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::addGeometry(newGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Adding Geometry Data Error -> " << err << std::endl;
	}

	renderableManager->addGeometryType(getGeometryManager()->getGeometry(newGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Adding Geometry Data Error -> " << err2 << std::endl;
	}

}

//	Update the Geometry in the Renderer, specified by the Geometry Name.
void DeferredRenderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	Renderer::updateGeometry(currentGeometryName, newGeometryData);

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Updating Geometry Data Error -> " << err << std::endl;
	}


	renderableManager->updateGeometryType(getGeometryManager()->getGeometry(currentGeometryName));

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Updating Geometry Data Error -> " << err2 << std::endl;
	}

}

//	Delete the Geometry.
void DeferredRenderer::deleteGeometry(std::string deadGeometryName)
{
	renderableManager->removeGeometryType(getGeometryManager()->getGeometry(deadGeometryName));

	//	Check for Errors.
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Backend Deleting Geometry Data Error -> " << err << std::endl;
	}


	Renderer::deleteGeometry(deadGeometryName);

	//	Check for Errors.
	GLenum err2 = GL_NO_ERROR;
	while ((err2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Post - Renderer Deleting Geometry Data Error -> " << err2 << std::endl;
	}

}

//	Add Shader to the Renderer.
void DeferredRenderer::addShader(std::shared_ptr<const ShaderData> newShaderData)
{
	Renderer::addShader(newShaderData);
	std::string shaderType;
	newShaderData->findProperty("Shader Name", shaderType);
	renderableManager->addShaderType("OPAQUE_BASIC");

}

//	Delete the Shader in the Renderer.
void DeferredRenderer::deleteShader(std::string deadShaderName)
{
	renderableManager->removeShaderType(getShaderManager()->viewShaderData(deadShaderName)->shaderType);
	Renderer::deleteShader(deadShaderName);
}

//	Add the Light to the Renderer, under the name.
void DeferredRenderer::addLight(std::string newLightName, std::shared_ptr<const LightData> newLightData)
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
void DeferredRenderer::updateLight(std::string currentLightName, std::shared_ptr<const LightData> newLightData)
{
	Renderer::updateLight(currentLightName, newLightData);
}

//	Delete the Light.
void DeferredRenderer::deleteLight(std::string deadLightName)
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
void DeferredRenderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::addTexture(newTextureName, newTextureData);
}

//	Update the Texture in the Renderer, specified by name.
void DeferredRenderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	Renderer::updateTexture(currentTextureName, newTextureData);
}

//	Delete the Texture in the Renderer.
void DeferredRenderer::deleteTexture(std::string deadTextureName)
{
	Renderer::deleteTexture(deadTextureName);
}

//	Bind the Environment Maps.
void DeferredRenderer::uploadBackgroundEnviroment(const RendererShaderData & rendererShaderData)
{
	//	-------------------------------------------------------------------------------------------------------------------------------------------	//

	if (rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentIntensities != (GLfloat)-1)
	{
		glUniform4fv(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentIntensities, 1, glm::value_ptr(backgroundEnvironmentData.backgroundEnvironmentCubeMapsIntensities));
	}

	//	The Active Texture 0.
	std::shared_ptr<const RendererTextureData> textureDataOne = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[0] != "NONE" && rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapOne != (GLfloat)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(textureDataOne->textureType, textureDataOne->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapOne, 0);
		glActiveTexture(GL_TEXTURE0);

	}

	//	The Active Texture 1.
	std::shared_ptr<const RendererTextureData> textureDataTwo = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[1] != "NONE" && rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapTwo != (GLfloat)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(textureDataTwo->textureType, textureDataTwo->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapTwo, 1);
		glActiveTexture(GL_TEXTURE0);
	}

	//	The Active Texture 2.
	std::shared_ptr<const RendererTextureData> textureDataThree = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[2] != "NONE" && rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapThree != (GLfloat)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(textureDataThree->textureType, textureDataThree->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapThree, 2);
		glActiveTexture(GL_TEXTURE0);
	}

	//	The Active Texture 3.
	std::shared_ptr<const RendererTextureData> textureDataFour = getTextureManager()->viewTexture(backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3]);
	if (backgroundEnvironmentData.backgroundEnvironmentCubeMaps[3] != "NONE" && rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapFour != (GLfloat)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(textureDataFour->textureType, textureDataFour->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.environmentDataUniforms.u_backgroundEnvironmentCubeMapFour, 3);
		glActiveTexture(GL_TEXTURE0);
	}

	//	-------------------------------------------------------------------------------------------------------------------------------------------	//
}

//	Upload the Camera Data to the Shader Pipeline.
void DeferredRenderer::uploadCameraData(const RendererShaderData & rendererShaderData, const glm::vec4 & worldCameraPosition, const glm::mat4 & perspectiveMatrix, const glm::mat4 & viewMatrix, const glm::vec4 & cameraNearFarPlaneDistance)
{
	//	Upload the Camera Position.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_worldCameraPosition, 1, glm::value_ptr(worldCameraPosition));

	//	Upload the Camera Perspective Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

	//	Upload the Camera View Matrix.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//	Upload the Camera View Matrix without Translation.
	glUniformMatrix4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_screenSpaceViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));

	//	Upload the Camera Near and Far Distance.
	glUniform4fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_cameraNearFarPlaneDistance, 1, glm::value_ptr(cameraNearFarPlaneDistance));

	//	
	glUniformMatrix3fv(rendererShaderData.shaderUniforms.cameraDataUniforms.u_inverseTransposeCameraViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(viewMatrix))));
}

//	Upload the Model Data to the Shader Pipeline.
void DeferredRenderer::uploadModelData(const RendererShaderData & rendererShaderData, const glm::mat4 & viewMatrix, const glm::mat4 & modelMatrix)
{
	//	Upload the Model Matrix.
	if (rendererShaderData.shaderUniforms.modelDataUniforms.u_modelMatrix != (GLuint)-1)
		glUniformMatrix4fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//	Upload the Inverse Transpose Model Matrix.
	if (rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelMatrix != (GLuint)-1)
		glUniformMatrix3fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(modelMatrix))));

	//	Upload the ModelView Matrix.
	if (rendererShaderData.shaderUniforms.modelDataUniforms.u_modelViewMatrix != (GLuint)-1)
		glUniformMatrix4fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_modelViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix * modelMatrix));

	//	Upload the Inverse Transpose Model View Matrix.
	if (rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelViewMatrix != (GLuint)-1)
		glUniformMatrix3fv(rendererShaderData.shaderUniforms.modelDataUniforms.u_inverseTransposeModelViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(viewMatrix * modelMatrix))));
}

//	Upload the Material Data to the Shader Pipeline.
void DeferredRenderer::uploadMaterialData(const RendererShaderData & rendererShaderData, const glm::vec4 & diffuseAlbedo, const glm::vec4 & specularAlbedo, const glm::vec4 & emissiveColor, const glm::vec4 & metallicnessRoughnessFresnelOpacity)
{

	//	
	GLenum cerr1 = GL_NO_ERROR;
	while ((cerr1 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error 1 -> " << cerr1 << std::endl;
	}

	//	Upload the Diffuse Albedo.
	if (rendererShaderData.shaderUniforms.materialValuesUniforms.u_diffuseAlbedoAndLitType != (GLuint)-1)
		glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_diffuseAlbedoAndLitType, 1, glm::value_ptr(diffuseAlbedo));

	//	
	GLenum cerr2 = GL_NO_ERROR;
	while ((cerr2 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error 2 -> " << cerr2 << std::endl;
	}


	//	Upload the Specular Albedo.
	if (rendererShaderData.shaderUniforms.materialValuesUniforms.u_specularAlbedoAndLightingType != (GLuint)-1)
		glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_specularAlbedoAndLightingType, 1, glm::value_ptr(specularAlbedo));

	//	
	GLenum cerr3 = GL_NO_ERROR;
	while ((cerr3 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error 3 -> " << cerr3 << std::endl;
	}

	//	Upload the Emissive Color And Intensity.
	if (rendererShaderData.shaderUniforms.materialValuesUniforms.u_emssionColorAndIntensity != (GLuint)-1)
		glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_emssionColorAndIntensity, 1, glm::value_ptr(emissiveColor));

	//	
	GLenum cerr4 = GL_NO_ERROR;
	while ((cerr4 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error 4 -> " << cerr4 << std::endl;
	}

	//	Upload the Material Properties.
	if (rendererShaderData.shaderUniforms.materialValuesUniforms.u_metallicnessRoughnessFresnelOpacity != (GLuint)-1)
		glUniform4fv(rendererShaderData.shaderUniforms.materialValuesUniforms.u_metallicnessRoughnessFresnelOpacity, 1, glm::value_ptr(metallicnessRoughnessFresnelOpacity));

	//	
	GLenum cerr5 = GL_NO_ERROR;
	while ((cerr5 = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Shadowing Pass Error 5 -> " << cerr5 << std::endl;
	}

}

//	Update the Material Texture Data.
void DeferredRenderer::uploadMaterialTextureData(const RendererShaderData & rendererShaderData, const std::string & diffuseAlbedoMap, const std::string & specularAlbedoMap, const std::string & MRFOMap, const std::string & NormalMap, const std::string & OcclusionMap)
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

//	Upload the Ambient Light Data.
void DeferredRenderer::uploadAmbientLightData(const RendererShaderData & rendererShaderData)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;
	GLuint currentLightAttributeLocation = -1;
	glUniform4fv(rendererShaderData.shaderUniforms.lightDataUniforms.u_ambientLight, 1, glm::value_ptr(glm::vec4(0.025, 0.025, 0.025, 1.0)));
}

//	Upload the Shader Lights Data to the Shader Pipeline.
void DeferredRenderer::uploadLightsData(const RendererShaderData & rendererShaderData)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;
	GLuint currentLightAttributeLocation = -1;
	//	Iterate over the active lights.
	for (int lightNumber = 0; lightNumber < activeLightNames.size(); lightNumber++)
	{
		if (activeLightNames[lightNumber] != "NONE") // && lightNumber == 0)
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

				//	CurrentLight - Position
				currentLightAttribute = "lightPosition";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightPosition));

				//	CurrentLight - Color
				currentLightAttribute = "lightColorAndLightIntensity";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightColorAndLightIntensity));

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

				//	Bind the appropriate Texture Unit. Upload the Light Color Map.
				glActiveTexture(GL_TEXTURE0 + (45 + (lightNumber * 2)));
				glBindTexture(GL_TEXTURE_2D, activeLightDatas[lightNumber].currentViewLightColorMap);

				currentLightAttribute = "mainLightColorMap";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				if (currentLightAttributeLocation != (GLfloat)-1)
				{
					glUniform1i(currentLightAttributeLocation, 45 + (lightNumber * 2));
				}

				//	Bind the appropriate Texture Unit. Upload the Light Depth Map.
				glActiveTexture(GL_TEXTURE0 + (46 + (lightNumber * 2)));
				glBindTexture(GL_TEXTURE_2D, activeLightDatas[lightNumber].currentViewLightDepthMap);

				currentLightAttribute = "mainLightDepthMap";
				currentLightAttributeLocation = -1;
				currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (lightPrefix + "[" + std::to_string(lightNumber) + "]" + "." + currentLightAttribute).c_str());
				if (currentLightAttributeLocation != (GLfloat)-1)
				{
					glUniform1i(currentLightAttributeLocation, 46 + (lightNumber * 2));
				}

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

//	Upload the Data of a Single Light to the RendererShaderData.
void DeferredRenderer::uploadSingleLightsData(const RendererShaderData & rendererShaderData, const int & lightNumber)
{
	//	Renderer Shader Data.
	GLuint currentShaderProgramID = rendererShaderData.shaderID;
	GLuint currentLightAttributeLocation = -1;
	glUniform4fv(rendererShaderData.shaderUniforms.lightDataUniforms.u_ambientLight, 1, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));

	if (activeLightNames[lightNumber] != "NONE")
	{
		//	Get the current Renderer Light Data of the specified Light.
		std::shared_ptr<const RendererLightData> lightData = activeLights[lightNumber];

		//	Current Light Attribute.
		std::string currentLightAttribute = "";
		GLuint currentLightAttributeLocation = -1;

		//	
		currentLightAttribute = "lightEnabledShadowLightType";
		currentLightAttributeLocation = -1;
		currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
		glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightEnabledShadowLightType));

		//	If the Current Light is not enabled, do not bother uploading all the other stuff.
		if (lightData->lightEnabledShadowLightType[0] == 1.0)
		{

			//	CurrentLight - Position
			currentLightAttribute = "lightPosition";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightPosition));

			//	CurrentLight - Color
			currentLightAttribute = "lightColorAndLightIntensity";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightColorAndLightIntensity));

			//	CurrentLight -	Attenuation
			currentLightAttribute = "lightConeDirection";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->lightConeDirection));

			//	CurrentLight -	spotCosCutOffAndExponent
			currentLightAttribute = "lightSpotCosCutOffAndExponent";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(lightData->spotCosCutOffAndExponent));

			//	Bind the appropriate Texture Unit. Upload the Light Color Map.
			glActiveTexture(GL_TEXTURE0 + (45 + (lightNumber * 2)));
			glBindTexture(GL_TEXTURE_2D, activeLightDatas[lightNumber].currentViewLightColorMap);

			currentLightAttribute = "mainLightColorMap";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			if (currentLightAttributeLocation != (GLfloat)-1)
			{
				glUniform1i(currentLightAttributeLocation, 45 + (lightNumber * 2));
			}

			//	Bind the appropriate Texture Unit. Upload the Light Depth Map.
			glActiveTexture(GL_TEXTURE0 + (46 + (lightNumber * 2)));
			glBindTexture(GL_TEXTURE_2D, activeLightDatas[lightNumber].currentViewLightDepthMap);

			currentLightAttribute = "mainLightDepthMap";
			currentLightAttributeLocation = -1;
			currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
			if (currentLightAttributeLocation != (GLfloat)-1)
			{
				glUniform1i(currentLightAttributeLocation, 46 + (lightNumber * 2));
			}
		}
	}
	else
	{
		//	
		std::string currentLightAttribute = "";
		GLuint currentLightAttributeLocation = -1;

		//	Upload whether the Light has been Enabled, the Shadow type and the Light Type.
		currentLightAttribute = "lightEnabledShadowLightType";
		currentLightAttributeLocation = -1;
		currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
		glUniform4fv(currentLightAttributeLocation, 1, glm::value_ptr(glm::vec4(0.0)));
	}
}

//	Upload the Point Light Shadow Cube Map Data.
void DeferredRenderer::uploadPointLightShadowCubeMapData(const RendererShaderData & rendererShaderData)
{
	GLuint currentShaderProgramID = rendererShaderData.shaderID;

	//	Current Light Attribute.
	std::string currentLightAttribute = "";
	GLuint currentLightAttributeLocation = -1;

	//	Bind the appropriate Texture Unit. Upload the Light Color Map.
	glActiveTexture(GL_TEXTURE0 + 45);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightColorCubeMap);

	currentLightAttribute = "lightColorCubeMap";
	currentLightAttributeLocation = -1;
	currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
	if (currentLightAttributeLocation != (GLint)-1)
	{
		glUniform1i(currentLightAttributeLocation, 45);
	}

	//	
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL Active Shadowing Pass Error -> " << err << std::endl;
	}

	//	Bind the appropriate Texture Unit. Upload the Light Depth Map.
	glActiveTexture(GL_TEXTURE0 + 46);
	glBindTexture(GL_TEXTURE_CUBE_MAP, pointLightDepthCubeMaps.lightDepthCubeMap);

	currentLightAttribute = "lightDepthCubeMap";
	currentLightAttributeLocation = -1;
	currentLightAttributeLocation = glGetUniformLocation(currentShaderProgramID, (currentLightAttribute).c_str());
	if (currentLightAttributeLocation != (GLint)-1)
	{
		glUniform1i(currentLightAttributeLocation, 46);
	}
}

//	Upload the Sampling Data.
void DeferredRenderer::uploadSamplingData(const RendererShaderData & rendererShaderData)
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
void DeferredRenderer::uploadNoiseTextures(const RendererShaderData & rendererShaderData)
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
void DeferredRenderer::uploadGBufferDataTextures(const RendererShaderData & rendererShaderData)
{

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexPosition != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 20);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_POSITION_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexPosition, 20);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexNormalAndDepth != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 21);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_WORLD_SPACE_VERTEX_NORMAL_AND_DEPTH_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_worldSpaceVertexNormalAndDepth, 21);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_diffuseAlbedoAndLitType != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 22);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_DIFFUSE_ALBEDO_AND_LIT_TYPE_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_diffuseAlbedoAndLitType, 22);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_specularAlbedoAndLightingType != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 23);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_SPECULAR_ALBEDO_AND_LIGHTING_TYPE_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_specularAlbedoAndLightingType, 23);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_emissionColorAndIntensity != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 24);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_EMISSIVE_COLOR_INTENSITIY_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_emissionColorAndIntensity, 24);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.gBufferInputUniforms.g_metallicnessRoughnessFresnelOpacity != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 25);
		glBindTexture(GL_TEXTURE_2D, rendererPipelineTextures["G_BUFFER_METALLICNESS_ROUGHNESS_FRESNEL_OPACITY_TEXTURE"]->textureID);
		glUniform1i(rendererShaderData.shaderUniforms.gBufferInputUniforms.g_metallicnessRoughnessFresnelOpacity, 25);
		//	Reset to the default active texture.
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Upload the Post Process Textures.
void DeferredRenderer::uploadPrimaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureOneID, GLuint postProcessTextureTwoID, GLuint postProcessTextureThreeID, GLuint postProcessTextureFourID)
{
	if (rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureOne != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 35);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureOneID);
		glUniform1i(rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureOne, 35);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureTwo != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 36);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureTwoID);
		glUniform1i(rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureTwo, 36);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureThree != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 37);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureThreeID);
		glUniform1i(rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureThree, 37);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureFour != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 38);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureFourID);
		glUniform1i(rendererShaderData.shaderUniforms.primaryPostProcessInputUniforms.pp_inputTextureFour, 38);
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Upload the Post Process Textures.
void DeferredRenderer::uploadSecondaryPostProcessTextures(const RendererShaderData & rendererShaderData, GLuint postProcessTextureFiveID, GLuint postProcessTextureSixID, GLuint postProcessTextureSevenID, GLuint postProcessTextureEightID)
{
	if (rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureFive != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 39);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureFiveID);
		glUniform1i(rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureFive, 39);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureSix != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 40);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureSixID);
		glUniform1i(rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureSix, 40);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureSeven != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 41);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureSevenID);
		glUniform1i(rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureSeven, 41);
		glActiveTexture(GL_TEXTURE0);
	}

	if (rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureEight != (GLuint)-1)
	{
		glActiveTexture(GL_TEXTURE0 + 42);
		glBindTexture(GL_TEXTURE_2D, postProcessTextureEightID);
		glUniform1i(rendererShaderData.shaderUniforms.secondaryPostProcessInputUniforms.pp_inputTextureEight, 42);
		glActiveTexture(GL_TEXTURE0);
	}
}

//	Check the Framebuffer Status.
void DeferredRenderer::checkFramebufferStatus()
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
void DeferredRenderer::destroyBackgroundEnvironment()
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
void DeferredRenderer::destroyNoiseTextures()
{
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureOneID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureTwoID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureThreeID);
	glDeleteTextures(1, &rendererNoiseTextures.noiseTextureFourID);
}

