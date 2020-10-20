#pragma once
#include "Component.h"
#include "LiberoMacros.h"

namespace Libero
{
	class FPSComponent : public Component<FPSComponent>
	{
	public:
		DefGetSet(double, m_SecondsSincelastFrame, FPS);

	private:
		double m_SecondsSincelastFrame{};
	};
}

