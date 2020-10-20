#include "PCH.h"
#include "TextComponent.h"
#include "Logger.h"
#include "LiberoRenderer_SDL.h"
#include <iomanip>

namespace Libero
{
	TextComponent::TextComponent(const std::string& text)
		: m_Text{}
		, m_pFont{nullptr}
		, m_ShouldRender{true}
	{
		m_pFont = TTF_OpenFont("../Resources/Fonts/ARCADE.TTF", 60);
		if (!m_pFont) LoggerLocator::Locate()->LogWarning("Problem opening font!" + std::string(TTF_GetError()));

		SetText(text);
	}

	void TextComponent::SetText(const std::string& newText)
	{
		m_Text = newText;
	}

	TTF_Font* TextComponent::GetTTF_Font() const
	{
		return m_pFont;
	}

	void TextComponent::SetShouldRender(bool enable)
	{
		m_ShouldRender = enable;
	}

	bool TextComponent::ShouldRender() const
	{
		return m_ShouldRender;
	}

	std::ofstream& TextComponent::ToFile(std::ofstream& ofs) const
	{
		ofs << "- TextComponent: \n";
		ofs << "Text: " << m_Text << "\n";
		ofs << "DestRect: ... \n";
		ofs << "ShouldRender: " << std::boolalpha << m_ShouldRender << "\n";
		ofs << "\n";

		return ofs;
	}
}

