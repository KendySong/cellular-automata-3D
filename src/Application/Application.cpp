#include "Application.h"

Application::Application(unsigned int width, unsigned int height, const char* title) 
{
	_width = width;
	_height = height;
	_title = title;

	//Init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(_window);

	//Init renderer
	_renderer = new Renderer(_window, width, height);
}

int Application::Run() 
{
	//Main loop
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();

		//Update


		//Render
		_renderer->RenderFrame();
		glfwSwapBuffers(_window);
	}

	glfwDestroyWindow(_window);
	return 0;
}

