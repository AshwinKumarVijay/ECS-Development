#pragma once
#include <vector>
#include <memory>
#include "GL\glew.h"

class Renderer;
class ModuleRenderer;

//
class RendererModule
{

public:
	
	//	Default RendererModule Constructor.
	RendererModule(std::shared_ptr<Renderer> newModuleRenderer);

	//	Default RendererModule Destructor.
	virtual ~RendererModule();

	//	Return the weak_ptr to the Module Renderer.
	virtual std::weak_ptr<ModuleRenderer> getModuleRenderer();

private:
	std::weak_ptr<ModuleRenderer> moduleRenderer;


};

