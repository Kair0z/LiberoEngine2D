#include "Sys_LevelSwitch.h"
#include "EnemyState.h"
#include "EventMaster.h"
#include "MiscEvent.h"

void Sys_LevelSwitch::Update(float)
{
	bool enemyAlive{ false };
	bool enemyExists = false;

	ForEachComponent<EnemyComponent>([=, &enemyAlive, &enemyExists](EnemyComponent* pEnemy)
		{
			enemyExists = true;
			if (enemyAlive) return;

			if (!pEnemy->GetIsPopped()) enemyAlive = true;
		});
	
	if (!enemyAlive && enemyExists) EventMasterLocator::Locate()->AddToQueue<NextSceneEvent>(0);
}
