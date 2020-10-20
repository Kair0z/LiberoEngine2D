#pragma once
#include <System.h>
#include "System.h"

class Sys_FPSCounter final : public Libero::System<Sys_FPSCounter>
{
public:
	Sys_FPSCounter();
	void Update(float dt) override;

private:
	
};

