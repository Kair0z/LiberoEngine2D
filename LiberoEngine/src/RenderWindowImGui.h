#pragma once
#include "IWindowImGui.h"

namespace Libero
{
	class RenderWindowImGui : public IWindowImGui
	{
	public:
		RenderWindowImGui() = default;
		~RenderWindowImGui() = default;

		virtual void ProcessInput() override;
		virtual void RenderToImGui() const override;

	private:

	public:
		ROFDEL(RenderWindowImGui)
	};
}


