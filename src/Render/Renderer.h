///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Render each frame

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "../Application/Gui.h"
#include "../Application/Timer.h"
#include "../World/World.h"

#pragma once
class Renderer
{
	//Attributes and properties
private :
	Gui* _gui;
	GLFWwindow* _window;

	World _world;
	Camera* _camera;
	Timer _timer;

	Shader* _shader;
	int _modelLocation;

	int _nbBlocks;

public :
	Renderer(GLFWwindow* window, unsigned int width, unsigned int height);

	~Renderer();

	void LoadShaders();

	void UpdateFrame();

	void RenderFrame();
};