#pragma once
#include "../RendererModule.h"

class ModuleRenderer;
class RendererShaderManager;

class GaussianBlurRendererModule : public RendererModule
{

public:

	//	Default Gaussian Blur Renderer Module Constructor, with the provided input and output textures.
	GaussianBlurRendererModule(std::shared_ptr<Renderer> newModuleRenderer, const unsigned int & newBlurPassCount, const unsigned int & newInputTexture, const unsigned int & newOutputTexture, const unsigned int & newTextureWidth, const unsigned int & newTextureHeight);

	//	Default Gaussian Blur Renderer Module Destructor.
	~GaussianBlurRendererModule();

	//	Render the Gaussian Blur.
	virtual void renderGaussianBlurModule();

	//	
	

private:

	//	Create the Gaussian Blur Textures.
	void createGaussianBlurTextures();

	//	Create the Gaussian Blur Framebuffers.
	void createGaussianBlurFramebuffers();

	//	Upload the Gaussian Blur Textures.
	void uploadGaussianBlurTextures(const GLuint & colorTexture, const GLuint & depthTexture);

	//	Upload the Copy Textures.
	void uploadCopyTexture(const GLuint & colorTexture, const GLuint & depthTexture);

	//	The Renderer Shader Manager.
	std::weak_ptr<const RendererShaderManager> rendererShaderManager;


	//	The Blur Pass Count.
	unsigned int blurPassCount;

	//	The Width and Height of the Input Texture.
	unsigned int textureWidth;
	unsigned int textureHeight;


	//	Input and Output Framebuffer ID.
	unsigned int inputFramebufferID;
	unsigned int outputFramebufferID;

	//	The Gaussian Blur Framebuffer IDs.
	unsigned int vbFramebufferID;
	unsigned int hbFramebufferID;


	//	Input Textures for Copying in.
	unsigned int inputTextureID;
	unsigned int inputDepthTexture;

	//	Output Textures for Copying Out.
	unsigned int outputTextureID;
	unsigned int outputDepthTexture;

	//	Color Texture and Depth Texture One.	
	unsigned int colorTextureOne;
	unsigned int depthTextureOne;

	//	Color Texture and Depth Texture Two.
	unsigned int colorTextureTwo;
	unsigned int depthTextureTwo;

	//	The Copy Texture Program ID, and the Texture Input Location.
	unsigned int copyTextureProgramID;
	unsigned int copyTextureProgramTextureInputLocation;

	//	The Copy Texture Program ID, and the Texture Input Location.
	unsigned int gaussianBlurProgramID;
	unsigned int gaussianBlurProgramColorTextureLocation;
	unsigned int gaussianBlurProgramDepthTextureLocation;

};

