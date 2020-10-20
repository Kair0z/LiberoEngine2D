#pragma once
#include "LiberoMacros.h"
#include "Component.h"
#include <string>
#include "LiberoMath.h"
#include "LiberoMacros.h"

struct SDL_Texture;

namespace Libero
{
	class Texture2DComponent : public Component<Texture2DComponent>
	{
	public:
		Texture2DComponent(const std::string& filename, const Rectf& dest);
		Texture2DComponent(const std::string& filename, const Rectf& dest, const Rectf& src);
		~Texture2DComponent();

		ROFDEL(Texture2DComponent)

		DefGetSet(std::string, m_File, Filename);
		DefGetRef(std::string, m_File, Filename);
		DefGetSet(Rectf, m_DestRect, DestRect);
		DefGetRef(Rectf, m_DestRect, DestRect);
		DefGetSet(Rectf, m_SrcRect, SourceRect);
		DefGet(SDL_Texture*, m_pSDLTexture, SDLTexture);
		SDL_Texture* GetSDLTexture();

	private:
		std::string m_File{};
		SDL_Texture* m_pSDLTexture = nullptr;
		Rectf m_DestRect{};
		Rectf m_SrcRect{};
	};
}


