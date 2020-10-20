#include "PCH.h"
#include "IWindowImGui.h"

namespace Libero
{
	void IWindowImGui::SetEditable(const bool editable)
	{
		m_OpenForEdit = editable;
	}

	void IWindowImGui::SetSize(const ImVec2& size)
	{
		m_Size = size;
	}

	ImVec2 IWindowImGui::GetSize() const
	{
		return m_Size;
	}

	void IWindowImGui::SetPos(const ImVec2& pos)
	{
		m_Pos = pos;
	}

	ImVec2 IWindowImGui::GetPos() const
	{
		return m_Pos;
	}
}

