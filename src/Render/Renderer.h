///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Render each frame

#include <glad/glad.h>
#include <glfw/glfw3.h>

#pragma once
class Renderer
{
	//Attributes and properties
private :


public :
	Renderer(GLFWwindow* window, unsigned int width, unsigned int height);

	void RenderFrame();
};