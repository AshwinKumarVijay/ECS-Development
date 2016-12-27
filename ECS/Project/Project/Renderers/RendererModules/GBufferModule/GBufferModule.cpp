#include "GBufferModule.h"
#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"
#include "../../RenderableManager/RenderableManager.h"
#include "../../Renderer/SceneMetaData.h"

//	Default GBufferModule Constructor.
GBufferModule::GBufferModule(std::shared_ptr<Renderer> newModuleRenderer) : RendererModule(newModuleRenderer)
{
	createGBufferTexturesAndFramebuffers(1920, 1080);
}

//	Default GBufferModule Destructor.
GBufferModule::~GBufferModule()
{

}

//	Render to the G Buffer Textures.
void GBufferModule::renderToGBuffer()
{
	//	Bind the G-Buffer Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	
	//	Render all the objects having a Material with no Transparency.


	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//	Return the World Space Position Texture.
unsigned int GBufferModule::viewWorldSpacePositionTexture() const
{
	return worldSpaceVertexPositionTexture;
}

//	Return the World Space Vertex Normal and Depth Texture.
unsigned int GBufferModule::viewWorldSpaceVertexNormalAndDepthTexture() const
{
	return worldSpaceVertexNormalAndDepthTexture;
}

//	Return the Ambient Color Texture.
unsigned int GBufferModule::viewAmbientColorTexture() const
{
	return ambientColorTexture;
}

//	Return the Diffuse Albedo and Lit Type Texture.
unsigned int GBufferModule::viewDiffuseAlbedoAndLitTypeTexture() const
{
	return diffuseAlbedoAndLitTypeTexture;
}

//	Return the Specular Albedo and Lighting Type Texture.
unsigned int GBufferModule::viewSpecularAlbedoAndLightingTypeTexture() const
{
	return specularAlbedoAndLightingTypeTexture;
}

//	Return the MRFO Texture.
unsigned int GBufferModule::viewMRFOTexture() const
{
	return mrfoTexture;
}

//	Return the Emssive Color and Intensity Texture.
unsigned int GBufferModule::viewEmissiveColorAndIntensityTexture() const
{
	return emissiveColorAndIntensityTexture;
}

//	Return the Depth Texture.
unsigned int GBufferModule::viewDepthTexture() const
{
	return depthTexture;
}

//	Create the G Buffer Textures and Framebuffers.
void GBufferModule::createGBufferTexturesAndFramebuffers(const unsigned int & screenWidth, const unsigned int & screenHeight)
{
	//	Generate the World Space Vertex Position Textures.
	glGenTextures(1, &worldSpaceVertexPositionTexture);
	glBindTexture(GL_TEXTURE_2D, worldSpaceVertexPositionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the World space Vertex Normal and Depth Texture.
	glGenTextures(1, &worldSpaceVertexNormalAndDepthTexture);
	glBindTexture(GL_TEXTURE_2D, worldSpaceVertexNormalAndDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Ambient Color Texture.
	glGenTextures(1, &ambientColorTexture);
	glBindTexture(GL_TEXTURE_2D, ambientColorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Diffuse Albedo and Lit Type Texture.
	glGenTextures(1, &diffuseAlbedoAndLitTypeTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseAlbedoAndLitTypeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Specular Albedo and Lighting Type Texture.
	glGenTextures(1, &specularAlbedoAndLightingTypeTexture);
	glBindTexture(GL_TEXTURE_2D, specularAlbedoAndLightingTypeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Specular Albedo and Lighting Type Texture.
	glGenTextures(1, &mrfoTexture);
	glBindTexture(GL_TEXTURE_2D, mrfoTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Emssive Color and Intensity Texture.
	glGenTextures(1, &emissiveColorAndIntensityTexture);
	glBindTexture(GL_TEXTURE_2D, emissiveColorAndIntensityTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Depth Texture.
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);


	//	Create the Framebuffer to Render to the G Buffer.
	glGenFramebuffers(1, &framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	//	Associate the Textures of the G Buffer with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, worldSpaceVertexPositionTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, worldSpaceVertexNormalAndDepthTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, ambientColorTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 3, GL_TEXTURE_2D, diffuseAlbedoAndLitTypeTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 4, GL_TEXTURE_2D, specularAlbedoAndLightingTypeTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 5, GL_TEXTURE_2D, mrfoTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 6, GL_TEXTURE_2D, emissiveColorAndIntensityTexture, 0);

	//	Associate the Depth Stencil Texture with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	//	Set up the G Buffer Draw Textures.
	GLenum framebufferDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0, GL_COLOR_ATTACHMENT0 + 1, GL_COLOR_ATTACHMENT0 + 2, GL_COLOR_ATTACHMENT0 + 3, GL_COLOR_ATTACHMENT0 + 4, GL_COLOR_ATTACHMENT0 + 5, GL_COLOR_ATTACHMENT0 + 6};
	glDrawBuffers(7, framebufferDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
