#pragma once
#include "IWindowImGui.h"
#include "Logger.h"
#include "CoreSettings.h"

namespace Libero
{
	class LoggerWindowImGui : public IWindowImGui
	{
	public:
		LoggerWindowImGui()
		{
			float x = (float)CoreSettings::m_GameDimensions.x;
			//float y = (float)s.m_GameDimensions[1];

			float totX = (float)CoreSettings::m_ApplicationDimensions.x;
			//float totY = (float)s.m_ApplicationDimensions[1];

			float midX = totX / 2.f;

			float posX = midX - x / 2.f;

			// - inspectorwindowwidth
			float inspectorWidth = (totX - (midX + x / 2.f));
			SetSize({totX - inspectorWidth - posX, 400.f});
			SetPos({posX, 720.f});
		}
		~LoggerWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:

	public:
		ROFDEL(LoggerWindowImGui)
	};
}


