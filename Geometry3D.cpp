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

	GLuint VBO[3]; //vertices, normals, texcoords
	glGenBuffers(3, VBO);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);


	//GENERATE DATA
	//Teapot loading using tiny obj
	
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	const char* filename = "./models/untitled.obj";
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, "./models/", true);

	//assert proper load
	assert(ret == true);
	std::cout << "vertex count: " << attrib.vertices.size() << "\n";


	//preprocess the mesh

	uint32_t num_indices = shapes[0].mesh.indices.size();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;


	for (uint32_t i = 0; i < num_indices; i++)
	{
		uint32_t vertIndex = shapes[0].mesh.indices[i].vertex_index;
		uint32_t normIndex = shapes[0].mesh.indices[i].normal_index;
		uint32_t texcoordIndex = shapes[0].mesh.indices[i].texcoord_index;

		float vx = attrib.vertices[vertIndex * 3 + 0];
		float vy = attrib.vertices[vertIndex * 3 + 1];
		float vz = attrib.vertices[vertIndex * 3 + 2];

		float nx = attrib.normals[normIndex * 3 + 0];
		float ny = attrib.normals[normIndex * 3 + 1];
		float nz = attrib.normals[normIndex * 3 + 2];

		float tx = attrib.texcoords[texcoordIndex * 2 + 0];
		float ty = attrib.texcoords[texcoordIndex * 2 + 1];
		
		vertices.push_back(glm::vec3(vx, vy, vz));
		normals.push_back(glm::vec3(nx,ny,nz));
		uvs.push_back(glm::vec2(tx,ty));

	}

	num_vertices = vertices.size();

	

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), static_cast<void*>(vertices.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), static_cast<void*>(normals.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), static_cast<void*>(uvs.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);


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
	cam.updateCamera(mWindow, deltaTime);


	float currentFrame = (float)glfwGetTime();
	
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


	GLint model = glGetUniformLocation(shaderProgram, "modelMatrix");
	GLint view = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint perspective = glGetUniformLocation(shaderProgram, "perspectiveMatrix");

	glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(0.5,0.5,0.5));
	
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(scale));
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
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVEO);

	//initialize the program appropriate primitive to work on
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);

}


void Geometry3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}



void Geometry3D::OnMouseMove(double xpos, double ypos)
{

	if (cameraFlag == false)
	{
		//do nothing
	}
	else
	{
		cam.mouseMove(xpos, ypos);
	}

}


void Geometry3D::OnCKeyPressed()
{
	if (cameraFlag == false)
	{
		cameraFlag = true;
	}
	else
	{
		cameraFlag = false;
	}
}