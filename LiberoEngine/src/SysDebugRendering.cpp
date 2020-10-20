#include "PCH.h"
#include "SysDebugRendering.h"

#include "ECS_Includes.h"
#include "LiberoRenderer_SDL.h"
#include "Logger.h"
#include "SpaceMath.h"

#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "GridComponent.h"
#include "ColliderComponent.h"
#include "CharacterComponent.h"
#include "PhysicsMaster.h"

namespace Libero
{
	void SysDebugRendering::PostDraw() const
	{
		//DrawGrids();
		//DrawTransforms();
		//DrawPhysics();
		//DrawMovement();
	}

	void SysDebugRendering::DrawTransforms() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<Transform2DComponent>([&pRenderer](Transform2DComponent* pTransform)
			{
				Vector2f pos = pTransform->GetPosition();

				pRenderer->RenderQuad(pos.x, pos.y, 5.f, 5.f, ColorRGBA{ 255.f, 255.f, 0.f, 255.f }, LiberoRenderer_SDL::Space::World);
			});
	}

	void SysDebugRendering::DrawGrids() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<Grid2DComponent>([&pRenderer](Grid2DComponent* pGrid)
			{
				IEntity* pOwner = pGrid->GetOwnerEntity();
				Vector2f transPos = {};
				Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
				if (pTransform) transPos = pTransform->GetPosition();

				for (const GridCell& cell : pGrid->GetCells())
				{
					Vector2f pos = cell.GetLeftTop();

					pRenderer->RenderQuad(pos[0] + transPos[0], pos[1] + transPos[1], cell.m_W, cell.m_H, { 255.f, 0.f, 0.f, 20.f }, LiberoRenderer_SDL::Space::World, false);
				}
			});
	}

	void SysDebugRendering::DrawPhysics() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<BoxCollider2DComponent>([&pRenderer](BoxCollider2DComponent* pBoxCollider)
			{
				IEntity* pOwner = pBoxCollider->GetOwnerEntity();
				if (pOwner && pOwner->HasComponent<Transform2DComponent>())
				{
					Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
					auto points = pBoxCollider->GetShape()->m_vertices;

					Vector2f pos = pTransform->GetPosition();
					Rectf rect{};
					rect.m_LeftTop.x = Physics::ScaleToWorld(points[3].x);
					rect.m_LeftTop.y = Physics::ScaleToWorld(points[3].y);
					rect.m_W = Physics::ScaleToWorld(points[2].x - points[3].x);
					rect.m_H = Physics::ScaleToWorld(-(points[0].y - points[3].y));

					pRenderer->RenderQuad(pos.x + rect.m_LeftTop.x, pos.y + rect.m_LeftTop.y, rect.m_W, rect.m_H, { 0.f, 255.f, 0.f, 255.f }, LiberoRenderer_SDL::Space::World, false);
				}
				
			});
	}

	void SysDebugRendering::DrawMovement() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<CharacterComponent>([&pRenderer](CharacterComponent* pCharacter)
			{
				IEntity* pOwner = pCharacter->GetOwnerEntity();
				if (!pOwner) return;

				Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();
				if (!pTransform) return;

				Vector2f pos = pTransform->GetPosition();
				Rectf feet = pCharacter->GetFeet();

				pRenderer->RenderQuad(pos.x + feet.m_LeftTop.x, pos.y + feet.m_LeftTop.y, feet.m_W, feet.m_H, { 0.f, 255.f, 0.f, 255.f }, LiberoRenderer_SDL::Space::World, false);
			});
	}
}