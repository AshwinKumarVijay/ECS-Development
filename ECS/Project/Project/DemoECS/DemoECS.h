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

#include "../RDFP/RDFP.h"
#include "../TBM/TBM.h"

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

	//	Initialize the Camera Views.
	void initializeCameraViews();

	//	Load the Resources From a given file.
	virtual void loadResourcesFromFile(const std::string & resourceFile);

	//	Process the Resource.
	virtual void processResource(const ResourceDescription & currentResourceDescription);

	//	Process the provided input.
	virtual void processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType);

	//	Update the ECS.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

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

	//	The Resources and the Resource Description.
	std::map<std::string, ResourceDescription> resources;

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

	//	The Cube Entity.
	long int cubeEntity1;
	long int cubeEntity2;

	//	The Camera Views Entities.
	long int cameraEntity1;
	long int cameraEntity2;
	long int cameraEntity3;
	long int cameraEntity4;

	//	The Base Entity.
	long int baseEntity;

	//	Resource Description File Parser.
	RDFP rdfp;

	//	TerrainBlockMaker
	TBM tbm;
};

