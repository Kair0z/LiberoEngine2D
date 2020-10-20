#pragma once
#include "Entity.h"
#include <string>
#include <fstream>

namespace Libero
{
	class Transform2DComponent;

	class GameObject : public Entity<GameObject>
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		void Initialize() override;
		void SetName(const std::string& newName);
		const std::string& Getname() const;

		Transform2DComponent* GetTransform();

	private:
		std::string m_Name = "GameObject";
		Transform2DComponent* m_pTransform = nullptr;
	};
}


