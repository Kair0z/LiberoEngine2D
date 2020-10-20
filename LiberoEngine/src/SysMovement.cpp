#include "PCH.h"
#include "SysMovement.h"
#include "CharacterComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "LiberoMath.h"
#include "ColliderComponent.h"

namespace Libero
{
	SysMovement::SysMovement()
	{
		m_UpdateInterval = 0.01f;
	}

	void SysMovement::PreUpdate(float)
	{

	}

	void SysMovement::Update(float dt)
	{
		MoveCharacters(dt);
	}

	void SysMovement::PostUpdate(float)
	{
	}

	void SysMovement::MoveCharacters(float dt)
	{
		ForEachComponent<CharacterComponent>([=](CharacterComponent* pCharacter)
			{
				IEntity* pOwner = pCharacter->GetOwnerEntity();
				if (!pOwner) return;
				Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
				if (!pTransform) return;

				CheckIfGrounded(pCharacter);

				// Gravity
				if (!pCharacter->GetIsGrounded() && pCharacter->GetEnableGravity()) pCharacter->AddAcceleration({0.f, -800.f });

				Vector2f finalVelocity = { pCharacter->GetVelocity().x, pCharacter->GetVelocity().y + pCharacter->GetAcceleration().y * dt};
				pTransform->Translate(finalVelocity * dt);

				// Remember only the vertical velocity:
				pCharacter->SetVelocity({ 0.f, finalVelocity.y });
				pCharacter->SetAcceleration({});

				// Set Facing direction according to velocity:
				if (pCharacter->GetVelocity().x < 0.f) pCharacter->SetFaceDirection(CharacterComponent::FaceDirection::LEFT);
				else pCharacter->SetFaceDirection(CharacterComponent::FaceDirection::RIGHT);
			});
	}

	void SysMovement::CheckIfGrounded(CharacterComponent* pCharacter)
	{
		bool result = false;
		ForEachComponent<BoxCollider2DComponent>([=, &result](BoxCollider2DComponent* pBoxCollider)
			{
				if (pCharacter->GetOwnerEntity() == pBoxCollider->GetOwnerEntity()) return;

				if (result) return;
				IEntity* pOwner = pBoxCollider->GetOwnerEntity();
				if (!pOwner) return;

				Transform2DComponent* pBoxTransform = pOwner->GetComponent<Transform2DComponent>();
				if (!pBoxTransform) return;

				Transform2DComponent* pCharTransform = pCharacter->GetOwnerEntity()->GetComponent<Transform2DComponent>();
				if (!pCharTransform) return;

				if (pBoxTransform->GetPosition().y > pCharTransform->GetPosition().y) return;

				Rectf feetRect = pCharacter->GetFeet();
				Rectf boxRect = pBoxCollider->GetBox();
				feetRect.m_LeftTop += pCharTransform->GetPosition();
				boxRect.m_LeftTop += pBoxTransform->GetPosition();

				if (feetRect.Overlap(boxRect))
				{
					result = true;
					feetRect.Overlap(boxRect);
				}
			});

		pCharacter->SetIsGrounded(result);
	}
}

