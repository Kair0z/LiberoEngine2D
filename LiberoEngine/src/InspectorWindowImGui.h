#pragma once
#include "IWindowImGui.h"
#include "LiberoMacros.h"
#include "CoreSettings.h"

namespace Libero
{
	class InspectorWindowImGui : public IWindowImGui
	{
	public:
		InspectorWindowImGui()
		{
			float x = (float)CoreSettings::m_GameDimensions.x;
			//float y = (float)s.m_GameDimensions[1];

			float totX = (float)CoreSettings::m_ApplicationDimensions.x;
			float totY = (float)CoreSettings::m_ApplicationDimensions.y;

			float midX = totX / 2.f;

			float posX = (midX + x / 2.f);

			SetPos({posX, 20.f });
			SetSize({(totX - posX), totY});
		}
		~InspectorWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:

	public:
		ROFDEL(InspectorWindowImGui)
	};
}


