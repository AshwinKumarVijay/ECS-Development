#include "ShadowsModule.h"


//	Default ShadowsModule Constructor.
ShadowsModule::ShadowsModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const LightsModule> newLightsModule) : RendererModule(newModuleRenderer)
{
	lightsModule = newLightsModule;
}

//	Default ShadowsModule Destructor.
ShadowsModule::~ShadowsModule()
{

}

void ShadowsModule::renderShadowsModule()
{
}
