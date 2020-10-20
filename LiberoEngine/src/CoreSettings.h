#pragma once
#include "LiberoMath.h"
#include <string>

// - 40 for windowed mode
#define WINDOWED_VERTICAL_CUTOFF 40
#define MENUBAR_VERTICAL_CUTOFF 20

namespace Libero
{
	namespace CoreSettings
	{
		static std::string m_VersionName = "v1.0";
		static std::string m_WindowName = "Libero Engine " + m_VersionName;
		static ColorRGBA m_ClearColor = { 63.f, 0.f, 0.0f, 255.f };

		static Vector2ui m_ApplicationDimensions = { 1920, 1080 - WINDOWED_VERTICAL_CUTOFF };
		static Vector2ui m_GameDimensions = { 720, 640 };
		static Vector2ui m_GameWindowTopLeft = {
				size_t((float(m_ApplicationDimensions.x) / 2.f) - (float(m_GameDimensions.x) / 2.f)),
				size_t(MENUBAR_VERTICAL_CUTOFF) };

	}
}


