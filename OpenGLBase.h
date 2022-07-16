#pragma once

#include "GLEW/glew.h"	// extensions
#include <gl/GL.h>	    // gl lib
#include "GLFW/glfw3.h"	// windowing lib
#include <cassert>
#include <iostream>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"./GLEW/glew32.lib")
#pragma comment(lib,"./GLFW/glfw3.lib")



class OpenGLBase
{
protected:
	OpenGLBase();
	OpenGLBase(const OpenGLBase& rhs) = delete;
	OpenGLBase& operator=(const OpenGLBase& rhs) = delete;
	virtual ~OpenGLBase();

public:

	void RenderLoop();
	void CheckGLErrors();
	int getWindowWidth();
	int getWindowHeight();
	int getWindowXpos();
	int getWindowYpos();
	void setWindowXpos(int32_t x);
	void setWindowYpos(int32_t y);


	//Convinience input overrides
	virtual bool Initialize();
	virtual void OnResize(int width, int height) {}
	virtual void OnMouseMove(double xpos, double ypos) {}


protected:

	bool InitializeWindowAndOpenGLContext();

//pure virtuals  functions
protected:

	virtual void RenderFrame() = 0;
	virtual void UpdateFrame() = 0;

	
public:
	int32_t mClientWindowWidth = 1920;
	int32_t mClientWindowHeight = 1080;
	int32_t mXwindowPos ;
	int32_t mYwindowPos ;

	bool mFullScreenState = false;
	GLFWwindow* mWindow = nullptr;

};


