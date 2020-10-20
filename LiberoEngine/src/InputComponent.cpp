#include "PCH.h"
#include "InputComponent.h"

namespace Libero
{
	InputComponent::InputComponent()
	{
		m_KeyStates.reserve(200);
	}

#pragma region KeyState
	void InputComponent::ResetKeys()
	{
		// Set all keys to NONE:
		for (auto& state : m_KeyStates)
		{
			state.second = KeyState::NONE;
		}
	}
	void InputComponent::SetKeyState(SDL_Keycode key, KeyState state)
	{
		m_KeyStates[key] = state;
	}

	InputComponent::KeyState InputComponent::GetKeyState(SDL_Keycode key) const
	{
		if (m_KeyStates.find(key) == m_KeyStates.end()) return KeyState::NONE;

		return m_KeyStates.at(key);
	}

	bool InputComponent::IsKeyDown(SDL_Keycode key)
	{
		return (GetKeyState(key) == KeyState::DOWN);
	}
	bool InputComponent::IsKeyUp(SDL_Keycode key)
	{
		return (GetKeyState(key) == KeyState::UP);
	}

	
#pragma endregion

#pragma region MouseState
	void InputComponent::SetMouseDown(bool isDown)
	{
		m_MouseState.m_IsMouseDown = isDown;
	}
	void InputComponent::SetMouseUp(bool isUp)
	{
		m_MouseState.m_IsMouseDown = !isUp;
	}

	bool InputComponent::IsMouseUp() const
	{
		return !m_MouseState.m_IsMouseDown;
	}
	bool InputComponent::IsMouseDown() const
	{
		return !IsMouseUp();
	}
#pragma endregion
}

