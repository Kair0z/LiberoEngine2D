#include "PCH.h"
#include "ImmediateUI.h"
#include "imgui_sdl.h"
#include "ImGuiStyleLibrary.h"
#include "IWindowImGui.h"
#include "ImGuiPremadeWindows.h"
#include "Logger.h"

// Init & Destruction:
namespace Libero
{
	ImmediateUI::ImmediateUI()
		: m_pIO{nullptr}
	{

	}

	ImmediateUI::~ImmediateUI()
	{
		Cleanup();
	}

	void ImmediateUI::Initialize(SDL_Renderer* pSDLRenderer, const Vector2ui& windowDim)
	{
		ImGui::CreateContext();
		ImGuiSDL::Initialize(pSDLRenderer, (int)windowDim[0], (int)windowDim[1]);

		m_pIO = &ImGui::GetIO();

		ImGuiStyles::PurpleTheme();

		InitWindows();
	}

	void ImmediateUI::Cleanup()
	{
		for (auto pWindow : m_pWindows)
		{
			delete pWindow.second;
			pWindow.second = nullptr;
		}

		ImGuiSDL::Deinitialize();
		ImGui::DestroyContext();
	}
}

// Functionality:
namespace Libero
{
	void ImmediateUI::InitWindows()
	{
		m_pWindows["Hierarchy"] = new HierarchyWindowImGui{};
		m_pWindows["Logger"] = new LoggerWindowImGui{};
		m_pWindows["Inspector"] = new InspectorWindowImGui{};
		m_pWindows["Resources"] = new ResourcesWindowImGui{};
		m_pWindows["Play"] = new PlayWindowImGui{};

		for (auto pWindow : m_pWindows)
		{
			pWindow.second->SetEditable(false);
		}
	}

	void ImmediateUI::ProcessInput()
	{
		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		m_pIO->MousePos = ImVec2(float(mouseX), float(mouseY));
		m_pIO->MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		m_pIO->MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		for (auto pWindow : m_pWindows)
		{
			pWindow.second->ProcessInput();
		}
	}

	void ImmediateUI::Render() const
	{
		ImGui::NewFrame();

		m_TopMenu.Render();
		
		for (auto pWindow : m_pWindows) pWindow.second->RenderToImGui();

		ImGui::ShowDemoWindow();

		m_TopMenu.End();
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		ImGui::EndFrame();
	}

	bool ImmediateUI::IsFocussedOnUI() const
	{
		return false;
	}
}

