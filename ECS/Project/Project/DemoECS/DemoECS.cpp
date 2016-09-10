#include "DemoECS.h"

#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/EntityManager/EntityManager.h"

#include "../ECS/System/System.h"
#include "../Systems/TransformSystem/TransformSystem.h"
#include "../Systems/RenderingSystem/RenderingSystem.h"
#include "../Systems/CameraSystem/CameraSystem.h"
#include "../Systems/MovementSystem/MovementSystem.h"
#include "../Systems/InputSystem/InputSystem.h"
#include "../Systems/InteractionMovementResponseSystem/InteractionMovementResponseSystem.h"

#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/SpeedComponent/SpeedComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include "../Transform/Transform.h"

#include "../GeometryGeneratorSelector/GeometryGeneratorSelector.h"
#include "../TextureGeneratorSelector/TextureGeneratorSelector.h"

#include "../Resources/ResourceManager/GeometryResourceManager/GeometryResourceManager.h"
#include "../Resources/ResourceManager/MaterialResourceManager/MaterialResourceManager.h"
#include "../Resources/ResourceManager/LightResourceManager/LightResourceManager.h"
#include "../Resources/ResourceManager/TextureResourceManager/TextureResourceManager.h"
#include "../Resources/ResourceManager/ShaderResourceManager/ShaderResourceManager.h"

#include "../Resources/ResourceData/MaterialData/MaterialData.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../Resources/ResourceData/LightData/LightData.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"

#include "../Renderers/BasicRenderer/BasicRenderer.h"

//	Default DemoECS Constructor
DemoECS::DemoECS()
{


}

//	Default DemoECS Destructor
DemoECS::~DemoECS()
{

}

//	Initialize the Demo ECS.
void DemoECS::initializeDemoECS()
{
	//	Initialize the underlying ECS.
	ECS::initializeECS();

	//	Geometry and Texture Factories.
	geometryGeneratorSelector = std::make_shared<GeometryGeneratorSelector>();
	textureGeneratorSelector = std::make_shared<TextureGeneratorSelector>();

	//	Initialize the InteractionGenerationSystem.
	inputSystem = std::make_shared<InputSystem>(getEntityManager(), getEventQueue());
	inputSystem->initializeSystem();

	interactionMovementResponseSystem = std::make_shared<InteractionMovementResponseSystem>(getEntityManager(), getEventQueue());
	interactionMovementResponseSystem->initializeSystem();

	//	Initialize the Movement System.
	movementSystem = std::make_shared<MovementSystem>(getEntityManager(), getEventQueue());
	movementSystem->initializeSystem();

	//	Initialize the Transform System.
	transformSystem = std::make_shared<TransformSystem>(getEntityManager(), getEventQueue());
	transformSystem->initializeSystem();

	//	Initialize the Camera System.
	cameraSystem = std::make_shared<CameraSystem>(getEntityManager(), getEventQueue());
	cameraSystem->initializeSystem();

	//	Initialize the Rendering System.
	renderingSystem = std::make_shared<RenderingSystem>(getEntityManager(), getEventQueue());
	renderingSystem->initializeSystem();


	//	Create the Geometry, Material, Light, Texture and Shader Resource Manager.
	geometryResourceManager = std::make_shared<GeometryResourceManager>(getEventQueue());
	materialResourceManager = std::make_shared<MaterialResourceManager>(getEventQueue());
	lightResourceManager = std::make_shared<LightResourceManager>(getEventQueue());
	textureResourceManager = std::make_shared<TextureResourceManager>(getEventQueue());
	shaderResourceManager = std::make_shared<ShaderResourceManager>(getEventQueue());

	//	Initialize the VR Scene.
	initializeScene();

	//	Register the Systems.
	ECS::registerSystem(inputSystem);
	ECS::registerSystem(interactionMovementResponseSystem);
	ECS::registerSystem(movementSystem);
	ECS::registerSystem(transformSystem);
	ECS::registerSystem(cameraSystem);
	ECS::registerSystem(renderingSystem);

	//	Dispatch the ECS_START_EVENT to the Event Queue.
	getDispatcher()->dispatchToEventQueue(EventType::ECS_START_EVENT, ModuleType::GLOBAL, ComponentType::NO_COMPONENT, 0);
}

//	Initialize the VR Scene.
void DemoECS::initializeScene()
{
	//	Create the Sphere Entity.
	sphereEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy, Transform, Speed, Geometry and Rendering Component.
	getEntityManager()->addComponentToEntity(sphereEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(sphereEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(sphereEntity, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(sphereEntity, ComponentType::RENDERING_COMPONENT);

	std::shared_ptr<GeometryComponent> sphereGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(sphereEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	sphereGeometryComponent->setGeometryType("SPHERE");

	std::shared_ptr<RenderingComponent> sphereRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(sphereEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	sphereRenderingComponent->setMaterialType("DEFAULT MATERIAL 3");
	sphereRenderingComponent->setShaderType("BASIC DEFERRED SHADER");

	std::shared_ptr<TransformComponent> sphereTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(sphereEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	sphereTransformComponent->getTransform()->translateBy(glm::vec3(0.0, 2.0, 0.0));
	sphereTransformComponent->getTransform()->setScale(glm::vec3(2.0, 2.0, 2.0));


	//	Create the Sphere Entity.
	baseEntity = getEntityManager()->createEntity();

	//	Add the Hierarcy, Transform, Speed, Geometry and Rendering Component.
	getEntityManager()->addComponentToEntity(baseEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(baseEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(baseEntity, ComponentType::GEOMETRY_COMPONENT);
	getEntityManager()->addComponentToEntity(baseEntity, ComponentType::RENDERING_COMPONENT);

	std::shared_ptr<GeometryComponent> baseGeometryComponent = std::dynamic_pointer_cast<GeometryComponent>(getEntityManager()->getComponentOfEntity(baseEntity, ComponentType::GEOMETRY_COMPONENT, ModuleType::NO_MODULE));
	baseGeometryComponent->setGeometryType("CUBE");

	std::shared_ptr<RenderingComponent> baseRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(baseEntity, ComponentType::RENDERING_COMPONENT, ModuleType::NO_MODULE));
	baseRenderingComponent->setMaterialType("DEFAULT MATERIAL 3");
	baseRenderingComponent->setShaderType("BASIC DEFERRED SHADER");

	std::shared_ptr<TransformComponent> baseTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(baseEntity, ComponentType::TRANSFORM_COMPONENT, ModuleType::NO_MODULE));
	baseTransformComponent->getTransform()->setScale(glm::vec3(50.0, 0.01, 50.0));


}

//	Load the Geometry From File.
void DemoECS::loadGeometryFromFile(const std::string & geometryResourceFile)
{
	//	Open the Geometry Resource File.
	std::ifstream sourceFile(geometryResourceFile.c_str(), std::ifstream::in);
	std::string nextLine;

	if (sourceFile.is_open())
	{
		//	As long as there are still lines left.
		while (!sourceFile.eof())
		{
			getline(sourceFile, nextLine);
			if (nextLine == "#define Geometry")
			{
				//	Get the Geometry Name.
				std::string geometryNameLine;
				getline(sourceFile, geometryNameLine);
				std::vector<std::string> interpretedGeometryNameLine = StringModifiers::split_string(geometryNameLine, "=");
				std::string geometryName = interpretedGeometryNameLine[1];
				StringModifiers::trim(geometryName);

				//	Get the Geometry Type.
				std::string geometryTypeLine;
				getline(sourceFile, geometryTypeLine);
				std::vector<std::string> interpretedGeometryTypeLine = StringModifiers::split_string(geometryTypeLine, "=");
				std::string geometryType = interpretedGeometryTypeLine[1];
				StringModifiers::trim(geometryType);

				//	Get the Geometry Filename.
				std::string geometryFileNameLine;
				getline(sourceFile, geometryFileNameLine);
				std::vector<std::string> interpretedGeometryFileNameLine = StringModifiers::split_string(geometryFileNameLine, "=");
				std::string geometryFileName = interpretedGeometryFileNameLine[1];
				StringModifiers::trim(geometryFileName);

				//	Get the Geometry Parameters.
				std::string geometryParametersLine;
				getline(sourceFile, geometryParametersLine);
				std::vector<std::string> interpretedGeometryParametersLine = StringModifiers::split_string(geometryParametersLine, "=");
				std::string geometryParameters = interpretedGeometryParametersLine[1];
				StringModifiers::trim(geometryParameters);

				//	Parse OBJS.
				std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> generatedGeometry = geometryGeneratorSelector->generateGeometry(geometryType, geometryFileName, geometryParameters);

				//	
				if (generatedGeometry->size() == 1)
				{
					geometryResourceManager->addGeometry(geometryName, (*generatedGeometry)[0]);
				}
				else
				{
					//	Assuming more than one piece of Geometry was created.
					for (int i = 0; i < generatedGeometry->size(); i++)
					{
						//	Create the new geometry name.
						std::string currentGeometryName = geometryName + " " + std::to_string(i);

						//	Add the new geometry.
						geometryResourceManager->addGeometry(currentGeometryName, (*generatedGeometry)[i]);
					}
				}
			}
		}
	}
	else
	{
		//	Throw - Could not open the Geometry file.
		std::cout << "Error - Could Not Open Geometry File " << geometryResourceFile << std::endl;
	}

}

//	Load the Materials from File.
void DemoECS::loadMaterialsFromFile(const std::string & materialResourceFile)
{
	//	Open the Material Resource File.
	std::ifstream sourceFile(materialResourceFile.c_str(), std::ifstream::in);
	std::string nextLine;

	//	Parse the file.
	if (sourceFile.is_open())
	{
		//	As long as there are still lines left.
		while (!sourceFile.eof())
		{
			getline(sourceFile, nextLine);
			if (nextLine == "#define Material")
			{
				//	Get the Material Name.
				std::string materialNameLine = "";
				getline(sourceFile, materialNameLine);
				std::vector<std::string> interpretedMaterialLine = StringModifiers::split_string(materialNameLine, "=");
				std::string materialName = interpretedMaterialLine[1];
				StringModifiers::trim(materialName);

				//	Get the Diffuse Albedo Values.
				std::string diffuseAlbedoLine = "";
				getline(sourceFile, diffuseAlbedoLine);
				std::vector<std::string> interpretedDiffuseAlbedoLine = StringModifiers::split_string(diffuseAlbedoLine, "=");
				std::vector<std::string> diffuseAlbedoLineValues = StringModifiers::split_string(interpretedDiffuseAlbedoLine[1], ",");
				glm::vec4 diffuseAlbedoValues = glm::vec4(std::stof(diffuseAlbedoLineValues[0]), std::stof(diffuseAlbedoLineValues[1]), std::stof(diffuseAlbedoLineValues[2]), std::stof(diffuseAlbedoLineValues[3]));

				//	Get the Specular Albedo Values.
				std::string specularAlbedoLine = "";
				getline(sourceFile, specularAlbedoLine);
				std::vector<std::string> interpretedSpecularAlbedoLine = StringModifiers::split_string(specularAlbedoLine, "=");
				std::vector<std::string> specularAlbedoLineValues = StringModifiers::split_string(interpretedSpecularAlbedoLine[1], ",");
				glm::vec4 specularAlbedoValues = glm::vec4(std::stof(specularAlbedoLineValues[0]), std::stof(specularAlbedoLineValues[1]), std::stof(specularAlbedoLineValues[2]), std::stof(specularAlbedoLineValues[3]));

				//	Get the Emissive Color Values.
				std::string emissiveColorLine = "";
				getline(sourceFile, emissiveColorLine);
				std::vector<std::string> interpretedEmissiveColorLine = StringModifiers::split_string(emissiveColorLine, "=");
				std::vector<std::string> emissiveColorLineValues = StringModifiers::split_string(interpretedEmissiveColorLine[1], ",");
				glm::vec4 emissiveColorValues = glm::vec4(std::stof(emissiveColorLineValues[0]), std::stof(emissiveColorLineValues[1]), std::stof(emissiveColorLineValues[2]), std::stof(emissiveColorLineValues[3]));

				//	Get the Metallic, Roughness and Opacity Values.
				std::string metallicRoughnessFresnelOpacityLine = "";
				getline(sourceFile, metallicRoughnessFresnelOpacityLine);
				std::vector<std::string> interpretedmetallicRoughnessFresnelOpacityLine = StringModifiers::split_string(metallicRoughnessFresnelOpacityLine, "=");
				std::vector<std::string> metallicRoughnessOpacityLineValues = StringModifiers::split_string(interpretedmetallicRoughnessFresnelOpacityLine[1], ",");
				glm::vec4 metallicRoughnessFresnelOpacityValues = glm::vec4(std::stof(metallicRoughnessOpacityLineValues[0]), std::stof(metallicRoughnessOpacityLineValues[1]), std::stof(metallicRoughnessOpacityLineValues[2]), std::stof(metallicRoughnessOpacityLineValues[3]));

				//	Get the Diffuse Albedo Map Value.
				std::string diffuseAlbedoMapLine = "";
				getline(sourceFile, diffuseAlbedoMapLine);
				std::vector<std::string> interpretedDiffuseAlbedoMapLine = StringModifiers::split_string(diffuseAlbedoMapLine, "=");
				std::string interpretedDiffuseAlbedoMap = StringModifiers::trimmed(interpretedDiffuseAlbedoMapLine[1]);

				std::string specularAlbedoMapLine = "";
				getline(sourceFile, specularAlbedoMapLine);
				std::vector<std::string> interpretedSpecularAlbedoMapLine = StringModifiers::split_string(specularAlbedoMapLine, "=");
				std::string interpretedSpecularAlbedoMap = StringModifiers::trimmed(interpretedSpecularAlbedoMapLine[1]);

				//	Get the Normal Map Value.
				std::string normalMapLine = "";
				getline(sourceFile, normalMapLine);
				std::vector<std::string> interpretedNormalMapLine = StringModifiers::split_string(normalMapLine, "=");
				std::string interpretedNormalMap = StringModifiers::trimmed(interpretedNormalMapLine[1]);

				//	Get the Occlusion Map Value.
				std::string occlusionMapLine = "";
				getline(sourceFile, occlusionMapLine);
				std::vector<std::string> interpretedOcclusionMapLine = StringModifiers::split_string(occlusionMapLine, "=");
				std::string interpretedOcclusionMap = StringModifiers::trimmed(interpretedOcclusionMapLine[1]);

				//	Create the new Material Values.
				MaterialValues newMaterialValues;
				newMaterialValues.diffuseAlbdeo = diffuseAlbedoValues;
				newMaterialValues.specularAlbedo = specularAlbedoValues;
				newMaterialValues.emissiveColor = emissiveColorValues;
				newMaterialValues.metallicRoughnessFresnelOpacity = metallicRoughnessFresnelOpacityValues;

				//	Create the new Material Maps.
				MaterialMaps newMaterialMaps;
				newMaterialMaps.DiffuseAlbedoMap = interpretedDiffuseAlbedoMap;
				newMaterialMaps.SpecularAlbedoMap = interpretedSpecularAlbedoMap;
				newMaterialMaps.NormalMap = interpretedNormalMap;
				newMaterialMaps.OcclusionMap = interpretedSpecularAlbedoMap;

				//	Add it to the Material Manager.
				std::shared_ptr<MaterialData> newMaterialData = std::make_shared<MaterialData>(newMaterialValues, newMaterialMaps);
				materialResourceManager->addMaterial(materialName, newMaterialData);
			}
		}
	}
	else
	{
		//	Throw - Could not open the Material file.
		std::cout << "Error - Could Not Open Material File " << materialResourceFile << std::endl;
	}

}

//	Load the Lights from File.
void DemoECS::loadLightsFromFile(const std::string & lightResourceFile)
{
	//	Open the Light Resource File.
	std::ifstream sourceFile(lightResourceFile.c_str(), std::ifstream::in);
	std::string nextLine;

	//	Parse the file.
	if (sourceFile.is_open())
	{
		//	As long as there are still lines left.
		while (!sourceFile.eof())
		{
			getline(sourceFile, nextLine);
			if (nextLine == "#define Light")
			{

				//	Get the Light Name.
				std::string lightNameLine;
				getline(sourceFile, lightNameLine);
				std::vector<std::string> interpretedLightNameLine = StringModifiers::split_string(lightNameLine, "=");
				std::string lightName = interpretedLightNameLine[1];
				StringModifiers::trim(lightName);

				//	Get whether the Light is enabled.
				std::string lightEnabledLine;
				getline(sourceFile, lightEnabledLine);
				std::vector<std::string> interpretedLightEnabledLine = StringModifiers::split_string(lightEnabledLine, "=");
				StringModifiers::trim(interpretedLightEnabledLine[1]);
				bool lightEnabled = (interpretedLightEnabledLine[1] == "True");

				//	Get whether the Light is enabled.
				std::string lightLocalLine;
				getline(sourceFile, lightLocalLine);
				std::vector<std::string> interpretedLightLocalLine = StringModifiers::split_string(lightLocalLine, "=");
				StringModifiers::trim(interpretedLightLocalLine[1]);
				bool lightLocal = (interpretedLightLocalLine[1] == "True");

				//	Get the Light Type.
				std::string lightTypeLine;
				getline(sourceFile, lightTypeLine);
				std::vector<std::string> interpretedLightTypeLine = StringModifiers::split_string(lightTypeLine, "=");
				int lightType = std::stoi(interpretedLightTypeLine[1]);

				//	Get the Light color.
				std::string lightColorLine;
				getline(sourceFile, lightColorLine);
				std::vector<std::string> interpretedLightColorLine = StringModifiers::split_string(lightColorLine, "=");
				std::vector<std::string> lightColorValues = StringModifiers::split_string(interpretedLightColorLine[1], ",");
				glm::vec3 lightColor = glm::vec3(std::stof(lightColorValues[0]), std::stof(lightColorValues[1]), std::stof(lightColorValues[2]));

				//	Get the Light Intensity.
				std::string lightIntenstiyLine;
				getline(sourceFile, lightIntenstiyLine);
				std::vector<std::string> interpretedLightIntensityLine = StringModifiers::split_string(lightIntenstiyLine, "=");
				float lightIntensity = std::stof(interpretedLightIntensityLine[1]);

				//	Get the Light Position.
				std::string lightPositionLine;
				getline(sourceFile, lightPositionLine);
				std::vector<std::string> interpretedLightPositionLine = StringModifiers::split_string(lightPositionLine, "=");
				std::vector<std::string> lightPositionValues = StringModifiers::split_string(interpretedLightPositionLine[1], ",");
				glm::vec4 lightPosition = glm::vec4(std::stof(lightPositionValues[0]), std::stof(lightPositionValues[1]), std::stof(lightPositionValues[2]), std::stof(lightPositionValues[3]));

				//	Get the Light Attenuation.
				std::string lightAttenuationLine;
				getline(sourceFile, lightAttenuationLine);
				std::vector<std::string> interpretedAttenuationPositionLine = StringModifiers::split_string(lightAttenuationLine, "=");
				std::vector<std::string> lightAttenuationValues = StringModifiers::split_string(interpretedAttenuationPositionLine[1], ",");
				glm::vec4 lightAttenuation = glm::vec4(std::stof(lightAttenuationValues[0]), std::stof(lightAttenuationValues[1]), std::stof(lightAttenuationValues[2]), std::stof(lightAttenuationValues[3]));


				//	Get the Light SpotCosCutOffAndExponent.
				std::string lightSpotCosCutOffAndExponentLine;
				getline(sourceFile, lightSpotCosCutOffAndExponentLine);
				std::vector<std::string> interpretedSpotCosCutOffAndExponentLine = StringModifiers::split_string(lightSpotCosCutOffAndExponentLine, "=");
				std::vector<std::string> lightSpotCosCutOffAndExponentValues = StringModifiers::split_string(interpretedSpotCosCutOffAndExponentLine[1], ",");
				glm::vec4 lightSpotCosCutOffAndExponent = glm::vec4(std::stof(lightSpotCosCutOffAndExponentValues[0]), std::stof(lightSpotCosCutOffAndExponentValues[1]), std::stof(lightSpotCosCutOffAndExponentValues[2]), std::stof(lightSpotCosCutOffAndExponentValues[3]));

				std::shared_ptr<LightData> newLightData = std::make_shared<LightData>(lightEnabled, lightLocal, lightType, lightColor, lightIntensity, lightPosition, lightAttenuation, lightSpotCosCutOffAndExponent);
				lightResourceManager->addLight(lightName, newLightData);
			}
		}
	}
	else
	{
		//	Throw - Could not open the Light file.
		std::cout << "Error - Could Not Open Light File " << lightResourceFile << std::endl;

	}

}

//	Load the Textures From File.
void DemoECS::loadTexturesFromFile(const std::string & textureResourceFile)
{
	//	Open the Texture Resource File.
	std::ifstream sourceFile(textureResourceFile.c_str(), std::ifstream::in);
	std::string nextLine;

	if (sourceFile.is_open())
	{
		while (!sourceFile.eof())
		{
			getline(sourceFile, nextLine);

			if (nextLine == "#define Texture")
			{
				//	Get the Texture Name.
				std::string textureNameLine;
				getline(sourceFile, textureNameLine);
				std::vector<std::string> interpretedTextureNameLine = StringModifiers::split_string(textureNameLine, "=");
				std::string textureName = interpretedTextureNameLine[1];
				StringModifiers::trim(textureName);

				//	Get the Texture Type.
				std::string textureTypeLine;
				getline(sourceFile, textureTypeLine);
				std::vector<std::string> interpretedTextureTypeLine = StringModifiers::split_string(textureTypeLine, "=");
				std::string textureType = interpretedTextureTypeLine[1];
				StringModifiers::trim(textureType);

				//	Get the Texture Generation.
				std::string textureGenerationLine;
				getline(sourceFile, textureGenerationLine);
				std::vector<std::string> interpretedTextureGenerationLine = StringModifiers::split_string(textureGenerationLine, "=");
				std::string textureGeneration = interpretedTextureGenerationLine[1];
				StringModifiers::trim(textureGeneration);

				std::string textureParametersLine;
				getline(sourceFile, textureParametersLine);
				std::vector<std::string> interpretedTextureParametersLine = StringModifiers::split_string(textureParametersLine, "=");
				std::string textureParameters = interpretedTextureParametersLine[1];
				StringModifiers::trim(textureParameters);


				if (textureType == "TEXTURE_2D")
				{
					//	Get the Texture Source.
					std::string textureSourceLine;
					getline(sourceFile, textureSourceLine);
					std::vector<std::string> interpretedTextureSourceLine = StringModifiers::split_string(textureSourceLine, "=");
					std::string textureSource = interpretedTextureSourceLine[1];
					StringModifiers::trim(textureSource);

					std::shared_ptr<TextureData> newTextureData = std::make_shared<TextureData>(GL_TEXTURE_2D);
					std::shared_ptr<TextureBufferData> newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource, textureParameters);
					newTextureData->addTextureBufferData(0, newTextureBufferData);

					//	
					textureResourceManager->addTexture(textureName, newTextureData);

				}
				else if (textureType == "TEXTURE_CUBE_MAP")
				{
					std::shared_ptr<TextureData> newTextureData = std::make_shared<TextureData>(GL_TEXTURE_CUBE_MAP);

					//	Get the Texture Source 0.
					std::string textureSourceLine0;
					getline(sourceFile, textureSourceLine0);
					std::vector<std::string> interpretedTextureSource0Line = StringModifiers::split_string(textureSourceLine0, "=");
					std::string textureSource0 = interpretedTextureSource0Line[1];
					StringModifiers::trim(textureSource0);

					std::shared_ptr<TextureBufferData> newTextureBufferData0 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource0, textureParameters);

					//	Get the Texture Source 1.
					std::string textureSourceLine1;
					getline(sourceFile, textureSourceLine1);
					std::vector<std::string> interpretedTextureSource1Line = StringModifiers::split_string(textureSourceLine1, "=");
					std::string textureSource1 = interpretedTextureSource1Line[1];
					StringModifiers::trim(textureSource1);

					std::shared_ptr<TextureBufferData> newTextureBufferData1 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource1, textureParameters);

					//	Get the Texture Source 2.
					std::string textureSourceLine2;
					getline(sourceFile, textureSourceLine2);
					std::vector<std::string> interpretedTextureSource2Line = StringModifiers::split_string(textureSourceLine2, "=");
					std::string textureSource2 = interpretedTextureSource2Line[1];
					StringModifiers::trim(textureSource2);

					std::shared_ptr<TextureBufferData> newTextureBufferData2 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource2, textureParameters);

					//	Get the Texture Source 3.
					std::string textureSourceLine3;
					getline(sourceFile, textureSourceLine3);
					std::vector<std::string> interpretedTextureSource3Line = StringModifiers::split_string(textureSourceLine3, "=");
					std::string textureSource3 = interpretedTextureSource3Line[1];
					StringModifiers::trim(textureSource3);

					std::shared_ptr<TextureBufferData> newTextureBufferData3 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource3, textureParameters);

					//	Get the Texture Source 4.
					std::string textureSourceLine4;
					getline(sourceFile, textureSourceLine4);
					std::vector<std::string> interpretedTextureSource4Line = StringModifiers::split_string(textureSourceLine4, "=");
					std::string textureSource4 = interpretedTextureSource4Line[1];
					StringModifiers::trim(textureSource4);

					std::shared_ptr<TextureBufferData> newTextureBufferData4 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource4, textureParameters);

					//	Get the Texture Source 5.
					std::string textureSourceLine5;
					getline(sourceFile, textureSourceLine5);
					std::vector<std::string> interpretedTextureSource5Line = StringModifiers::split_string(textureSourceLine5, "=");
					std::string textureSource5 = interpretedTextureSource5Line[1];
					StringModifiers::trim(textureSource5);

					std::shared_ptr<TextureBufferData> newTextureBufferData5 = textureGeneratorSelector->generateTexture(textureGeneration, textureSource5, textureParameters);


					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(0, newTextureBufferData0);

					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(1, newTextureBufferData1);

					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(2, newTextureBufferData2);

					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(3, newTextureBufferData3);

					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(4, newTextureBufferData4);

					//	Add the the TextureBufferData to the appropriate location.
					newTextureData->addTextureBufferData(5, newTextureBufferData5);

					//	
					textureResourceManager->addTexture(textureName, newTextureData);
				}
			}
		}
	}
	else
	{
		//	Throw - Could not open the Texture file.
		std::cout << "Error - Could Not Open Texture File " << textureResourceFile << std::endl;
	}

}

//	Load the Shaders from File.
void DemoECS::loadShadersFromFile(const std::string & shaderResourceFile)
{
	//	Open the Shader Resource File.
	std::ifstream sourceFile(shaderResourceFile.c_str(), std::ifstream::in);
	std::string nextLine;

	if (sourceFile.is_open())
	{
		//	As long as there are still lines left.
		while (!sourceFile.eof())
		{
			//	Get the next line of the file.
			getline(sourceFile, nextLine);

			if (nextLine == "#define Shader")
			{
				//
				std::map<std::string, std::string> mapShaderPropertyToValue;

				//
				std::string shaderPropertyLine;
				std::vector<std::string> shaderPropertyLineParts;
				std::string shaderPropertyName = "";
				std::string shaderPropertyValue = "";

				//	Get the Name of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Type of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Camera Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Model Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Material Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Vertex Basic Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Vertex Tangent Bitangent Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Vertex Texture Coordinates of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Lights Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Environment Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Material Textures Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the G Buffer Data of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the output Default Color the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the ouput Opacity of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the output G Buffer the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Vertex Shader source of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Get the Fragment Shader source of the Shader.
				getline(sourceFile, shaderPropertyLine);
				shaderPropertyLineParts = StringModifiers::split_string(shaderPropertyLine, "=");
				shaderPropertyName = StringModifiers::trimmed(shaderPropertyLineParts[0]);
				shaderPropertyValue = StringModifiers::trimmed(shaderPropertyLineParts[1]);
				mapShaderPropertyToValue[shaderPropertyName] = shaderPropertyValue;

				//	Add the ShaderData to the Shader Resource Manager.
				std::shared_ptr<ShaderData> newShaderData = std::make_shared<ShaderData>(mapShaderPropertyToValue);

				//	Add the shader under the specified name.
				shaderResourceManager->addShader(newShaderData->getShaderProgramName(), newShaderData);
			}
		}
	}
	else
	{
		//	Throw - Could not open the Texture file.
		std::cout << "Error - Could Not Open Shader File " << shaderResourceFile << std::endl;
	}

}

//	Process the provided input.
void DemoECS::processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType)
{

}

//	Shut down the Demo ECS
void DemoECS::shutDownDemoECS()
{
	//	Shut down the underlying ECS.
	ECS::shutDownECS();

	//	Destroy the Input System.
	inputSystem->shutDownSystem();

	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->shutDownSystem();

	//	Destroy the Movement System.
	movementSystem->shutDownSystem();

	//	Destroy the CameraSystem.
	cameraSystem->shutDownSystem();

	//	Destroy the Transform System.
	transformSystem->shutDownSystem();

	//	Destroy the Rendering System.
	renderingSystem->shutDownSystem();
}

//	Clean Up the Demo ECS.
void DemoECS::destroyDemoECS()
{
	//	Clean up the underlying ECS.
	ECS::destroyECS();

	//	Destroy the Input System.
	inputSystem->destroySystem();
	
	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->destroySystem();

	//	Destroy the Movement System.
	movementSystem->destroySystem();

	//	Destroy the CameraSystem.
	cameraSystem->destroySystem();

	//	Destroy the Transform System.
	transformSystem->destroySystem();

	//	Destroy the Rendering System.
	renderingSystem->destroySystem();

}