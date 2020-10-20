#include "Sys_EnemyBehaviour.h"
#include "LiberoRenderer_SDL.h"

#include "EnemyState.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"

using namespace Libero;

Sys_EnemyBehaviour::Sys_EnemyBehaviour()
{
}

void Sys_EnemyBehaviour::Update(float dt)
{
	ForEachComponent<EnemyComponent>([=](EnemyComponent* pEnemy)
		{
			IEntity* pEntity = pEnemy->GetOwnerEntity();
			if (!pEntity) return;

			RigidbodyComponent* pBody = pEntity->GetComponent<RigidbodyComponent>();
			if (!pBody) return;

			CharacterComponent* pCharacter = pEntity->GetComponent<CharacterComponent>();
			if (!pCharacter) return;

			ICharacterState* pCurrentState = pEnemy->GetState();
			if (pCurrentState)
			{
				ICharacterState* pNewState = pCurrentState->Update(dt, pCharacter);
				if (pNewState)
				{
					pEnemy->SetNewState(pNewState);
					pNewState->OnEnter(pCharacter);
				}

				// Enemies don't process Input:
				// ICharacterState* pNewState2 = pCurrentState->ProcessInput();
			}
		});
}
