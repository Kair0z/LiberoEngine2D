#include "PCH.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "LiberoECS_EntityMaster.h"
#include "ECS_Defines.h"

namespace Libero
{

	void GameObject::Initialize()
	{
		m_pTransform = AddComponent<Transform2DComponent>();
		m_IsActive = true;
	}

	void GameObject::SetName(const std::string& newName)
	{
		m_Name = newName;
	}
	const std::string& GameObject::Getname() const
	{
		return m_Name;
	}

	Transform2DComponent* GameObject::GetTransform()
	{
		return m_pTransform;
	}
}

