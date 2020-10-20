#include "PCH.h"
#include "SysPhysics.h"
#include "PhysicsMaster.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsMaster.h"
#include <sstream>

namespace Libero
{
	SysPhysics::SysPhysics()
	{
		m_IsEnabled = true;
		m_UpdateInterval = 0.0001f;
	}

	void SysPhysics::Start()
	{
		bool needsPhysics = false;
		ForEachComponent<RigidbodyComponent>([&needsPhysics](RigidbodyComponent* pRigidbody)
			{
				needsPhysics = true;
				IEntity* pOwner = pRigidbody->GetOwnerEntity();

				// Attach to collider:
				if (pOwner && pOwner->HasComponent<Collider2DComponent>())
				{
					Collider2DComponent* pCollider = pOwner->GetComponent<Collider2DComponent>();

					if (pCollider)
					{
						pRigidbody->AttachCollider(pCollider);
					}
				}

				// Set pos to Transform:
				if (pOwner && pOwner->HasComponent<Transform2DComponent>())
				{
					Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();

					if (pTransform)
					{
						// Align the rigidbody with the start-transform
						pRigidbody->GetB2DBody()->SetTransform({ 
							Physics::ScaleToBox2D(pTransform->GetPosition().x),
							Physics::ScaleToBox2D(pTransform->GetPosition().y) },
							pTransform->GetRotation());
					}
				}

			});

		m_DoesNeedUpdate = needsPhysics;
	}

	void SysPhysics::Update(float dt)
	{
		ForEachComponent<RigidbodyComponent>([=](RigidbodyComponent* pRigidBody)
			{
				Vector2f forceSum = pRigidBody->GetForceSum();

				if (!pRigidBody->IsSimulated()) return;

				IEntity* pOwner = pRigidBody->GetOwnerEntity();
				if (pOwner && pOwner->HasComponent<Transform2DComponent>())
				{
					Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();

					// Move the transform with the rigidbody:
					pTransform->SetPosition({
						Physics::ScaleToWorld(pRigidBody->GetB2DBody()->GetPosition().x),
						Physics::ScaleToWorld(pRigidBody->GetB2DBody()->GetPosition().y) });
					pTransform->SetRotation({ pRigidBody->GetB2DBody()->GetAngle() });
				}

				if (forceSum.IsZero()) return;
				

				// apply sum of forces:
				pRigidBody->GetB2DBody()->ApplyForceToCenter({ forceSum.x, forceSum.y }, true);
				// Reset forcesum:
				pRigidBody->SetForceSum({});
			});

		PhysicsMasterLocator::Locate()->Update(dt);
	}
}

