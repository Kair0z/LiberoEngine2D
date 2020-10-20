#include "PCH.h"
#include "HierarchyWindowImGui.h"

#include "SceneManager.h"
#include "LiberoScene.h"
#include "GameObject.h"
#include "Logger.h"

namespace Libero
{
	void HierarchyWindowImGui::ProcessInput()
	{
	}

	void HierarchyWindowImGui::RenderToImGui() const
	{
		// Begin window:
		if (m_OpenForEdit) ImGui::Begin("Hierarchy", nullptr);
		else
		{
			ImGui::SetNextWindowPos(m_Pos);
			ImGui::SetNextWindowSize(m_Size);
			ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		}

		// Get Scenemaster:
		LiberoSceneMaster* pSceneMaster = SceneMasterLocator::Locate();
		if (!pSceneMaster)
		{
			LoggerLocator::Locate()->LogWarning("HierarchyWindowImGui: While rendering, couldn't find a SceneMaster!");
			ImGui::End();
			return;
		}

		if (pSceneMaster->IsEmpty())
		{
			ImGui::End();
			return;
		}

		LiberoScene* pCurrentScene = pSceneMaster->GetActiveScene();

		bool h = ImGui::CollapsingHeader(pCurrentScene->GetName().c_str());
		if (ImGui::BeginPopupContextItem("* Game Scene *"))
		{
			if (ImGui::Selectable("* Create GameObject * ")) pCurrentScene->AddGameObject();
			ImGui::EndPopup();
		}
		
		if (h)
		{
			for (size_t i{}; i < pCurrentScene->GetObjects().size(); ++i)
			{
				GameObject* pGameObject = pCurrentScene->GetObjects()[i];

				if (ImGui::TreeNode(pGameObject->Getname().c_str()))
				{
					if (ImGui::BeginPopupContextItem("* Game Scene *"))
					{
						std::string fullString = "* Delete " + pGameObject->Getname() + " * ";
						if (ImGui::Selectable(fullString.c_str())) pCurrentScene->DestroyGameObject(pGameObject);

						ImGui::EndPopup();
					}
					ImGui::TreePop();
				}
			}
		}

		ImGui::End();
	}
}