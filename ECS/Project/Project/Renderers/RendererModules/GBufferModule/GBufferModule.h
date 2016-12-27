#pragma once
#include <memory>
#include "../RendererModule.h"

class RenderableManager;
class Renderer;
class ModuleRenderer;
struct SceneQuality;

class GBufferModule : public RendererModule
{

public:

	//	Default GBufferModule Constructor.
	GBufferModule(std::shared_ptr<Renderer> newModuleRenderer);

	//	Default GBufferModule Destructor.
	virtual ~GBufferModule();

	//	Render to the GBuffer.
	virtual void renderToGBuffer();

	//	TO DO - Add Comments.
	unsigned int viewWorldSpacePositionTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewWorldSpaceVertexNormalAndDepthTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewAmbientColorTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewDiffuseAlbedoAndLitTypeTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewSpecularAlbedoAndLightingTypeTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewMRFOTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewEmissiveColorAndIntensityTexture() const;

	//	TO DO - Add Comments.
	unsigned int viewDepthTexture() const;

private:

	//	Create the G Buffer Textures and Framebuffers.
	virtual void createGBufferTexturesAndFramebuffers(const unsigned int & screenWidth, const unsigned int & screenHeight);

	//	World Space Vertex Position Texture.
	unsigned int worldSpaceVertexPositionTexture;

	//	World Space Vertex Normal and Depth Texture.
	unsigned int worldSpaceVertexNormalAndDepthTexture;

	//	Ambient Color Texture.
	unsigned int ambientColorTexture;

	//	Diffuse Albedo and Lit Type Texture.
	unsigned int diffuseAlbedoAndLitTypeTexture;

	//	Specular Albedo and Lighting Type Texture.
	unsigned int specularAlbedoAndLightingTypeTexture;

	//	Metallicness, Roughness, Fresnel, Opacity Texture
	unsigned int mrfoTexture;

	//	Emissive Color and Intensity Texture.
	unsigned int emissiveColorAndIntensityTexture;

	//	Depth Texture.
	unsigned int depthTexture;

	//	Render to G Buffer Framebuffer ID.
	unsigned int framebufferID;
};

