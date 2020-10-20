#include "PCH.h"
#include "ResourcesWindowImGui.h"

namespace Libero
{
	void ResourcesWindowImGui::ProcessInput()
	{

	}

	void ResourcesWindowImGui::RenderToImGui() const
	{
		if (m_OpenForEdit) ImGui::Begin("Resources", nullptr);
		else
		{
			ImGui::SetNextWindowPos(m_Pos);
			ImGui::SetNextWindowSize(m_Size);
			ImGui::Begin("Resources", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		}


		ImGui::End();
	}
}