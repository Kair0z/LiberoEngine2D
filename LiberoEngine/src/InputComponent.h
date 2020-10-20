#pragma once
#include "Component.h"
#include <unordered_map>
#include "SDL.h"

namespace Libero
{
	class InputComponent : public Component<InputComponent>
	{
	public:
		enum class KeyState
		{
			DOWN,
			UP,
			NONE
		};
	private:
		struct MouseState
		{
			bool m_IsMouseDown;
		};

		using KeyMap = std::unordered_map<SDL_Keycode, KeyState>;

	public:
		InputComponent();

		// Mouse State:
		void SetMouseDown(bool isDown = true);
		void SetMouseUp(bool isUp = true);

		bool IsMouseDown() const;
		bool IsMouseUp() const;

		// Key state:
		void ResetKeys();
		void SetKeyState(SDL_Keycode key, KeyState);
		KeyState GetKeyState(SDL_Keycode key) const;

		bool IsKeyDown(SDL_Keycode key);
		bool IsKeyUp(SDL_Keycode key);

	private:
		MouseState m_MouseState{};
		KeyMap m_KeyStates;
	};
}

