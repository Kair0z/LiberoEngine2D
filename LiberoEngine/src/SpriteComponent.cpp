#include "PCH.h"
#include "SpriteComponent.h"
#include "LiberoRenderer_SDL.h"

namespace Libero
{
	SpriteComponent::SpriteComponent(
		const std::string& filename, 
		const Rectf& destRect, 
		float framesPerSecond,
		size_t nrFrames, 
		size_t nrFramesPerRow,
		size_t initFrame, 
		const Vector2f& frameDimensions,
		const Vector2f& frameOffset,
		const Vector2f& sheetOffset)
	{

#pragma region init
		m_Data.m_NrFrames = nrFrames;
		m_Data.m_FramesPerRow =  nrFramesPerRow ;
		m_Data.m_DestRect = destRect;
		m_Data.m_Filename = filename;
		m_Data.m_FrameDimensions = frameDimensions;
		m_Data.m_pSDLTexture = nullptr;
		m_Data.m_FramesPerSecond = framesPerSecond;
		m_Data.m_ShouldAnimate = true;
		m_Data.m_TimeSinceLastFrame = 0;
		m_Data.m_Reverse = false;
		m_Data.m_FrameOffset = frameOffset;
		m_Data.m_SheetOffset = sheetOffset;
#pragma endregion

		m_Data.m_pSDLTexture = IMG_LoadTexture(static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate())->GetSDLRenderer(), filename.c_str());
		SetFrame(initFrame);
	}

	SpriteComponent::SpriteComponent(const SpriteComponent& other)
	{
		m_Data = other.m_Data;

		m_Data.m_pSDLTexture = IMG_LoadTexture(static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate())->GetSDLRenderer(), m_Data.m_Filename.c_str());
		SetFrame(0);
	}

	SpriteComponent::SpriteComponent(SpriteComponent&& other)
	{
		m_Data = other.m_Data;

		m_Data.m_pSDLTexture = IMG_LoadTexture(static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate())->GetSDLRenderer(), m_Data.m_Filename.c_str());
		SetFrame(0);
	}

	SpriteComponent::~SpriteComponent()
	{
		SDL_DestroyTexture(m_Data.m_pSDLTexture);
		m_Data.m_pSDLTexture = nullptr;
	}

	SDL_Texture* SpriteComponent::GetSDLTexture()
	{
		return m_Data.m_pSDLTexture;
	}

	void SpriteComponent::SetFrame(size_t frameIdx)
	{
		if (frameIdx > m_Data.m_NrFrames) frameIdx = m_Data.m_NrFrames;

		m_Data.m_CurrentFrame.m_Idx = frameIdx;

		m_Data.m_CurrentFrame.m_SrcRect.m_LeftTop.x = m_Data.m_SheetOffset.x +  (frameIdx % m_Data.m_FramesPerRow) * (m_Data.m_FrameDimensions.x + m_Data.m_FrameOffset.x);
		m_Data.m_CurrentFrame.m_SrcRect.m_LeftTop.y = m_Data.m_SheetOffset.y + (frameIdx / m_Data.m_FramesPerRow) * (m_Data.m_FrameDimensions.y + m_Data.m_FrameOffset.y);

		m_Data.m_CurrentFrame.m_SrcRect.m_W = m_Data.m_FrameDimensions.x;
		m_Data.m_CurrentFrame.m_SrcRect.m_H = m_Data.m_FrameDimensions.y;
	}

	void SpriteComponent::NextFrame()
	{
		size_t nextIdx = m_Data.m_CurrentFrame.m_Idx + 1;
		if (nextIdx >= m_Data.m_NrFrames) nextIdx = 0;

		SetFrame(nextIdx);
	}

	void SpriteComponent::PreviousFrame()
	{
		size_t prevIdx = m_Data.m_CurrentFrame.m_Idx - 1;
		if ((int)m_Data.m_CurrentFrame.m_Idx - 1 < 0) prevIdx = m_Data.m_NrFrames - 1;

		SetFrame(prevIdx);
	}
}

