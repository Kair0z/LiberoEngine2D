#pragma once
#include "ECS_Defines.h"

namespace Libero
{
	class ECS_ComponentMaster;
	class ECS_EntityMaster;
	class IComponent;

	class IEntity
	{
	public:
		IEntity() = default;
		virtual ~IEntity() = default;
		virtual void Initialize() = 0;

		const EntityID GetID() const;
		virtual const EntityTypeID GetStaticTypeID() const = 0;

		void SetActive(bool active);
		bool IsActive() const;

		template <class CompType>
		CompType* GetComponent() const;
		std::vector<IComponent*> GetComponents() const;

		template <class CompType, class ...Param>
		CompType* AddComponent(Param... parameters);

		template <class CompType>
		void RemoveComponent();

		template <class CompType>
		bool HasComponent() const;

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		bool operator==(const IEntity& other) const;
		bool operator!=(const IEntity& other) const;
		bool operator==(const IEntity* pOther) const;
		bool operator!=(const IEntity* pOther) const;

	protected:
		EntityID m_ID = g_EntityID_Invalid;
		bool m_IsEnabled = true;
		bool m_IsActive = true;

		friend class ECS_EntityMaster;

		// Get set at creation in entityMaster
		ECS_EntityMaster* m_pEntityMasterRef = nullptr;
		ECS_ComponentMaster* m_pComponentMasterRef = nullptr;
	};
}

#include "IEntity.inl"

