#include "main.h"

//	
int main(int argc, char** argv)
{

	//	Initialize GLFW
	if (initializeGLFW() == -1) exit(-1);

	//	Initialize GLEW
	if (initializeGLEW() == -1) exit(-2);

	//	Initialize ECS.
	initializeECS();

	//	Begin the Rendering Cycle.
	enterRenderCycle();

	//	Terminate ECS.
	terminateECS();

	//	Return 0;
	return 0;
}

// Default GLEW initialization. 
int initializeGLEW()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialisation error: " << glewGetErrorString(err) << std::endl;
		return -1;
	}
	std::cout << "GLEW intialised successfully. Using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
	return 0;
}

//	Initialize GLFW.
int initializeGLFW()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	monitor = glfwGetPrimaryMonitor();

	mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_DECORATED, 0);

	window = glfwCreateWindow(1280, 720, "System Of Planets", NULL, NULL);
	glfwSetWindowPos(window, 320, 180);
	glfwSwapInterval(2);
	glfwSetKeyCallback(window, key_callback);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return 0;
}

//	Initialize the ECS.
void initializeECS()
{
	
	Configuration::getConfiguration().loadConfigurationFromFile("Assets/Configurations/DefaultConfig.txt");

	//	Create the Demo ECS.
	ecs = std::make_shared<DemoECS>();

	//	Initialize the Demo ECS.
	ecs->initializeDemoECS();

	//	Read in the Resources from the Resources File.
	ecs->loadResourcesFromFile(Configuration::getConfiguration().getProperty("RESOURCES FILE"));
}

//	Enter Render Cycle.
void enterRenderCycle()
{

	//	Last Frame Time.
	lastFrameTime = (float)glfwGetTime();

	//	While the GLFW window is open.
	while (!glfwWindowShouldClose(window))
	{
		//	Check the Current Frame Time.
		currentFrameTime = (float)glfwGetTime();

		//	Check the Delta Frame Time.
		deltaFrameTime = currentFrameTime - lastFrameTime;

		//	Update the ECS
		ecs->update(deltaFrameTime, currentFrameTime, lastFrameTime);

		//	Swap Buffers.
		glfwSwapBuffers(window);

		//	Poll the EVents.
		glfwPollEvents();

		//	Update the Last Frame Time.
		lastFrameTime = currentFrameTime;
	}
}

//	Terminate ECS.
void terminateECS()
{
	//	Shut Down the ECS.
	ecs->shutDownDemoECS();

	//	Clean Up the ECS.
	ecs->destroyDemoECS();

	//	Terminate GLFW.
	glfwTerminate();

}

//	Key Callback.
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//	ECS Event.
	EventType eventType = EventType::ECS_NO_EVENT;

	//	Input Event Type.
	InputEventType inputEventType = InputEventType::INPUT_NO_EVENT;

	//	ECS Key.
	InputType ecsKey = InputType::KEY_UNKNOWN;

	//	Select the Appropriate Action.
	switch (action)
	{

	case GLFW_PRESS:
		inputEventType = InputEventType::INPUT_KEY_PRESS;
		break;

	case GLFW_REPEAT:
		inputEventType = InputEventType::INPUT_KEY_PRESS;
		break;

	case GLFW_RELEASE:
		inputEventType = InputEventType::INPUT_KEY_RELEASE;
		break;

	default:
		inputEventType = InputEventType::INPUT_NO_EVENT;
		break;
	}

	//	Select the Appropriate Key.
	switch (key)
	{

	case GLFW_KEY_A:
		ecsKey = InputType::KEY_A;
		break;

	case GLFW_KEY_B:
		ecsKey = InputType::KEY_B;
		break;

	case GLFW_KEY_C:
		ecsKey = InputType::KEY_C;
		break;

	case GLFW_KEY_D:
		ecsKey = InputType::KEY_D;
		break;

	case GLFW_KEY_E:
		ecsKey = InputType::KEY_E;
		break;

	case GLFW_KEY_F:
		ecsKey = InputType::KEY_F;
		break;

	case GLFW_KEY_G:
		ecsKey = InputType::KEY_G;
		break;

	case GLFW_KEY_H:
		ecsKey = InputType::KEY_H;
		break;

	case GLFW_KEY_I:
		ecsKey = InputType::KEY_I;
		break;

	case GLFW_KEY_J:
		ecsKey = InputType::KEY_J;
		break;

	case GLFW_KEY_K:
		ecsKey = InputType::KEY_K;
		break;

	case GLFW_KEY_L:
		ecsKey = InputType::KEY_L;
		break;

	case GLFW_KEY_M:
		ecsKey = InputType::KEY_M;
		break;

	case GLFW_KEY_N:
		ecsKey = InputType::KEY_N;
		break;

	case GLFW_KEY_O:
		ecsKey = InputType::KEY_O;
		break;

	case GLFW_KEY_P:
		ecsKey = InputType::KEY_P;
		break;

	case GLFW_KEY_Q:
		ecsKey = InputType::KEY_Q;
		break;

	case GLFW_KEY_R:
		ecsKey = InputType::KEY_R;
		break;

	case GLFW_KEY_S:
		ecsKey = InputType::KEY_S;
		break;

	case GLFW_KEY_T:
		ecsKey = InputType::KEY_T;
		break;

	case GLFW_KEY_U:
		ecsKey = InputType::KEY_U;
		break;

	case GLFW_KEY_V:
		ecsKey = InputType::KEY_V;
		break;

	case GLFW_KEY_W:
		ecsKey = InputType::KEY_W;
		break;

	case GLFW_KEY_X:
		ecsKey = InputType::KEY_X;
		break;

	case GLFW_KEY_Y:
		ecsKey = InputType::KEY_Y;
		break;

	case GLFW_KEY_Z:
		ecsKey = InputType::KEY_Z;
		break;

	case GLFW_KEY_LEFT:
		ecsKey = InputType::KEY_LEFT;
		break;

	case GLFW_KEY_RIGHT:
		ecsKey = InputType::KEY_RIGHT;
		break;

	case GLFW_KEY_UP:
		ecsKey = InputType::KEY_UP;
		break;

	case GLFW_KEY_DOWN:
		ecsKey = InputType::KEY_DOWN;
		break;

	case GLFW_KEY_SPACE:
		ecsKey = InputType::KEY_SPACE;
		break;

	default:
		ecsKey = InputType::KEY_UNKNOWN;
		break;
	}

	if (ecsKey != InputType::KEY_UNKNOWN && inputEventType != InputEventType::INPUT_NO_EVENT)
	{
		eventType = EventType::INPUT_EVENT;
		ecs->processInput(ecsKey, inputEventType, eventType);
	}
}

