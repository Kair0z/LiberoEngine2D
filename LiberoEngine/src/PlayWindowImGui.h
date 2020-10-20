#pragma once
#include "IWindowImGui.h"
#include "CoreSettings.h"

namespace Libero
{
	class PlayWindowImGui : public IWindowImGui
	{
	public:
		PlayWindowImGui() 
		{
			m_Pos = { (float)CoreSettings::m_GameWindowTopLeft.x, 20.f };
			m_Size = { (float)CoreSettings::m_GameDimensions.x, 60.f };
		}

		virtual ~PlayWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:
		ROFDEL(PlayWindowImGui);
	};
}


