#pragma once
#include "IEntity.h"
#include "LiberoECS_ComponentMaster.h"
#include "LiberoECS_EntityMaster.h"

namespace Libero
{
	inline const EntityID IEntity::GetID() const
	{
		return m_ID;
	}

	inline void IEntity::SetActive(bool active)
	{
		if (m_IsEnabled == active) return;

		// Set new activity
		m_IsEnabled = active;

		// Call enable / disable
		if (!active) OnDisable();
		else OnEnable();
	}

	inline bool IEntity::IsActive() const
	{
		return m_IsActive;
	}

	inline std::vector<IComponent*> IEntity::GetComponents() const
	{
		if (!m_pComponentMasterRef) return std::vector<IComponent*>{};

		return m_pComponentMasterRef->GetComponents(m_ID);
	}

	template <class CompType>
	inline CompType* IEntity::GetComponent() const
	{
		if (!m_pComponentMasterRef) return nullptr;

		return m_pComponentMasterRef->GetComponent<CompType>(m_ID);
	}

	template<class CompType, class ...Param>
	inline CompType* IEntity::AddComponent(Param ...parameters)
	{
		if (!m_pComponentMasterRef) return nullptr;
		if (HasComponent<CompType>()) return GetComponent<CompType>();
		// TODO: if we already have the component, should we overwrite? or return the already existing one?

		CompType* pComponent = m_pComponentMasterRef->AddComponent<CompType>(m_ID, std::forward<Param>(parameters)...);
		return pComponent;
	}

	template<class CompType>
	inline void IEntity::RemoveComponent()
	{
		if (!m_pComponentMasterRef) return;

		m_pComponentMasterRef->RemoveComponent<CompType>(m_ID);
	}

	template<class CompType>
	inline bool IEntity::HasComponent() const
	{
		return (GetComponent<CompType>() != nullptr);
	}

#pragma region EntityComp
	inline bool IEntity::operator==(const IEntity& other) const
	{
		return m_ID == other.m_ID;
	}

	inline bool IEntity::operator==(const IEntity* pOther) const
	{
		return m_ID == pOther->m_ID;
	}

	inline bool IEntity::operator!=(const IEntity& other) const
	{
		return !(*this == other);
	}

	inline bool IEntity::operator!=(const IEntity* pOther) const
	{
		return !(this == pOther);
	}
#pragma endregion
}


