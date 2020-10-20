#pragma once
#include "System.h"

class Sys_BubbleBehaviour : public Libero::System<Sys_BubbleBehaviour>
{
public:
	void Update(float dt) override;
};

