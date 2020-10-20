#include "PCH.h"
#include "LoggerWindowImGui.h"
#include "Logger.h"

namespace Libero
{
	void LoggerWindowImGui::ProcessInput()
	{
	}

	void LoggerWindowImGui::RenderToImGui() const
	{
		if (m_OpenForEdit) ImGui::Begin("Log", nullptr);
		else
		{
			ImGui::SetNextWindowPos(m_Pos);
			ImGui::SetNextWindowSize(m_Size);
			ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		}

		Logger* pLogger = LoggerLocator::Locate();
		if (pLogger)
		{
			const std::vector<std::string>& buffer = pLogger->GetLogBuffer();
			for (auto it = buffer.rbegin(); it != buffer.rend(); ++it)
			{
				ImGui::TextUnformatted(it->c_str());
			}
		}

		ImGui::End();
	}
}