#pragma once
#include "Entity.h"

namespace Libero
{
	template<class Type>
	inline const EntityTypeID Entity<Type>::GetStaticTypeID() const
	{
		return m_Stat_TypeID;
	}

	template<class Type>
	inline const EntityTypeID Entity<Type>::StaticGetStaticTypeID()
	{
		return m_Stat_TypeID;
	}
}
