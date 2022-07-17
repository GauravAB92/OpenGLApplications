#include "Camera.h"
#include <iostream>

glm::mat4 Camera::viewTransform()
{
	return glm::lookAt(cameraPos, cameraPos + cameraTarget, cameraUp);
}

glm::mat4 Camera::perspectiveTransform(int windowWidth, int windowHeight)
{
	return glm::perspectiveFov(45.0f, (float)windowWidth, (float)windowHeight, 1.0f, 1000.0f);

}


void Camera::updateCamera(GLFWwindow* window, float deltaTime)
{

	float cameraSpeed = cameraMovementAmplitude * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraTarget;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraTarget;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraTarget, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraTarget, cameraUp)) * cameraSpeed;

}

void Camera:: mouseMove(double x, double y)
{
	float xoffset = (float)(x - lastX);
	float yoffset = float(lastY - y);
	lastX = (float)x;
	lastY = (float)y;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	yaw += xoffset;
	pitch += yoffset;
	
	if (pitch > 89.0f)
	pitch = 89.0f;
	
	if (pitch < -89.0f)
		pitch = -89.0f;
	
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	cameraTarget = glm::normalize(direction);

}

