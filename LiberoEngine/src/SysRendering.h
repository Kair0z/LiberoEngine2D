#pragma once
#include "System.h"
#include "Event.h"

namespace Libero
{
	enum class PivotType
	{
		Center,
		LeftTop,
		RightTop,
		LeftBottom,
		RightBottom
	};

	class SysRendering : public System<SysRendering>
	{
	public:
		virtual void Draw() const override;
		virtual void PostDraw() const override;

	private:
		void DrawTexts() const;
		void DrawTextures() const;
		void DrawSprites() const;
	};
}



