#pragma once
#include "LiberoMacros.h"
#include "LiberoMath.h"
#include "TopMenuImGui.h"
#include "ILiberoLocator.h"
#include <unordered_map>

struct SDL_Renderer;
struct ImGuiIO;

namespace Libero
{
	class IWindowImGui;
	class ImmediateUI 
	{
	public:
		ImmediateUI();
		~ImmediateUI();

		virtual void Initialize(SDL_Renderer* pSDLRenderer, const Vector2ui& windowDim); // Takes in a window
		virtual void Render() const; 
		virtual void ProcessInput();
		virtual bool IsFocussedOnUI() const;

	private:
		ImGuiIO* m_pIO;
		void InitWindows();
		void Cleanup();

		std::unordered_map<std::string, IWindowImGui*> m_pWindows;
		TopMenuImGui m_TopMenu;

	public:
		ROFDEL(ImmediateUI)

	public:
		
	};

	class UILocator : public ILiberoLocator<ImmediateUI>{};
}


