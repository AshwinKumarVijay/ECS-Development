#include "RendererModule.h"


//	Default RendererModule Constructor.
RendererModule::RendererModule(std::shared_ptr<Renderer> newModuleRenderer)
{

}

//	Default RendererModule Destructor.
RendererModule::~RendererModule()
{

}

//	Return the weak_ptr to the Module Renderer.
std::weak_ptr<ModuleRenderer> RendererModule::getModuleRenderer()
{
	return moduleRenderer;
}
