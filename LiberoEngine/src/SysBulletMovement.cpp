#include "PCH.h"
#include "SysBulletMovement.h"

#include "BulletComponent.h"
#include "TransformComponent.h"

#include "SceneManager.h"

namespace Libero
{
	void SysBulletMovement::Update(float dt)
	{
		ForEachComponent<BulletComponent>([=](BulletComponent* pBullet)
			{
				IEntity* pOwner = pBullet->GetOwnerEntity();
				if (!pOwner) return;

				Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
				if (!pTransform) return;

				// Move Along velocity
				pTransform->Translate(pBullet->GetInitVelocity() * dt);

				// Increase lifetimer:
				pBullet->ProgressLife(dt);

				if (pBullet->IsExpired()) pBullet->SetActive(false);
			});
	}
}

