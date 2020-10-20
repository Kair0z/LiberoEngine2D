#include "PCH.h"
#include "PhysicsMaster.h"

namespace Libero
{
	PhysicsMaster::PhysicsMaster()
		: m_pB2DWorld{nullptr}
	{

	}

	PhysicsMaster::~PhysicsMaster()
	{
		delete m_pB2DWorld;
		m_pB2DWorld = nullptr;
	}

	void PhysicsMaster::Initialize()
	{
		b2Vec2 gravity{ 0.f, -9.81f };
		m_pB2DWorld = new b2World{gravity};

		m_IsInitialized = true;
	}

	void PhysicsMaster::Update(float dt)
	{
		m_pB2DWorld->Step(dt, 8, 3);
	}

	b2Body* PhysicsMaster::CreateBody(const b2BodyDef& bodyDef)
	{
		b2Body* pBody = m_pB2DWorld->CreateBody(&bodyDef);

		return pBody;
	}

	void PhysicsMaster::DestroyBody(b2Body* pBody)
	{
		if (!pBody) return;

		m_pB2DWorld->DestroyBody(pBody);
	}
}

