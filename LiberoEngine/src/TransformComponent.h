#pragma once
#include "LiberoMath.h"
#include "Component.h"
#include "LiberoMacros.h"
#include <fstream>

namespace Libero
{
	class TransformComponent : public Component<TransformComponent>
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent() = default;

		DefGetSet(Vector3f, m_Position, Position);
		DefGetSet(Vector3f, m_Rotation, Rotation);
		DefGetSet(Vector3f, m_Scale, Scale);

		DefGetRef(Vector3f, m_Position, Position);
		DefGetRef(Vector3f, m_Rotation, Rotation);
		DefGetRef(Vector3f, m_Scale, Scale);

		virtual std::ofstream& ToFile(std::ofstream& ofs) const override;

	private:
		Vector3f m_Position{};
		Vector3f m_Rotation{}; // Euler
		Vector3f m_Scale{};
	};

	class Transform2DComponent : public Component<Transform2DComponent>
	{
	public:
		Transform2DComponent() = default;
		virtual ~Transform2DComponent() = default;

		DefGetSet(Vector2f, m_Position, Position);
		DefGetSet(float, m_Rotation, Rotation);
		DefGetSet(Vector2f, m_Scale, Scale);

		DefGetRef(Vector2f, m_Position, Position);
		DefGetRef(float, m_Rotation, Rotation);
		DefGetRef(Vector2f, m_Scale, Scale);

		void Translate(const Vector2f& translate);
		void AddRotation(const float rotAdd);

		virtual std::ofstream& ToFile(std::ofstream& ofs) const override;

	private:
		Vector2f m_Position{};
		float m_Rotation{};
		Vector2f m_Scale{};
	};
}

