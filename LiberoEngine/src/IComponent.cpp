#include "PCH.h"
#include "IComponent.h"
#include "LiberoECS_EntityMaster.h"

namespace Libero
{
	const ComponentID IComponent::GetID() const
	{
		return m_ID;
	}
	const EntityID IComponent::GetOwner() const
	{
		return m_Owner;
	}

	IEntity* IComponent::GetOwnerEntity() const
	{
		if (!m_pEntityMasterRef) return nullptr;

		return m_pEntityMasterRef->GetEntity(GetOwner());
	}

	void IComponent::SetActive(bool active)
	{
		m_IsActive = active;
	}

	bool IComponent::IsActive() const
	{
		return m_IsActive;
	}

	const bool IComponent::operator==(const IComponent& other) const
	{
		return !(*this != other);
	}

	const bool IComponent::operator!=(const IComponent& other) const
	{
		if (m_ID != other.m_ID) return true;
		if (m_Owner != other.m_Owner) return true;
		return false;
	}
	std::ofstream& IComponent::ToFile(std::ofstream& ofs) const
	{
		ofs << "- Unwritten Component: TODO... \n";
		ofs << "\n";

		return ofs;
	}
}

