#pragma once
#include "IWindowImGui.h"
#include "CoreSettings.h"

namespace Libero
{
	class ResourcesWindowImGui : public IWindowImGui
	{
	public:
		ResourcesWindowImGui()
		{
			float x = (float)CoreSettings::m_GameDimensions.x;
			//float y = (float)s.m_GameDimensions[1];

			float totX = (float)CoreSettings::m_ApplicationDimensions[0];
			//float totY = (float)s.m_ApplicationDimensions[1];

			float midX = totX / 2.f;

			SetPos({0.f, 720.f});
			SetSize({ midX - x / 2.f, 1040 - 720});
		}
		~ResourcesWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:


	public:
		ROFDEL(ResourcesWindowImGui)

	};
}


