#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "World.h"
#include "User.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCR_WIDTH = 1350;
const unsigned int SCR_HEIGHT = 730;

bool firstMouse = true;
float lastX = 1140.0f / 2.0;
float lastY = 660.0f / 2.0;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));

	glm::mat4 projection = glm::perspective(glm::radians(55.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 4100.0f);

	World world(projection);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.update();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	glfwSetWindowShouldClose(window, true);

	User::moveCommand.x = 0;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) User::moveCommand.x += 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) User::moveCommand.x -= 1;

	User::moveCommand.z = 0;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) User::moveCommand.z += 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) User::moveCommand.z -= 1;

	User::runCommand = 0;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) User::runCommand = 1;

	User::moveCommand.y = 0;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) User::moveCommand.y = 1;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) User::attackCommand = 2;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) User::attackCommand = 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	User::mouseOffset.x = (float)xpos - lastX;
	User::mouseOffset.y = lastY - (float)ypos;
	lastX = (float)xpos;
	lastY = (float)ypos;
}