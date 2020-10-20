#pragma once
#include "ICharacterState.h"
#include "GameObject.h"
#include "LiberoMath.h"

using namespace Libero;

class BubbleStateComponent : public Libero::Component<BubbleStateComponent>
{
public:
	BubbleStateComponent();
	~BubbleStateComponent();

	DefGetSet(bool, m_BubbleActive, IsInUse);

	IState* GetState();
	void SetNewState(IState* pNewState);

private:
	IState* m_pBubbleState;
	bool m_BubbleActive;
};

class BubbleFlying : public Libero::IState
{
public:
	BubbleFlying(const Vector2f& vel, float lifetime = 3.f);
	virtual void OnEnter(GameObject* pObj) override;
	virtual IState* ProcessInput(GameObject*, InputComponent*) override { return nullptr; };
	virtual IState* Update(float dt, GameObject* pObj) override;

private:
	float m_Flytimer = 0.f;
	float m_Flytime = 3.f;

	Vector2f m_FlyVelocity{};
};

class BubbleFloating : public Libero::IState
{
public:
	BubbleFloating(float lifetime = 3.f, float floatPower = 50.f);
	virtual void OnEnter(GameObject*) override {};
	virtual IState* ProcessInput(GameObject*, InputComponent*) override { return nullptr; };
	virtual IState* Update(float dt, GameObject* pObj) override;

private:
	float m_FloatTime;
	float m_FloatTimer;
	float m_FloatPower;
};

class BubbleBurst : public Libero::IState
{
public:
	BubbleBurst() = default;

	virtual void OnEnter(GameObject* pObj) override;
	virtual IState* ProcessInput(GameObject*, InputComponent*) override { return nullptr; };
	virtual IState* Update(float, GameObject*) override { return nullptr; };
};
