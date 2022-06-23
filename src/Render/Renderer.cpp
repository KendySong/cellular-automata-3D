#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window, unsigned int width, unsigned int height)
{
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);	
	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	float vertices[]
	{
		//Front
		 0.5,  0.5, -0.5,	//Top right
		-0.5,  0.5, -0.5,	//Top left
		-0.5, -0.5, -0.5,	//Bot left
		 0.5, -0.5, -0.5,	//Bot right

		//Back
		 0.5,  0.5,  0.5,
		-0.5,  0.5,  0.5,
		-0.5, -0.5,  0.5,
		 0.5, -0.5,  0.5
	};

	unsigned int indices[]
	{
		//Front
		0, 1, 3,
		1, 2, 3,

		//Back
		7, 6, 4,
		6, 5, 4,

		//Right
		4, 7, 0,
		7, 1, 0,

		//Left
		3, 2, 5,
		2, 6, 5,

		//Top
		4, 0, 5,
		0, 3, 5,

		//Bot
		7, 1, 2,
		1, 6, 2
	};


}

void Renderer::RenderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}