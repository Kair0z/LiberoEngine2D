#pragma once
#include "LiberoMacros.h"
#include "ImGui/imgui.h"

namespace Libero
{
	class IWindowImGui
	{
	public:
		virtual ~IWindowImGui() = default;

		virtual void ProcessInput() = 0;
		virtual void RenderToImGui() const = 0;

		void SetEditable(const bool editable);
		void SetSize(const ImVec2& size);
		ImVec2 GetSize() const;
		void SetPos(const ImVec2& pos);
		ImVec2 GetPos() const;

	protected:
		IWindowImGui() = default;
		bool m_OpenForEdit;
		ImVec2 m_Size;
		ImVec2 m_Pos;

	public:
		ROFDEL(IWindowImGui)
	};
}


