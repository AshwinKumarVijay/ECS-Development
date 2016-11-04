#pragma once

#include <iostream>
#include <memory>

//#include "vld.h"
#include "glm\glm.hpp"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Configuration\Configuration.h"
#include "DemoECS\DemoECS.h"
#include "PlanetMakerECS\PlanetMakerECS.h"

#include "TypesList\ComponentTypes.h"
#include "TypesList\EntityState.h"
#include "TypesList\EventTypes.h"
#include "TypesList\InputTypes.h"
#include "TypesList\ModuleType.h"
#include "TypesList\ResourceTypes.h"


//	
int main(int argc, char** argv);


// Initialize GLEW.
int initializeGLEW();

//	Initialize GLFW.
int initializeGLFW();

//	Initialize the ECS.
void initializeECS();

//	Render the Cycle.
void enterRenderCycle();

//	Terminate the ECS.
void terminateECS();

//	Key Callback.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


//	Pointer to the ECS.
std::shared_ptr<PlanetMakerECS> ecs;

//	Current Frame Time.
float deltaFrameTime, currentFrameTime, lastFrameTime;

// Default initialization for monitor
GLFWmonitor * monitor;
const GLFWvidmode * mode;
GLFWwindow	* window;
