#include "PCH.h"
#include "RenderWindowImGui.h"
#include "LiberoRenderer_SDL.h"
#include "imgui_sdl.h"

namespace Libero
{
	void RenderWindowImGui::ProcessInput()
	{

	}

	void RenderWindowImGui::RenderToImGui() const
	{
		if (m_OpenForEdit) ImGui::Begin("Renderer", nullptr);
		else ImGui::Begin("Renderer", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);


		ImGui::End();
	}
}
