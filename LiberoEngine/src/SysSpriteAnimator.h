#pragma once
#include "System.h"

namespace Libero
{
	class SysSpriteAnimator : public System<SysSpriteAnimator>
	{
	public:
		SysSpriteAnimator();
		virtual void Update(float dt) override;

	private:
		void UpdateSprites(float dt);

	};
}


