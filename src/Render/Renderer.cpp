#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window, unsigned int width, unsigned int height)
{
	_nbBlocks = 0;
	_window = window;

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);	
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	LoadShaders();
	
	//Load camera
	_camera = new Camera(_window, (float)width, (float)height, 90, 0.1f, 1000, 0.3f, 10, glm::vec3(50, 50, 50));
	_camera->projectionLocation = glGetUniformLocation(_shader->GetProgram(), "projection");
	_camera->viewLocation = glGetUniformLocation(_shader->GetProgram(), "view");
	glUniformMatrix4fv(_camera->projectionLocation, 1, false, glm::value_ptr(_camera->projection));
		
	//Define cube vertices and indices
	float vertices[]
	{
		//Front
		-0.5, -0.5,  0.5,
		 0.5, -0.5,  0.5,
		 0.5,  0.5,  0.5,
		-0.5,  0.5,  0.5,

		//Back
		-0.5, -0.5, -0.5,
		 0.5, -0.5, -0.5,
		 0.5,  0.5, -0.5,
		-0.5,  0.5, -0.5
	};

	unsigned int indices[] 
	{
		//Front
		0, 1, 2,
		2, 3, 0,

		//Right
		1, 5, 6,
		6, 2, 1,

		//Back
		7, 6, 5,
		5, 4, 7,

		//Left
		4, 0, 3,
		3, 7, 4,

		//Bottom
		4, 5, 1,
		1, 0, 4,

		//Top
		3, 2, 6,
		6, 7, 3
	};

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	_gui = new Gui(window);
}

Renderer::~Renderer()
{
	delete _shader;
	delete _camera;
	delete _gui;
}

void Renderer::LoadShaders() 
{
	_shader = new Shader("shaders/block.vert", "shaders/block.frag");
	glUseProgram(_shader->GetProgram());
	_modelLocation = glGetUniformLocation(_shader->GetProgram(), "model");
}

void Renderer::UpdateFrame() 
{
	_world.Update();

	_camera->ProcessMovement(_window, (float)_timer.GetElapsedTime());
	glUniformMatrix4fv(_camera->viewLocation, 1, false, glm::value_ptr(_camera->view));
	_timer.Restart();
}

void Renderer::RenderFrame()
{
	_nbBlocks = _world.cellsPosition.size();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_gui->CreateFrame();

	for (size_t i = 0; i < _nbBlocks; i++)
	{
		glUniformMatrix4fv(_modelLocation, 1, false, glm::value_ptr(glm::translate(glm::mat4(1.0f), _world.cellsPosition[i])));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	_gui->DisplayRenderData();
	_gui->ManageCamera(*_camera);
	_gui->ManageSimulationSettings(_world.tick, _nbBlocks);
	_gui->Render();
}