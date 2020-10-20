#pragma once
#include "LiberoMath.h"
#include "LiberoMacros.h"
#include "Component.h"

struct SDL_Texture;

namespace Libero
{
	class SpriteComponent : public Component<SpriteComponent>
	{
	public:
		struct SpriteFrame
		{
			size_t m_Idx{};
			Rectf m_SrcRect{};
		};

		struct SpriteData
		{
			std::string m_Filename{};
			SDL_Texture* m_pSDLTexture = nullptr;
			Rectf m_DestRect{};

			size_t m_NrFrames;
			size_t m_FramesPerRow;
			SpriteFrame m_CurrentFrame;

			float m_FramesPerSecond;
			float m_TimeSinceLastFrame;

			bool m_ShouldAnimate = true;
			bool m_Reverse;

			Vector2f m_FrameDimensions;
			Vector2f m_FrameOffset;
			Vector2f m_SheetOffset;
		};

	public:
		SpriteComponent(
			const std::string& filename,
			const Rectf& destRect,
			float framesPerSecond,
			size_t nrFrames,
			size_t nrFramesPerRow,
			size_t initFrame,
			const Vector2f& frameDimensions,
			const Vector2f& frameOffset,
			const Vector2f& sheetOffset = {});

		SpriteComponent(const SpriteComponent& other);
		SpriteComponent(SpriteComponent&& other);

		~SpriteComponent();

		DefGetSet(std::string, m_Data.m_Filename, Filename);
		DefGetSet(Rectf, m_Data.m_DestRect, DestRect);
		DefGetSet(float, m_Data.m_FramesPerSecond, FramesPerSecond);
		DefGetSet(float, m_Data.m_TimeSinceLastFrame, TimeSinceLastFrame);
		DefGetSet(bool, m_Data.m_ShouldAnimate, ShouldUpdate);
		DefGetSet(bool, m_Data.m_Reverse, IsReversed);
		DefGetSet(SpriteFrame, m_Data.m_CurrentFrame, CurrentFrame);
		DefGetSet(Vector2f, m_Data.m_FrameDimensions, FrameDimensions);
		DefGetSet(Vector2f, m_Data.m_FrameOffset, FrameOffset);
		DefGetSet(Vector2f, m_Data.m_SheetOffset, SheetOffset);
		DefGetSet(SpriteData, m_Data, SpriteData);
		SDL_Texture* GetSDLTexture();
		
		void SetFrame(size_t frameIdx);
		void NextFrame();
		void PreviousFrame();

	private:
		SpriteData m_Data;
	};
}


