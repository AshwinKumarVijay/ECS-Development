#pragma once
#include <memory>
#include <array>
#include "../RendererModule.h"

class Renderer;
class LightsModule;

class ShadowsModule : public RendererModule
{

public:

	//	Default ShadowsModule Constructor.
	ShadowsModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const LightsModule> newLightsModule);

	//	Default ShadowsModule Destructor.
	virtual ~ShadowsModule();

	//	Render the Shadows to the Shadow Maps.
	virtual void renderShadowsModule();

private:

	//	
	std::weak_ptr<const LightsModule> lightsModule;

	//	Data for Rendering Shadows from a Point Light.	
	unsigned int pointLightCubeColorTexture;
	unsigned int pointLightCubeDepthTexture;
	std::array<unsigned int, 6> pointLightFramebufferObjects;

	//	Data for Rendering Shadows from a Directional Light.
	unsigned int directionalLightColorTexture;
	unsigned int directionalLightDepthTexture;
	unsigned int directionalLightFramebufferObject;


	//	Data for Rendering Shadows from a Spot Light
	unsigned int spotLightColorTexture;
	unsigned int spotLightDepthTexture;
	unsigned int spotLightFramebufferObject;
};

