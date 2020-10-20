#pragma once
#include "LiberoMacros.h"
#include "ILiberoLocator.h"

namespace Libero
{
	class PhysicsMaster final
	{
	public:
		PhysicsMaster();
		~PhysicsMaster();

		void Initialize();
		void Update(float dt);

		b2Body* CreateBody(const b2BodyDef& bodyDef);
		void DestroyBody(b2Body* pBody);
		
	private:
		bool m_IsInitialized;

		b2World* m_pB2DWorld;

		ROFDEL(PhysicsMaster);
	};

	namespace Physics
	{
		template <typename T>
		T ScaleToBox2D(const T& val) { return val / 16.f; }
		template <typename T>
		T ScaleToWorld(const T& val) { return val * 16.f; }
	}

	class PhysicsMasterLocator : public ILiberoLocator<PhysicsMaster>{};
}

