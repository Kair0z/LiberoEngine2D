#pragma once
#include "System.h"

class Sys_LevelSwitch : public Libero::System<Sys_LevelSwitch>
{
public:
	Sys_LevelSwitch() { m_UpdateInterval = 1.f; }
	void Update(float dt) override;
};

