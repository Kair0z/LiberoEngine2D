#include "PCH.h"
#include "TextureComponent.h"

#include "LiberoRenderer_SDL.h"


namespace Libero
{
	Texture2DComponent::Texture2DComponent(const std::string& filename, const Rectf& destRect)
		: Texture2DComponent(filename, destRect, {})
	{
		Rectf source{};
		source.m_H = 1;
		source.m_W = 1;
		SetSourceRect(source);
	}

	Texture2DComponent::Texture2DComponent(const std::string& filename, const Rectf& dest, const Rectf& src)
		: m_DestRect{ dest }
		, m_SrcRect{src}
		, m_File{ filename }
		, m_pSDLTexture{ nullptr }
	{
		m_pSDLTexture = IMG_LoadTexture(static_cast<LiberoRenderer_SDL*>(RendererLocator::Locate())->GetSDLRenderer(), filename.c_str());
		
	}

	Texture2DComponent::~Texture2DComponent()
	{
		SDL_DestroyTexture(m_pSDLTexture);
		m_pSDLTexture = nullptr;
	}
	SDL_Texture* Texture2DComponent::GetSDLTexture()
	{
		return m_pSDLTexture;
	}
}