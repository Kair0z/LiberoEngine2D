#pragma once
#include "ICharacterState.h"

using namespace Libero;

class EnemyComponent : public Libero::Component<EnemyComponent>
{
public:
	EnemyComponent(const Libero::Rectf& bounds);
	~EnemyComponent();
	DefGetSet(Libero::Rectf, m_BoundsToWalk, Bounds);
	DefGetSet(bool, m_IsBubbled, IsBubbled);
	DefGetSet(bool, m_IsPopped, IsPopped);

	ICharacterState* GetState();
	void SetNewState(ICharacterState* pNewState);

private:
	Libero::Rectf m_BoundsToWalk;
	bool m_IsBubbled;
	bool m_IsPopped;

	ICharacterState* m_pEnemyState;
};


class EnemyIdleState : public ICharacterState
{
public:
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) { return nullptr; }
	ICharacterState* Update(float dt, CharacterComponent*) override;

private:
	float m_ChangeTime = 1.f;
	float m_ChangeTimer = 0.f;
	float m_Movement = 0.5f;

	float m_JumpTime = 3.f;
	float m_JumpTimer = 0.f;
};

class EnemyBubbledState : public ICharacterState
{
public:
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) { return nullptr; }
	ICharacterState* Update(float dt, CharacterComponent*) override;

private:
	float m_BubbledTime = 5.f;
	float m_BubbledTimer = 0.f;

	float m_BubbledSpeed = 10.f;
};

class EnemyJumpState : public ICharacterState
{
public:
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) { return nullptr; }
	ICharacterState* Update(float dt, CharacterComponent*) override;

private:
	float m_JumpTimer = 0.f;
	float m_JumpTime = 1.f;
};

class EnemyPoppedState : public ICharacterState
{
public:
	void OnEnter(CharacterComponent* pCharacter) override;
	ICharacterState* ProcessInput(CharacterComponent*, InputComponent*) { return nullptr; };
	ICharacterState* Update(float dt, CharacterComponent*) override;
};




