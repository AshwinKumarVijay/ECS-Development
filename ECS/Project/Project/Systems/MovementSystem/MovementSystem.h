#pragma once

#include "glm\glm.hpp"

#include "../ECS/System/System.h"

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;

class MovementSystem : public System
{


public:
	
	//	Add Comments - TO DO
	MovementSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Add Comments - TO DO
	virtual ~MovementSystem();

	//	Add Comments - TO DO
	virtual void initializeSystem();

	//	Add Comments - TO DO
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Add Comments - TO DO
	virtual void shutDownSystem();

	//	Add Comments - TO DO
	virtual void destroySystem();


private:

	//	Add Comments - TO DO
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);



};

