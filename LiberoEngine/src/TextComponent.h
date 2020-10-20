#pragma once
#include <string>
#include "LiberoMacros.h"
#include "Component.h"
#include "LiberoMath.h"
#include <SDL_ttf.h>

namespace Libero
{
	class TextComponent : public Component<TextComponent>
	{
	public:
		TextComponent(const std::string& text);

		DefGet(std::string, m_Text, Text);
		void SetText(const std::string& newText);
		DefGetSet(Rectf, m_DestRect, DestRect);

		TTF_Font* GetTTF_Font() const;

		void SetShouldRender(bool enable);
		bool ShouldRender() const;

		virtual std::ofstream& ToFile(std::ofstream& ofs) const override;

	private:
		std::string m_Text;
		TTF_Font* m_pFont;
		bool m_ShouldRender;
		Rectf m_DestRect{};
	};
}


