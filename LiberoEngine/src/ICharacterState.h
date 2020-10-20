#pragma once

#include "CharacterComponent.h"
#include "InputComponent.h"

namespace Libero
{
	class GameObject;
	class IState
	{
	public:
		virtual ~IState() = default;
		virtual void OnEnter(GameObject* pObj) = 0;
		virtual IState* ProcessInput(GameObject* pObj, InputComponent* pInput) = 0;
		virtual IState* Update(float dt, GameObject* pObj) = 0;
	};

	class ICharacterState
	{
	public:
		virtual ~ICharacterState() = default;
		virtual void OnEnter(CharacterComponent* pCharacter) = 0;
		virtual ICharacterState* ProcessInput(CharacterComponent* pCharacter, InputComponent* pInput) = 0;
		virtual ICharacterState* Update(float dt, CharacterComponent* pCharacter) = 0;
	};
}


