#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include "glm\glm.hpp"

#include "../StringModifiers/StringModifiers.h"
#include "../ECS/ECS.h"

#include "../TypesList/EventTypes.h"
#include "../TypesList/ModuleType.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"

class System;
class TransformSystem;
class RenderingSystem;
class CameraSystem;
class InputSystem;
class InteractionMovementResponseSystem;
class MovementSystem;

class GeometryGeneratorSelector;
class TextureGeneratorSelector;

class GeometryResourceManager;
class MaterialResourceManager;
class LightResourceManager;
class TextureResourceManager;
class ShaderResourceManager;

class MaterialData;
class TextureData;
class LightData;
class GeometryData;
class ShaderData;


class DemoECS : public ECS
{

public:

	//	Default DemoECS Constructor
	DemoECS();

	//	Default DemoECS Destructor
	~DemoECS();

	//	Miscellaneous Initialization of the Demo ECS.
	void initializeDemoECS();

	//	Initialize the Scene.
	void initializeScene();

	//	Load Geometry from File.
	virtual void loadGeometryFromFile(const std::string & geometryResourceFile);

	//	Load Materials from File.
	virtual void loadMaterialsFromFile(const std::string & materialResourceFile);

	//	Load Lights from File.
	virtual void loadLightsFromFile(const std::string & lightResourceFile);

	//	Load Textures from File.
	virtual void loadTexturesFromFile(const std::string & textureResourceFile);

	//	Load Shaders from File.
	virtual void loadShadersFromFile(const std::string & shaderResourceFile);

	//	Process the provided input.
	virtual void processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType);

	//	Shut Down the Demo ECS.
	void shutDownDemoECS();

	//	Miscellaneous clean up of the Systems.
	void destroyDemoECS();


private:


	//	The Interaction Generation System associated with the DemoECS.
	std::shared_ptr<InputSystem> inputSystem;

	//	The Interaction Movement Response System associated with the DemoECS.
	std::shared_ptr<InteractionMovementResponseSystem> interactionMovementResponseSystem;

	//	The Camera System associated with the DemoECS.
	std::shared_ptr<CameraSystem> cameraSystem;

	//	The Movement System associated with the DemoECS.
	std::shared_ptr<MovementSystem> movementSystem;

	//	The Transform System associated with the DemoECS.
	std::shared_ptr<TransformSystem> transformSystem;

	//	The Rendering System associated with the DemoECS.
	std::shared_ptr<RenderingSystem> renderingSystem;

	//	Geometry Resource Manager
	std::shared_ptr<GeometryResourceManager> geometryResourceManager;

	//	Material Resource Manager
	std::shared_ptr<MaterialResourceManager> materialResourceManager;

	//	Light Resource Manager
	std::shared_ptr<LightResourceManager> lightResourceManager;

	//	Texture Resource Manager
	std::shared_ptr<TextureResourceManager> textureResourceManager;

	//	Shader Resource Manager
	std::shared_ptr<ShaderResourceManager> shaderResourceManager;

	//	Geometry Generator Selector
	std::shared_ptr<GeometryGeneratorSelector> geometryGeneratorSelector;

	//	Texture Generator Selector
	std::shared_ptr<TextureGeneratorSelector> textureGeneratorSelector;

	//	Sphere Entity.
	long int sphereEntity;
	long int baseEntity;

};

