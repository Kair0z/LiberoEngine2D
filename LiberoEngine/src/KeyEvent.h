#pragma once
#include "Event.h"
#include <sstream>

namespace Libero
{
	using Keycode = int;

	class KeyUpEvent : public Event<KeyUpEvent>
	{
	public:
		KeyUpEvent(Keycode key) : m_Key{key}{}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Key Up: [" << m_Key << "]";

			return ss.str();
		}

		Keycode GetKey() const
		{
			return m_Key;
		}

	private:
		Keycode m_Key;
	};

	class KeyDownEvent : public Event<KeyDownEvent>
	{
	public:
		KeyDownEvent(Keycode key) : m_Key{ key } {}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Key Down: [" << m_Key << "]";

			return ss.str();
		}

		Keycode GetKey() const
		{
			return m_Key;
		}

	private:
		Keycode m_Key;
	};
}


