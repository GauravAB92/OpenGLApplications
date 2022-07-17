#pragma once

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/geometric.hpp"
#include "GLFW/glfw3.h"

class Camera
{
public:

	Camera() : 
		cameraPos(0.0f, 0.0f , 3.0f),
		cameraTarget(0.0f, 0.0f, -1.0f), 
		cameraUp(0.0f, 1.0f, 0.0f), 
		yaw(-90.0f), pitch(0.0f), roll(0.0f),
		direction(0.0f, 0.0f, 0.0f),
		cameraMovementAmplitude(2.5f)
	{
		lastX = 1000;
		lastY = 600;
	}

	~Camera() = default;

	//camera member funcs
	glm::mat4 viewTransform();
	glm::mat4 perspectiveTransform(int w, int h);

	void updateCamera(GLFWwindow* window, float deltaTime);
	void mouseMove(double x, double y);
	


	//basis precursors
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	//angular movement
	glm::vec3 direction;
	//euler angles
	float yaw;
	float pitch;
	float roll;
	float lastX;
	float lastY;

	//vertical field of view
	float fovy = 45.0f;

	//camera response time
	float cameraMovementAmplitude;
};
