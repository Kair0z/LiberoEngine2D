#pragma once
#include "Event.h"
#include "LiberoMath.h"

#include <sstream>

namespace Libero
{
	class MouseMoveEvent final : public Event<MouseMoveEvent>
	{
	public:
		MouseMoveEvent(const Vector2f& newMousePos) : m_NewMousePos{newMousePos}{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved: [" << m_NewMousePos[0] << ", " << m_NewMousePos[1] << "]";

			return ss.str();
		}

		Vector2f GetNewMousePos() const { return m_NewMousePos; }

	private:
		Vector2f m_NewMousePos{};
	};

	class MouseDownEvent final : public Event<MouseDownEvent>
	{
	public:
		MouseDownEvent(const Vector2f& mousePos) : m_MousePos{mousePos}{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Down: [" << m_MousePos[0] << ", " << m_MousePos[1] << "]";

			return ss.str();
		}

	private:
		Vector2f m_MousePos{};
	};

	class MouseUpEvent final : public Event<MouseUpEvent>
	{
	public:
		MouseUpEvent(const Vector2f& mousePos) : m_MousePos{mousePos}{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Up: [" << m_MousePos[0] << ", " << m_MousePos[1] << "]";

			return ss.str();
		}

	private:
		Vector2f m_MousePos{};
	};
}


