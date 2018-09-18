#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "BlockRenderer.h"
#include "Camera.h"




float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool endApp = false;


const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 800;

const glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCREENWIDTH / SCREENHEIGHT, 0.1f, 100.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			endApp = true;
	}
		
		

}

int main(void)
{
		glm::mat4 view(1.0f);


		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		
		glfwSetWindowSizeCallback(window, framebuffer_size_callback);

		


		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Error!" << std::endl;
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);

		std::cout << glGetString(GL_VERSION);




		unsigned int indices[] = {
			0,1,3,
			1,2,3
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		glEnable(GL_DEPTH_TEST);

		
		
		//RENDERINGSCOPE------------------------------------------------------------------------------------------------------
		{
			Renderer renderer(proj, &view);
			BlockRenderer r(renderer);
			Camera cam(window);
			/* Loop until the user closes the window */
			
			
			
			while (!glfwWindowShouldClose(window) && !endApp)
			{
				processInput(window);
				view = cam.getView(deltaTime);


				std::cout << 1/deltaTime << std::endl;

				float currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;

				if(endApp)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				int d = 8;

				for (size_t x = 0; x < d; x++)
				{
					for (size_t y = 0; y < d; y++)
					{
						for (size_t z = 0; z < d; z++)
						{
								r.drawBlock(x, y, z);
						}
						
					}
				}

				r.drawBlock(0, 0, 0);
				r.drawBlock(1, 0, 0);
				r.drawBlock(2, 1, 0);
				r.drawBlock(3, 2, 0);
				r.drawBlock(4, 3, 0);

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();
			}
		}
	
	glfwTerminate();
	return 0;
}
