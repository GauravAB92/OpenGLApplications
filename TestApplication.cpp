#include "TestApplication.h"


Test::Test()
{

}

Test::~Test()
{

	//CheckGLErrors();

}



bool Test::Initialize()
{
	//superclass initialize
	assert(OpenGLBase::Initialize() == true);


	//To stuff here

	
	glClearColor(1.0, 1.0, 1.0, 0.0); // R G B A
	

	OnResize(mClientWindowWidth, mClientWindowHeight);
	
	return true;
}

void Test::UpdateFrame()
{

}

void Test::RenderFrame()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


