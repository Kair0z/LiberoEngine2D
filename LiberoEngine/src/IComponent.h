#pragma once
#include "ECS_Defines.h"
#include <fstream>

namespace Libero
{
	class ECS_EntityMaster;
	class IEntity;

	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;

		virtual const ComponentTypeID GetStaticTypeID() const = 0;

		const ComponentID GetID() const;
		const EntityID GetOwner() const;

		IEntity* GetOwnerEntity() const;

		void SetActive(bool active);
		bool IsActive() const;

		const bool operator==(const IComponent& other) const;
		const bool operator!=(const IComponent& other) const;

		// Writing to file:
		virtual std::ofstream& ToFile(std::ofstream& ofs) const;

	protected:
		ComponentID m_ID = g_ComponentID_Invald;
		ComponentID m_HashID;

		EntityID m_Owner;

		bool m_IsActive = true;
		
	private:
		// Only componentmaster can create these (delete operators deleted in Component class)
		friend class ECS_ComponentMaster;
		ECS_EntityMaster* m_pEntityMasterRef;
	};
}


