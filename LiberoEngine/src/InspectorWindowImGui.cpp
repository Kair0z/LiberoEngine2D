#include "PCH.h"
#include "InspectorWindowImGui.h"

namespace Libero
{
	void InspectorWindowImGui::ProcessInput()
	{
	}

	void InspectorWindowImGui::RenderToImGui() const
	{
		if (m_OpenForEdit) ImGui::Begin("Inspector", nullptr);
		else
		{
			ImGui::SetNextWindowPos(m_Pos);
			ImGui::SetNextWindowSize(m_Size);
			ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		}

		ImGui::End();
	}
}