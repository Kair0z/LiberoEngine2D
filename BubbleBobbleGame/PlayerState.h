#pragma once
#include "Component.h"
#include "ICharacterState.h"

using namespace Libero;

class PlayerComponent : public Component<PlayerComponent>
{
public:
	PlayerComponent();
	~PlayerComponent();

	ICharacterState* GetState();
	void SetNewState(ICharacterState* pNewState);

private:
	ICharacterState* m_pPlayerState;
};



class PlayerIdleState : public ICharacterState
{
public:
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent* pCharacter, InputComponent* pInput) override;
	ICharacterState* Update(float, CharacterComponent*) override { return nullptr; }
};

class PlayerShootingState : public ICharacterState
{	
public:
	PlayerShootingState(float time = 0.5f, float shootingSpeed = 400.f, float bubbleLifetime = 0.5f);
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) override { return nullptr; };
	ICharacterState* Update(float dt, CharacterComponent* pCharacter) override;

private:
	float m_ShootingTime;
	float m_ShootingTimer;

	float m_ShootingSpeed;
	float m_BubbleLifetime;

	void InitializeBubble(Libero::GameObject* pBubble, float xSpeed);
};

class PlayerJumpState : public ICharacterState
{
public:
	PlayerJumpState(float jumpTime = 0.5f);
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) override { return nullptr; };
	ICharacterState* Update(float dt, CharacterComponent* pCharacter) override;

private:
	float m_JumpTime = 0.1f;
	float m_JumpTimer = 0.f;
};



