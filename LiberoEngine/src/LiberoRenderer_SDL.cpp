#include "PCH.h"
#include "LiberoRenderer_SDL.h"
#include "SceneManager.h"
#include "LiberoScene.h"
#include "SpaceMath.h"
#include "Logger.h"

namespace Libero
{
#pragma region Init&Cleanup
	LiberoRenderer_SDL::LiberoRenderer_SDL()
		: m_Context{}
		, m_IsInitialized{false}
		, m_pPixels{nullptr}
	{

	}

	LiberoRenderer_SDL::~LiberoRenderer_SDL()
	{
		Destroy();
	}

	void LiberoRenderer_SDL::Initialize(SDL_Window* pWindow, SDL_Rect* pSubRenderWindow)
	{
		SDL_GetWindowSize(pWindow, &m_WindowDimensions[0], &m_WindowDimensions[1]);
		
		InitContext(pWindow, pSubRenderWindow);

		m_AmountOfPixels = (size_t)m_WindowDimensions[0] * (size_t)m_WindowDimensions[1];

		m_pPixels = new uint32_t[m_AmountOfPixels]{};

		for (uint32_t i{}; i < m_AmountOfPixels; ++i)
		{
			m_pPixels[i] = SDL_MapRGBA(m_Context.m_pPixelFormat, 255, 255, 255, 255);
		}
	}

	bool LiberoRenderer_SDL::IsInitialized() const
	{
		return m_IsInitialized;
	}

	void LiberoRenderer_SDL::InitContext(SDL_Window* pWindow, SDL_Rect* pSubRenderWindow)
	{
		m_Context.m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_Context.m_pRenderer)
			throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());


		m_Context.m_pTexture = SDL_CreateTexture(m_Context.m_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_WindowDimensions[0], m_WindowDimensions[1]);
		if (!m_Context.m_pTexture)
			throw std::runtime_error(std::string("SDL_CreateTexture error: ") + SDL_GetError());

		if (pSubRenderWindow) SetSubRenderWindow({ (size_t)pSubRenderWindow->x, (size_t)pSubRenderWindow->y }, {(size_t)pSubRenderWindow->w, (size_t)pSubRenderWindow->h});

		m_Context.m_pPixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	}

	void LiberoRenderer_SDL::Destroy()
	{
		if (!m_Context.m_pRenderer) return;

		SDL_DestroyRenderer(m_Context.m_pRenderer);
		m_Context.m_pRenderer = nullptr;

		SDL_DestroyTexture(m_Context.m_pTexture);
		m_Context.m_pTexture = nullptr;

		SDL_FreeFormat(m_Context.m_pPixelFormat);
		m_Context.m_pPixelFormat = nullptr;

		delete m_Context.m_pSubWindow;
		m_Context.m_pSubWindow = nullptr;

		delete[] m_pPixels;
		m_pPixels = nullptr;
	}

	void LiberoRenderer_SDL::SetSubRenderWindow(const Vector2ui& cursor, const Vector2ui& dimensions)
	{
		if (m_Context.m_pSubWindow)
		{
			delete m_Context.m_pSubWindow;
		}

		SDL_Rect newRect{};
		newRect.x = cursor[0];
		newRect.y = cursor[1];
		newRect.w = dimensions[0];
		newRect.h = dimensions[1];

		m_Context.m_pSubWindow = new SDL_Rect(newRect);
	}

	SDL_Rect LiberoRenderer_SDL::GetRenderSpace() const
	{
		SDL_Rect result{};

		if (m_Context.m_pSubWindow)
		{
			result.h = m_Context.m_pSubWindow->h;
			result.w = m_Context.m_pSubWindow->w;
			result.x = m_Context.m_pSubWindow->x;
			result.y = m_Context.m_pSubWindow->y;
		}
		else
		{
			result.h = m_WindowDimensions[1];
			result.w = m_WindowDimensions[0];
			result.x = 0;
			result.y = 0;
		}

		return result;
	}

#pragma endregion

	SDL_Renderer* LiberoRenderer_SDL::GetSDLRenderer() const
	{
		return m_Context.m_pRenderer;
	}

	SDL_Rect LiberoRenderer_SDL::GetProcessedRectangle(float x, float y, float w, float h, Space space) const
	{
		SDL_Rect renderSpace = GetRenderSpace();
		SDL_Rect result{};

		result.w = (int)w;
		result.h = (int)h;

		Vector2i point = GetProcessedPoint(x, y, space);

		result.x = point.x;
		result.y = point.y;

		return result;
	}

	Vector2i LiberoRenderer_SDL::GetProcessedPoint(float x, float y, Space space) const
	{
		SDL_Rect renderSpace = GetRenderSpace();
		Vector2i res{};

		if (space == Space::World)
		{
			res.x = (renderSpace.x + renderSpace.w / 2) + (int)x;
			res.y = (renderSpace.y + renderSpace.h / 2) - (int)y;
		}
		else
		{
			res.x = renderSpace.x + (int)x;
			res.y = renderSpace.y + (int)y;
		}

		return res;
	}

	void LiberoRenderer_SDL::Open() const
	{
		SDL_SetRenderDrawColor(m_Context.m_pRenderer, (uint8_t)m_ClearColor[0], (uint8_t)m_ClearColor[1], (uint8_t)m_ClearColor[2], (uint8_t)m_ClearColor[3]);
		SDL_RenderClear(m_Context.m_pRenderer);

	}
	
	void LiberoRenderer_SDL::Present() const
	{
		SDL_RenderPresent(m_Context.m_pRenderer);
	}

	const uint32_t* LiberoRenderer_SDL::GetPixels() const
	{
		return m_pPixels;
	}

#pragma region Rendering
	
	void LiberoRenderer_SDL::RenderTexture(const std::string& tex, float x, float y, float w, float h, Space space) const
	{
		std::string fullString = "../Resources/" + tex;
		SDL_Texture* pTex = IMG_LoadTexture(m_Context.m_pRenderer, fullString.c_str());

		RenderTexture(pTex, x, y, w, h, space);

		SDL_DestroyTexture(pTex);
	}

	void LiberoRenderer_SDL::RenderTexture(const std::string& tex, float x, float y, float w, float h, const Rectf& srcRect, Space space) const
	{
		std::string fullString = "../Resources/" + tex;
		SDL_Texture* pTex = IMG_LoadTexture(m_Context.m_pRenderer, fullString.c_str());

		RenderTexture(pTex, x, y, w, h, srcRect, space);

		SDL_DestroyTexture(pTex);
	}

	void LiberoRenderer_SDL::RenderTexture(SDL_Texture* pTex, float x, float y, float w, float h, Space space) const
	{
		SDL_Rect dest = GetProcessedRectangle(x, y, w, h, space);

		int iW = (int)w;
		int iH = (int)h;

		SDL_QueryTexture(pTex, nullptr, nullptr, &iW, &iH);
		SDL_RenderCopy(GetSDLRenderer(), pTex, nullptr, &dest);
	}

	void LiberoRenderer_SDL::RenderTexture(SDL_Texture* pTex, float x, float y, float w, float h, const Rectf& srcRect, Space space) const
	{
		SDL_Rect dest = GetProcessedRectangle(x, y, w, h, space);
		SDL_Rect src;
		src.x = (int)srcRect.m_LeftTop.x;
		src.y = (int)srcRect.m_LeftTop.y;
		src.w = (int)srcRect.m_W;
		src.h = (int)srcRect.m_H;

		SDL_RenderCopy(GetSDLRenderer(), pTex, &src, &dest);
	}

	void LiberoRenderer_SDL::RenderQuad(float x, float y, float width, float height, const ColorRGBA& color, Space space, bool fill) const
	{
		SDL_SetRenderDrawColor(GetSDLRenderer(), (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], (uint8_t)color[3]);

		SDL_Rect dest = GetProcessedRectangle(x, y, width, height, space);

		if (fill) SDL_RenderFillRect(GetSDLRenderer(), &dest);
		else SDL_RenderDrawRect(GetSDLRenderer(), &dest);
	}

	void LiberoRenderer_SDL::RenderPoint(float x, float y, float pixelRadius, const ColorRGBA& color, Space space) const
	{
		pixelRadius;

		SDL_SetRenderDrawColor(GetSDLRenderer(), (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], (uint8_t)color[3]);

		SDL_Rect dest = GetProcessedRectangle(x, y, 0, 0, space);
		SDL_RenderDrawPoint(GetSDLRenderer(), (int)x, (int)y);
	}

	void LiberoRenderer_SDL::RenderLine(const Vector2f& p0, const Vector2f& p1, const ColorRGBA& color, Space space) const
	{
		Vector2i res0 = GetProcessedPoint(p0.x, p0.y, space);
		Vector2i res1 = GetProcessedPoint(p1.x, p1.y, space);

		SDL_SetRenderDrawColor(GetSDLRenderer(), (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], (uint8_t)color[3]);
		SDL_RenderDrawLine(GetSDLRenderer(), res0.x, res0.y, res1.x, res1.y);
	}

	void LiberoRenderer_SDL::RenderText(TTF_Font* pTTF_Font, const std::string& text, float x, float y, float w, float h, const ColorRGB& color, Space space) const
	{
		if (!pTTF_Font) LoggerLocator::Locate()->LogWarning("LiberoRenderer_SDL::RenderText( ) >> Font to render is not valid!");

		SDL_Color sdlColor = { (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2] };

		SDL_Surface* pSurface = TTF_RenderText_Solid(pTTF_Font, text.c_str(), sdlColor);
		SDL_Texture* pTex = SDL_CreateTextureFromSurface(GetSDLRenderer(), pSurface);


		SDL_Rect dest{};
		dest.x = (int)x;
		dest.y = (int)y;
		dest.w = (int)w;
		dest.h = (int)h;

		if (space != Space::World) dest = GetProcessedRectangle(x, y, w, h, space);

		SDL_RenderCopy(GetSDLRenderer(), pTex, NULL, &dest);
		SDL_FreeSurface(pSurface);
		SDL_DestroyTexture(pTex);
		
	}

	
#pragma endregion
}
