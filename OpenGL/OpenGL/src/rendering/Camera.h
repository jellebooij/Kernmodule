#pragma once
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class Camera {

private:
	GLFWwindow* window;

public:
	Camera(GLFWwindow* window);
	glm::mat4 getView(const float& deltaTime);

};