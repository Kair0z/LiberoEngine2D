#pragma once
#include "System.h"

namespace Libero
{
	class SysPhysics : public System<SysPhysics>
	{
	public:
		SysPhysics();
		virtual void Start() override;
		virtual void Update(float dt) override;
	private:

	};
}


