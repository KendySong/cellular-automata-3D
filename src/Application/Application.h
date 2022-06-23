///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Manage application running

#include "../Render/Renderer.h"

#include <glfw/glfw3.h>

#pragma once
class Application
{
	//Attributes and properties
private :
	unsigned int _width;
	unsigned int _height;
	const char* _title;

	GLFWwindow* _window;
	Renderer* _renderer;

public :
	Application(unsigned int width, unsigned int height, const char* title);

	int Run();
};