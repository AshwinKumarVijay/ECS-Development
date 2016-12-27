#pragma once
#include <memory>
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

private:

	//	
	std::weak_ptr<const LightsModule> lightsModule;

};

