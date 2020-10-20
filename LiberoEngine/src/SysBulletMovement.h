#pragma once
#include "System.h"

namespace Libero
{
	class SysBulletMovement : public System<SysBulletMovement>
	{
	public:
		SysBulletMovement() = default;
		virtual ~SysBulletMovement() = default;

		virtual void Update(float dt) override;

	private:

	};
}


