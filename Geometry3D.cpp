#include "Geometry3D.h"


Geometry3D::Geometry3D() : t(0),deltaTime(0),lastFrame(0),mVAO(0),mVEO(0),shaderProgram(0)
{

}

Geometry3D::~Geometry3D()
{

	//CheckGLErrors();

}



bool Geometry3D::Initialize()
{
	//superclass initialize
	assert(OpenGLBase::Initialize() == true);


	//Add data

	GLuint VBO;
	glGenVertexArrays(1, &mVAO); glGenBuffers(1, &VBO);
	glBindVertexArray(mVAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<glm::vec3> cubeVertices;


	//front 
	glm::vec3 leftTopFront = glm::vec3(-0.5, 0.5, 0.5);
	glm::vec3 yellow = glm::vec3(1.0, 1.0, 0.0);

	cubeVertices.push_back(leftTopFront);
	cubeVertices.push_back(yellow);

	glm::vec3 rightTopFront = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 white = glm::vec3(1.0, 1.0, 1.0);

	cubeVertices.push_back(rightTopFront);
	cubeVertices.push_back(white);

	glm::vec3 leftBottomFront = glm::vec3(-0.5, -0.5, 0.5);
	glm::vec3 green = glm::vec3(0.0, 1.0, 0.0);

	cubeVertices.push_back(leftBottomFront);
	cubeVertices.push_back(green);

	glm::vec3 rightBottomFront = glm::vec3(0.5, -0.5, 0.5);
	glm::vec3 cyan = glm::vec3(0.0, 1.0, 1.0);

	cubeVertices.push_back(rightBottomFront);
	cubeVertices.push_back(cyan);

	//back 
	glm::vec3 leftTopBack = glm::vec3(-0.5, 0.5, -0.5);
	glm::vec3 red = glm::vec3(1.0, 0.0, 0.0);
	cubeVertices.push_back(leftTopBack);
	cubeVertices.push_back(red);

	glm::vec3 rightTopBack = glm::vec3(0.5, 0.5, -0.5);
	glm::vec3 black = glm::vec3(0.0, 0.0, 0.0);

	cubeVertices.push_back(rightTopBack);
	cubeVertices.push_back(black);

	glm::vec3 leftBottomBack = glm::vec3(-0.5, -0.5, -0.5);
	glm::vec3 magenta = glm::vec3(1.0, 0.0, 1.0);
	cubeVertices.push_back(leftBottomBack);
	cubeVertices.push_back(magenta);

	glm::vec3 rightBottomBack = glm::vec3(0.5, -0.5, -0.5);
	glm::vec3 blue = glm::vec3(0.0, 0.0, 1.0);
	cubeVertices.push_back(rightBottomBack);
	cubeVertices.push_back(blue);

	

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cubeVertices.size(), static_cast<void*>(cubeVertices.data()), GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &mVEO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVEO);

	std::vector<uint16_t> indices;

	//front
	indices.push_back(0);indices.push_back(2);indices.push_back(1); //front left triangle
	indices.push_back(1); indices.push_back(2); indices.push_back(3); //front right triangle

	//right
	indices.push_back(1); indices.push_back(3); indices.push_back(5); //right left triangle
	indices.push_back(5); indices.push_back(3); indices.push_back(7); //right right triangle

	//back
	indices.push_back(5); indices.push_back(7); indices.push_back(6); //back left triangle
	indices.push_back(5); indices.push_back(6); indices.push_back(4); //back right triangle

	//left
	indices.push_back(0); indices.push_back(4); indices.push_back(6); //back left triangle
	indices.push_back(0); indices.push_back(6); indices.push_back(2); //back right triangle

	//top
	indices.push_back(5); indices.push_back(4); indices.push_back(0); //back left triangle
	indices.push_back(5); indices.push_back(0); indices.push_back(1); //back right triangle

	//bottom
	indices.push_back(3); indices.push_back(2); indices.push_back(6); //back left triangle
	indices.push_back(3); indices.push_back(6); indices.push_back(7); //back right triangle

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(),GL_STATIC_DRAW);





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

	glEnable(GL_DEPTH_TEST);
	
	glClearColor(0.0,0.0,0.0, 0.0); // R G B A
	
	
	OnResize(mClientWindowWidth, mClientWindowHeight);
	
	return true;
}

void Geometry3D::UpdateFrame()
{
	t += 0.1f;

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cam.updateCamera(mWindow, deltaTime);

	GLint model = glGetUniformLocation(shaderProgram, "rotationMatrix");
	GLint view = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint perspective = glGetUniformLocation(shaderProgram, "perspectiveMatrix");

	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(t), glm::vec3(1.0, 1.0, 1.0));
	
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(cam.viewTransform()));
	glUniformMatrix4fv(perspective, 1, GL_FALSE, glm::value_ptr(cam.perspectiveTransform(mClientWindowWidth,mClientWindowHeight)));

	if (t >= 360.0f)
	{
		t = 0.0f;
	}
}

void Geometry3D::RenderFrame()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bind program and data
	glUseProgram(shaderProgram);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mVEO);
	
	//initialize the program appropriate primitive to work on
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


}


void Geometry3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}



void Geometry3D::OnMouseMove(double xpos, double ypos)
{
	cam.mouseMove(xpos, ypos);

}