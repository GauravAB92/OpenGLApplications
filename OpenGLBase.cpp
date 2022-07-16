#include "OpenGLBase.h"

//global pointer to class to be used for callbacks
OpenGLBase* base;



//some auxillary c style funcitions

void windowFullscreenMode(GLFWwindow* window)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	GLFWmonitor* currentMonitor = glfwGetWindowMonitor(window);

	////check if fullscreen or widowed mode
	////if windowed turn to fullscreen

	//retrive position
	int32_t xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	base->setWindowXpos(xpos);
	base->setWindowYpos(ypos);

	glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	
}


void windowWindowedMode(GLFWwindow* window, int width, int height)
{
	//retrive position
	if (base->getWindowXpos() == 0)
	{
		int32_t xpos, ypos;
		glfwGetWindowPos(window, &xpos, &ypos);
		base->setWindowXpos(xpos);
		base->setWindowYpos(ypos);
	}

	glfwSetWindowMonitor(window, NULL, base->getWindowXpos(), base->getWindowYpos(), width, height, 0);
}


//C signature callbacks required for glfw

void resize(GLFWwindow* window, int width, int height)
{
	base->OnResize(width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	base->OnMouseMove(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		windowFullscreenMode(window);
		
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		windowWindowedMode(window, base->getWindowWidth(), base->getWindowHeight());
	}

}


OpenGLBase::OpenGLBase() 
{
	base = this;
}


OpenGLBase::~OpenGLBase()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}




bool OpenGLBase::InitializeWindowAndOpenGLContext()
{
	assert(glfwInit() == GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* window = glfwCreateWindow(
		mClientWindowWidth, mClientWindowHeight, "OpenGL Application", nullptr, nullptr
	);
	
	if (!window)
	{
		glfwTerminate();
		std::cerr << "glfw failed to create window\n";
		return false;
	}

	mWindow = window;

	glfwMakeContextCurrent(mWindow);

	glewExperimental = true;

	GLenum err_no = glewInit();

	if (err_no != GLEW_OK)
	{
		std::cerr << glewGetErrorString(err_no) << "\n";
		glfwDestroyWindow(mWindow);
		glfwTerminate();
		return false;
	}


	return true;
}

bool OpenGLBase::Initialize()
{
	if (!InitializeWindowAndOpenGLContext())
	{
		return false;
	}

	//set callbacks

	glfwSetWindowSizeCallback(mWindow, resize);
	glfwSetCursorPosCallback(mWindow, mouseCallback);
	glfwSetKeyCallback(mWindow, key_callback);

	return true;
}

void OpenGLBase::RenderLoop()
{
	
	while (!glfwWindowShouldClose(mWindow))
	{
		

		UpdateFrame();
		RenderFrame();

		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}
}


void OpenGLBase::CheckGLErrors()
{

	GLenum error = glGetError();

	if (error != GL_NO_ERROR) 
	{
		switch (error)
		{
		case GL_INVALID_VALUE:

			std::cerr << "ERROR: " << "GL_INVALID_VALUE" << "\n";
			break;
		case GL_INVALID_OPERATION:

			std::cerr << "ERROR: " << "GL_INVALID_OPERATION" << "\n";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:

			std::cerr << "ERROR: " << "GL_INVALID_FRAMEBUFFER_OPERATION" << "\n";
			break;
		case GL_OUT_OF_MEMORY:

			std::cerr << "ERROR: " << "GL_OUT_OF_MEMORY" << "\n";
			break;
		case GL_STACK_UNDERFLOW:

			std::cerr << "ERROR: " << "GL_STACK_UNDERFLOW" << "\n";
			break;
		case GL_STACK_OVERFLOW:

			std::cerr << "ERROR: " << "GL_STACK_OVERFLOW" << "\n";
			break;
		default:

			std::cerr << "ERROR: " << "UNKNOWN" << "\n";
			break;
		}
	}
	else 
	{
		std::cerr << "No errors reported.\n";
	}
}
int OpenGLBase::getWindowWidth()
{
	return mClientWindowWidth;
}

int OpenGLBase::getWindowHeight()
{
	return mClientWindowHeight;
}

int  OpenGLBase :: getWindowXpos()
{
	return mXwindowPos;
}

int  OpenGLBase :: getWindowYpos()
{
	return mYwindowPos;
}


void  OpenGLBase::setWindowXpos(int32_t xpos)
{
	mXwindowPos = xpos;
}

void  OpenGLBase::setWindowYpos(int32_t ypos)
{
	mYwindowPos = ypos;
}