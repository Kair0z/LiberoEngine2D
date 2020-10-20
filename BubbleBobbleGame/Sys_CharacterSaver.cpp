#include "Sys_CharacterSaver.h"
#include "CharacterComponent.h"
#include "TransformComponent.h"
#include "CoreSettings.h"
#include "RigidbodyComponent.h"
#include "PhysicsMaster.h"
#include "LiberoRenderer_SDL.h"

using namespace Libero;

void Sys_CharacterSaver::Update(float)
{
	ForEachComponent<CharacterComponent>([=](CharacterComponent* pCharacter)
		{
			IEntity* pOwner = pCharacter->GetOwnerEntity();
			if (!pOwner) return;

			Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
			if (!pTransform) return;

			RigidbodyComponent* pBody = pOwner->GetComponent<RigidbodyComponent>();
			if (!pBody) return;

			Vector2f pos = pTransform->GetPosition();
			Vector2f respawnPos = m_Respawnzone0.GetMid();

			// Vertical correction:
			float halfHeight = (float)(CoreSettings::m_GameDimensions.y / 2);
			if (pos.y < -halfHeight - 500.f || pos.y > halfHeight + 500.f)
			{
				pTransform->SetPosition(respawnPos);
				pBody->GetB2DBody()->SetTransform({ Physics::ScaleToWorld(respawnPos.x), Physics::ScaleToWorld(respawnPos.y) }, 0.f);
			}
		});
}

void Sys_CharacterSaver::PostDraw() const
{
	LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
	if (!pRenderer)
	{
		LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
		return;
	}

	pRenderer->RenderQuad(m_Respawnzone0.m_LeftTop.x, m_Respawnzone0.m_LeftTop.y, m_Respawnzone0.m_W, m_Respawnzone0.m_H, { 255.f, 255.f, 0.f, 255.f }, LiberoRenderer_SDL::Space::World, false);
	pRenderer->RenderQuad(m_Respawnzone1.m_LeftTop.x, m_Respawnzone1.m_LeftTop.y, m_Respawnzone1.m_W, m_Respawnzone1.m_H, { 255.f, 255.f, 0.f, 255.f }, LiberoRenderer_SDL::Space::World, false);
}
