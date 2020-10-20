#include "PCH.h"
#include "PlayWindowImGui.h"
#include "LiberoCore.h"
#include "EventMaster.h"
#include "MiscEvent.h"

namespace Libero
{
	void PlayWindowImGui::ProcessInput()
	{

	}

	void PlayWindowImGui::RenderToImGui() const
	{
		if (m_OpenForEdit) ImGui::Begin("Game", nullptr);
		else
		{
			ImGui::SetNextWindowPos(m_Pos);
			ImGui::SetNextWindowSize(m_Size);
			ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		}

		ImGui::Indent(250.f);

		if (ImGui::Button("Play", { 100, 30 })) EventMasterLocator::Locate()->AddToQueue<GamePlayEvent>();

		ImGui::SameLine();
		if (ImGui::Button("Stop", { 100, 30 })) EventMasterLocator::Locate()->AddToQueue<GameStopEvent>();
		ImGui::End();
	}
}

