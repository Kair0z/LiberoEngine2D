#pragma once
#include "IWindowImGui.h"
#include "CoreSettings.h"

namespace Libero
{
	class HierarchyWindowImGui : public IWindowImGui
	{
	public:
		HierarchyWindowImGui()
		{
			float x = (float)CoreSettings::m_GameDimensions.x;
			//float y = (float)s.m_GameDimensions[1];

			float totX = (float)CoreSettings::m_ApplicationDimensions.x;
			//float totY = (float)s.m_ApplicationDimensions[1];

			float midX = totX / 2.f;

			SetPos({0.0f, 20.0f});

			SetSize({midX - x / 2.f, 700.f});
		}

		~HierarchyWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:


	public:
		ROFDEL(HierarchyWindowImGui)
	};
}


