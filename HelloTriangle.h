#pragma once
#include "OpenGLBase.h"
#include "OpenGLUtils.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include "glm/glm.hpp"


class HelloTriangle : public OpenGLBase
{
public:

	HelloTriangle();
	~HelloTriangle();
	
	virtual void RenderFrame() override;
	virtual void UpdateFrame() override;

	virtual bool Initialize() override;
	virtual void OnResize(int ,int) override;



public:

	//triangle positions
	GLuint mVAO;
	GLuint shaderProgram;

	
};





