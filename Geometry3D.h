#pragma once
#include "OpenGLBase.h"
#include "OpenGLUtils.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"


class Geometry3D : public OpenGLBase
{
public:

	Geometry3D();
	~Geometry3D();
	
	virtual void RenderFrame() override;
	virtual void UpdateFrame() override;

	virtual bool Initialize() override;
	virtual void OnResize(int ,int) override;
	virtual void OnMouseMove(double xpos, double ypos) override;



public:

	GLuint mVAO;	//vertex array object
	GLuint mVEO;	//index buffer
	GLuint shaderProgram; 

	Camera cam;

	float t; //timer
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

};





