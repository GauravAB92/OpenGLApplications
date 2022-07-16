#pragma once
#include "OpenGLBase.h"
#include "OpenGLUtils.h"
#include <cassert>


class Test : public OpenGLBase
{
public:

	Test();
	~Test();
	
	virtual void RenderFrame() override;
	virtual void UpdateFrame() override;

	virtual bool Initialize() override;



public:

	//some data

};





