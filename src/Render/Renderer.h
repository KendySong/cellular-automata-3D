///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Render each frame

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "../Application/Gui.h"
#include "../Application/Timer.h"

#pragma once
class Renderer
{
	//Attributes and properties
private :
	GLFWwindow* _window;
	Shader* _shader;
	Camera* _camera;
	Gui* _gui;

	Timer _timer;

public :
	Renderer(GLFWwindow* window, unsigned int width, unsigned int height);
	~Renderer();

	void LoadShaders();

	void UpdateFrame();

	void RenderFrame();
};