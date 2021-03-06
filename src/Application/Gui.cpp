#include "Gui.h"
#include "Gui.h"

Gui::Gui(GLFWwindow* window)
{
	_fps = 0;
	_wireframe = false;
	_faceCulling = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	
	//Opengl and Gpu data
	const GLubyte* gpuName = glGetString(GL_RENDERER);
	const GLubyte* versionName = glGetString(GL_VERSION);
	for (size_t i = 0; i < 50; i++)
	{
		gpu += gpuName[i];
		version += versionName[i];
	}

	ApplySettings();
}

void Gui::CreateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::DisplayRenderData()
{
	_fps++;
	ImGui::Begin("Render");

	ImGui::Text(gpu.c_str());
	ImGui::Text(version.c_str());

	//FPS
	if (_timer.GetElapsedTime() >= 1)
	{
		_framerate = std::to_string(_fps) + " fps";
		_fps = 0;
		_timer.Restart();
	}
	ImGui::Text(_framerate.c_str());

	//Render mode
	ImGui::Checkbox("Wireframe Render", &_wireframe);
	ImGui::Checkbox("Face culling", &_faceCulling);

	if (ImGui::Button("Apply"))	
		ApplySettings();	

	ImGui::End();
}

void Gui::ApplySettings() 
{
	if (_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (_faceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void Gui::ManageSimulationSettings(float& tick, int nbBLocks) 
{
	ImGui::Begin("Simulation");
	ImGui::SliderFloat("Tick", &tick, 0.01f, 1);
	ImGui::InputInt("Number of cells", &nbBLocks);
	ImGui::End();
}

void Gui::ManageCamera(Camera& camera)
{
	ImGui::Begin("Camera");
	float cameraPos[]{ camera.position.x, camera.position.y ,camera.position.z };
	ImGui::InputFloat3("Camera position", cameraPos);
	ImGui::SliderFloat("Speed", &camera.speed, 1, 100);
	ImGui::End();
}

void Gui::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}