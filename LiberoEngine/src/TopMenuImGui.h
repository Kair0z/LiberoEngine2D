#pragma once
#include "LiberoMacros.h"

namespace Libero
{
	class LiberoCore;
	class TopMenuImGui
	{
	public:
		TopMenuImGui() = default;
		~TopMenuImGui() = default;

		void Render() const;
		void End() const;
	};
}


