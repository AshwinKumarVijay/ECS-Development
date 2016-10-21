#pragma once

#include "../ECS/System/System.h"


class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;

class Renderer;
class BasicRenderer;
class DeferredRenderer;

class Camera;

class RenderingSystem : public System
{

public:

	//	Default Rendering System Constructor. The Entity Manager and the Event Queue the System will use.
	RenderingSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);
	
	//	Default Rendering System Destructor.
	virtual ~RenderingSystem();

	//	Miscellaneous initialization of the System.
	virtual void initializeSystem();

	//	Update the System - Render!
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);
	
	//	Return a pointer to the Renderer.
	std::shared_ptr<Renderer> getRenderer();

	//	Shut Down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();



protected:

	//	Process the Events that have occurred.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

private:


	//	Add a renderable to the renderer.
	virtual void addRenderable(const long int & entityID);

	//	Update the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderable(const long int & entityID);

	//	Update the Shader Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableShaderType(const long int & entityID);
	
	//	Update the Material Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableMaterialType(const long int & entityID);

	//	Update the Geometry Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableGeometryType(const long int & entityID);

	//	Update the Transform Matrix of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableTransformMatrix(const long int & entityID);

	//	Update the Camera.
	virtual void updateCamera();

	//	Remove the Renderable associated with the entity specified by Entity ID.
	virtual void removeRenderable(const long int & entityID);

	//	Process the Resource Events.
	virtual void processResourceEvents(std::shared_ptr<const ECSEvent> nextEvent);

	//	Process Camera Events.
	virtual void processCameraEvents(std::shared_ptr<const ECSEvent> nextEvent);

	//	A pointer to the associated Renderer.
	std::shared_ptr<Renderer> renderer;

	//	A pointer to the default camera.
	std::shared_ptr<Camera> defaultCamera;

	//	A pointer to the active camera.
	std::shared_ptr<Camera> activeCamera;
};

