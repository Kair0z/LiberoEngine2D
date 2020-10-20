#include "PCH.h"
#include "TopMenuImGui.h"
#include "LiberoCore.h"

namespace Libero
{
	void TopMenuImGui::Render() const
	{
		ImGui::BeginMainMenuBar();

		if (ImGui::MenuItem("Libero", nullptr, nullptr, true))
		{
			
		}
	}

	void TopMenuImGui::End() const
	{
		ImGui::EndMainMenuBar();
	}
}

