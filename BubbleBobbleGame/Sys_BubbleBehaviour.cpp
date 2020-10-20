#include "Sys_BubbleBehaviour.h"
#include "BubbleState.h"

void Sys_BubbleBehaviour::Update(float dt)
{
	ForEachComponent<BubbleStateComponent>([=](BubbleStateComponent* pBubbleState)
		{
			IEntity* pOwner = pBubbleState->GetOwnerEntity();
			if (!pOwner) return;

			// Update currentState:
			IState* pNewState = pBubbleState->GetState()->Update(dt, (GameObject*)pOwner);
			if (pNewState)
			{
				pBubbleState->SetNewState(pNewState);
				pNewState->OnEnter((GameObject*)pOwner);
			}

			// Process Input currentState:
			InputComponent* pInput = pOwner->GetComponent<InputComponent>();
			if (pInput) pNewState = pBubbleState->GetState()->ProcessInput((GameObject*)pOwner, pInput);
			if (pNewState)
			{
				pBubbleState->SetNewState(pNewState);
				pNewState->OnEnter((GameObject*)pOwner);
			}
		});
}
