#pragma once
#include <Component.h>
#include "LiberoMacros.h"

class FPSComponent final : public Libero::Component<FPSComponent>
{
public:
	DefGetSet(float, m_TimeSinceLastFrame, TimeSinceLastFrame);

private:
	float m_TimeSinceLastFrame = 0.0f;
};


