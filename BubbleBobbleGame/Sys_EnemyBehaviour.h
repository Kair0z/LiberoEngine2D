#pragma once
#include <System.h>

class Sys_EnemyBehaviour : public Libero::System<Sys_EnemyBehaviour>
{
public:
	Sys_EnemyBehaviour();
	virtual void Update(float dt) override;
};

