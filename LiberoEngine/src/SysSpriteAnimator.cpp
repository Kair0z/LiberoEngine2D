#include "PCH.h"
#include "SysSpriteAnimator.h"
#include "LiberoRenderer_SDL.h"
#include "SpriteComponent.h"

namespace Libero
{
	SysSpriteAnimator::SysSpriteAnimator()
	{
		m_IsEnabled = true;
		m_UpdateInterval = 0.001f;
	}

	void SysSpriteAnimator::Update(float dt)
	{
		UpdateSprites(dt);
	}

	void SysSpriteAnimator::UpdateSprites(float dt)
	{
		ForEachComponent<SpriteComponent>([&dt](SpriteComponent* pSprite)
			{
				if (!pSprite->GetShouldUpdate()) return;

				// Increase time:
				pSprite->SetTimeSinceLastFrame(pSprite->GetTimeSinceLastFrame() + dt);

				if (pSprite->GetTimeSinceLastFrame() > pSprite->GetFramesPerSecond())
				{
					pSprite->SetTimeSinceLastFrame(0.0f);

					if (pSprite->GetIsReversed()) pSprite->PreviousFrame();
					else pSprite->NextFrame();
				}
			});
	}
}

