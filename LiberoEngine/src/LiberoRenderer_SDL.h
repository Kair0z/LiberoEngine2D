#pragma once
#include "LiberoRenderer.h"
#include "LiberoMacros.h"
#include "LiberoMath.h"
#include <SDL_ttf.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_PixelFormat;
struct SDL_Rect;

namespace Libero
{
	class LiberoSceneMaster;
	class LiberoScene;
	class Texture2DComponent;

	class LiberoRenderer_SDL final : public LiberoRenderer
	{
	public:
		struct SDLContext
		{
			SDL_Window* m_pWindow = nullptr;
			SDL_Renderer* m_pRenderer = nullptr;
			SDL_Texture* m_pTexture = nullptr;
			SDL_PixelFormat* m_pPixelFormat = nullptr;
			SDL_Rect* m_pSubWindow = nullptr;
		};

		enum class Space
		{
			World,
			Screen
		};

	public:
		LiberoRenderer_SDL();
		~LiberoRenderer_SDL();

		void Initialize(SDL_Window* pWindow, SDL_Rect* pSubRenderWindow);
		bool IsInitialized() const;

		void SetSubRenderWindow(const Vector2ui& cursor, const Vector2ui& dimensions);
		SDL_Rect GetRenderSpace() const;

		virtual void Open() const override final;
		virtual void Present() const override final;

		void RenderTexture(const std::string& tex, float x, float y, float w, float h, Space space = Space::Screen) const;
		void RenderTexture(const std::string& tex, float x, float y, float w, float h, const Rectf& srcRect, Space space = Space::Screen) const;
		void RenderTexture(SDL_Texture* pTex, float x, float y, float w, float h, Space space = Space::Screen) const;
		void RenderTexture(SDL_Texture* pTex, float x, float y, float w, float h, const Rectf& srcRect, Space space = Space::Screen) const;
		void RenderQuad(float x, float y, float width, float height, const ColorRGBA& color = {255.f, 0.f, 0.f, 255.f}, Space space = Space::Screen, bool fill = true) const;

		void RenderPoint(float x, float y, float pixelRadius = 3.f, const ColorRGBA& color = { 255.f, 0.f, 0.f, 255.f }, Space space = Space::Screen) const;
		void RenderLine(const Vector2f& p0, const Vector2f& p1, const ColorRGBA& color = { 255.f, 0.f, 0.f, 255.f }, Space space = Space::Screen) const;
		void RenderText(TTF_Font* pTTF_Font, const std::string& text, float x, float y, float w, float h, const ColorRGB& color = { 255.f, 255.f, 255.f }, Space space = Space::Screen) const;
		

		SDL_Renderer* GetSDLRenderer() const;
		const uint32_t* GetPixels() const;

	private:
		SDLContext m_Context;
		Vector2i m_WindowDimensions;
		
		uint32_t* m_pPixels;
		size_t m_AmountOfPixels;

		bool m_IsInitialized;

		void InitContext(SDL_Window* pWindow, SDL_Rect* pSubRenderWindow);
		void Destroy();
		SDL_Rect GetProcessedRectangle(float x, float y, float w, float h, Space space) const;
		Vector2i GetProcessedPoint(float x, float y, Space space) const;

	public:
		ROFDEL(LiberoRenderer_SDL)
	};
}


