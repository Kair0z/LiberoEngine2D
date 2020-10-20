#include "Sys_FPSCounter.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Logger.h"
#include <sstream>
#include <iomanip>

using namespace Libero;

Sys_FPSCounter::Sys_FPSCounter()
{
	m_UpdateInterval = 2.f;
}

void Sys_FPSCounter::Update(float dt)
{
	ForEachComponent<FPSComponent>([=](FPSComponent* pFPS)
		{
			// Set time since last frame:
			pFPS->SetTimeSinceLastFrame(dt);

			IEntity* pOwner = pFPS->GetOwnerEntity();
			if (!pOwner) return;

			std::stringstream ss;
			ss << "FPS: " << std::fixed << std::setprecision(2) << (1.f / pFPS->GetTimeSinceLastFrame());
			LoggerLocator::Locate()->LogInfo(ss.str());

			TextComponent* pText = pOwner->GetComponent<TextComponent>();
			// Get the TextComponent of the owner (if existing) & set it appropriately):
			if (pText) pText->SetText(ss.str());
		});
}
