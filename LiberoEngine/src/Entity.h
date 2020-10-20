#pragma once
#include "IEntity.h"
#include "FamilyTypeID.h"

namespace Libero
{
	template <class Type>
	class Entity : public IEntity
	{
	public:
		virtual const EntityTypeID GetStaticTypeID() const override;
		static const EntityTypeID StaticGetStaticTypeID();
		static const EntityTypeID m_Stat_TypeID;

	private:
		// Construction & deletion should happen in the EntityMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};

	template <class Type>
	const EntityTypeID Entity<Type>::m_Stat_TypeID = FamilyTypeID<IEntity>::Get<Type>();
}

#include "Entity.inl"



