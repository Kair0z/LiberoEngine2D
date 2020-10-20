#pragma once
#include "Component.h"
#include <string>
#include "LiberoMacros.h"

namespace Libero
{
	class Transform2D : public Component<Transform2D>
	{
	public:
		Transform2D() = default;
		DefGetSet(float, m_Rotation, Rotation);
		DefGetRef(float, m_Rotation, Rotation);

	private:
		float m_Rotation;
		float m_Position;
		float m_Scale;
	};

	class Velocity2D : public Component<Velocity2D>
	{
	public:

	private:

	};

	class Text : public Component<Text>
	{
	public:
		Text(const std::string& text) : m_Text{ text } {}

		DefGetSet(std::string, m_Text, Text);
		DefGetRef(std::string, m_Text, Text);

	private:
		std::string m_Text;
	};

	struct InputCatch : public Component<InputCatch>
	{
		bool m_KeydownLeft;
		bool m_KeydownRight;
	};

	struct Texture2DComponent : public Component<Texture2DComponent>
	{

	};

	struct Spawn : public Component<Spawn>
	{
		float m_Pos;
		float m_Rot;
	};

	struct BoxCollision2D : public Component<BoxCollision2D>
	{
		float m_LT;
		float m_Width;
		float m_Height;
	};

}

