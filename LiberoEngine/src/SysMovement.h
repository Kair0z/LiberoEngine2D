#pragma once
#include "System.h"

namespace Libero
{
	class CharacterComponent;

	class SysMovement : public System<SysMovement>
	{
	public:
		SysMovement();
		virtual void PreUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;

	private:
		void MoveCharacters(float dt);
		void CheckIfGrounded(CharacterComponent* pCharacter);
	};
}


