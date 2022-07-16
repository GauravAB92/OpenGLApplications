#include "HelloTriangle.h"


HelloTriangle::HelloTriangle()
{

}

HelloTriangle::~HelloTriangle()
{

	//CheckGLErrors();

}



bool HelloTriangle::Initialize()
{
	//superclass initialize
	assert(OpenGLBase::Initialize() == true);


	//Add data

	GLuint VBO;
	glGenVertexArrays(1, &mVAO); glGenBuffers(1, &VBO);
	glBindVertexArray(mVAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<glm::vec3> positions;

	glm::vec3 left_bottom = glm::vec3(-0.5f, -0.5f, 0.0f);
	glm::vec3 right_bottom = glm::vec3(0.5f, -0.5f, 0.0f);
	glm::vec3 top = glm::vec3(0.0f, 0.5f, 0.0f);

	positions.push_back(left_bottom);
	positions.push_back(right_bottom);
	positions.push_back(top);


	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, static_cast<void*>(positions.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	compileShaderFile(vertexShader, "./vertex_shader.glsl");
	compileShaderFile(fragmentShader, "./fragment_shader.glsl");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	linkShaderProgram(shaderProgram);

	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	glClearColor(1.0, 1.0, 1.0, 0.0); // R G B A
	

	OnResize(mClientWindowWidth, mClientWindowHeight);
	
	return true;
}

void HelloTriangle::UpdateFrame()
{

}

void HelloTriangle::RenderFrame()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bind program and data
	glUseProgram(shaderProgram);
	glBindVertexArray(mVAO);

	//initialize the program appropriate primitive to work on
	glDrawArrays(GL_TRIANGLES, 0, 3);


}


void HelloTriangle::OnResize(int width, int height) 
{
	glViewport(0, 0, width, height);
}


