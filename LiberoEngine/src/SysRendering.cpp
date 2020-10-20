#include "PCH.h"
#include "SysRendering.h"

#include "ECS_Includes.h"

#include "LiberoRenderer_SDL.h"
#include "Logger.h"

#include "TransformComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"	
#include "SpriteComponent.h"

namespace Libero
{
	Rectf RenderToPivot(const Vector2f& pos, const Rectf& destRect, PivotType pivotType)
	{
		Rectf res = destRect;

		switch (pivotType)
		{
		case PivotType::Center:
			res.m_LeftTop.x = pos.x - destRect.m_W / 2.f;
			res.m_LeftTop.y = pos.y + destRect.m_H / 2.f;
			return res;
			break;

		case PivotType::LeftBottom:
			res.m_LeftTop.y = pos.y - destRect.m_H / 2.f;
			return res;
			break;

		case PivotType::LeftTop:
			return res;
			break;

		case PivotType::RightBottom:
			res.m_LeftTop.x = pos.x + destRect.m_W / 2.f;
			res.m_LeftTop.y = pos.y - destRect.m_H / 2.f;
			return res;
			break;

		case PivotType::RightTop:
			res.m_LeftTop.x = pos.x + destRect.m_W / 2.f;
			return res;
			break;
		}

		return res;
	}

	void SysRendering::Draw() const
	{
		DrawTextures();
		DrawSprites();
	}

	void SysRendering::PostDraw() const
	{
		DrawTexts();
	}

	void SysRendering::DrawTexts() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<TextComponent>([&pRenderer](TextComponent* pText)
			{
				if (!pText->ShouldRender()) return;

				IEntity* pOwner = pText->GetOwnerEntity();
				if (pOwner && pOwner->HasComponent<Transform2DComponent>())
				{
					Rectf destRect = pText->GetDestRect();
					Vector2f pos = pOwner->GetComponent<Transform2DComponent>()->GetPosition();

					pRenderer->RenderQuad(destRect.m_LeftTop.x + pos.x, destRect.m_LeftTop.y - pos.y, 160.f, 60.f, { 0.f, 0.f, 0.f, 255.f });
					pRenderer->RenderQuad(destRect.m_LeftTop.x + pos.x, destRect.m_LeftTop.y - pos.y, 160.f, 60.f, { 255.f, 255.f, 255.f, 255.f }, LiberoRenderer_SDL::Space::Screen, false);
					pRenderer->RenderText(pText->GetTTF_Font(), pText->GetText(), destRect.m_LeftTop[0] + pos[0], destRect.m_LeftTop[1] - pos[1], 160, 60, { 255.f, 0.f, 0.f});
				}


			});
	}

	void SysRendering::DrawTextures() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<Texture2DComponent>([&pRenderer](Texture2DComponent* pTexture)
			{
				IEntity* pOwner = pTexture->GetOwnerEntity();
				Transform2DComponent* pTransform = pOwner->GetComponent<Transform2DComponent>();

				Vector2f pos = pTransform->GetPosition();
				Rectf destRect = pTexture->GetDestRect();

				pRenderer->RenderTexture(
					pTexture->GetSDLTexture(),
					destRect.m_LeftTop.x + pos.x, destRect.m_LeftTop.y + pos.y, destRect.m_W, destRect.m_H,
					pTexture->GetSourceRect(),
					LiberoRenderer_SDL::Space::World);
			});

	}

	void SysRendering::DrawSprites() const
	{
		LiberoRenderer_SDL* pRenderer = static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate());
		if (!pRenderer)
		{
			LoggerLocator::Locate()->LogError("SysRendering::Draw() >> No Renderer found via Locator!");
			return;
		}

		ForEachComponent<SpriteComponent>([=](SpriteComponent* pSprite)
			{
				IEntity* pOwner = pSprite->GetOwnerEntity();
				if (pOwner && pOwner->HasComponent<Transform2DComponent>())
				{
					Vector2f pos = pOwner->GetComponent<Transform2DComponent>()->GetPosition();
					Rectf destRect = RenderToPivot(pos, pSprite->GetDestRect(), PivotType::Center);

					pRenderer->RenderTexture(
						pSprite->GetFilename(),
						destRect.m_LeftTop.x, 
						destRect.m_LeftTop.y, 
						destRect.m_W, 
						destRect.m_H,
						pSprite->GetCurrentFrame().m_SrcRect,
						LiberoRenderer_SDL::Space::World);
				}
			});
	}
}


