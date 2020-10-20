#include "Sys_PlayerBehaviour.h"
#include "PlayerState.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "CharacterComponent.h"
#include "SpawnComponent.h"
#include "SceneManager.h"
#include "EventMaster.h"
#include "MiscEvent.h"
#include "TransformComponent.h"

using namespace Libero;

Sys_PlayerBehaviour::Sys_PlayerBehaviour()
{
	m_UpdateInterval = 0.01f;
}

void Sys_PlayerBehaviour::Update(float dt)
{
	ForEachComponent<PlayerComponent>([dt](PlayerComponent* pPlayer)
		{
			IEntity* pEntity = pPlayer->GetOwnerEntity();
			if (!pEntity) return;

			RigidbodyComponent* pBody = pEntity->GetComponent<RigidbodyComponent>();
			if (!pBody) return;

			CharacterComponent* pCharacter = pEntity->GetComponent<CharacterComponent>();
			if (!pCharacter) return;

			InputComponent* pInput = pEntity->GetComponent<InputComponent>();

			// Horizontal Movement
			float power = 3.f;
			if (pInput->IsKeyDown(SDLK_RIGHT) && pCharacter->GetIsGrounded())
			{
				pCharacter->SetFaceDirection(CharacterComponent::FaceDirection::RIGHT);
				pBody->AddForce({ power, 0.f });
			}
			if (pInput->IsKeyDown(SDLK_LEFT) && pCharacter->GetIsGrounded())
			{
				pCharacter->SetFaceDirection(CharacterComponent::FaceDirection::LEFT);
				pBody->AddForce({ -power, 0.f });
			}

			ICharacterState* pCurrentState = pPlayer->GetState();
			if (pCurrentState)
			{
				// Update state:
				ICharacterState* pNewState = pPlayer->GetState()->Update(dt, pCharacter);
				if (pNewState)
				{
					pPlayer->SetNewState(pNewState);
					pNewState->OnEnter(pCharacter);
				}

				// Process Input state:
				if (pInput) pNewState = pPlayer->GetState()->ProcessInput(pCharacter, pInput);
				if (pNewState)
				{
					pPlayer->SetNewState(pNewState);
					pNewState->OnEnter(pCharacter);
				}
			}
		});
}