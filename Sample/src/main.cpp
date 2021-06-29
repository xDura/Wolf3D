#include "wf_pch.h"
#include <iostream>
#include "sdl_window.h"
#include "wf_debug.h"

bool show_demo_window = true;
bool close = false;

int main(int argc, char* argv[])
{
    std::cout << "HELLO WORLD" << std::endl;
    Wolf::SDL_WINDOW* window = new Wolf::SDL_WINDOW("Wolf3D", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window->sdl_window);
	WF_ASSERT(false, "a");
	WF_ASSERT_ALWAYS(false, "b");

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		WF_LOGERROR("Failed initializing GLAD opengl context");
		return -1;
	}
	int interval = SDL_GL_SetSwapInterval(0);

	int windowWidth, windowHeight;
	SDL_GetWindowSize(window->sdl_window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	//IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui_ImplSDL2_InitForOpenGL(window->sdl_window, glcontext);
	ImGui_ImplOpenGL3_Init();

	while (!close) 
	{
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt) != 0)
		{
			ImGui_ImplSDL2_ProcessEvent(&evnt);
			if (evnt.type == SDL_QUIT) close = true;
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window->sdl_window);
		ImGui::NewFrame();
		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Render();
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window->sdl_window);
	}

	SDL_GL_DeleteContext(glcontext);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
    delete(window);
    return 0;
}