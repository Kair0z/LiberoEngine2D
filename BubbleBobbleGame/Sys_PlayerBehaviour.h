#pragma once
#include <System.h>

class Sys_PlayerBehaviour : public Libero::System<Sys_PlayerBehaviour>
{
public:
	Sys_PlayerBehaviour();
	virtual void Update(float dt) override;
};

