#pragma once
#include "Component.h"
#include "FamilyTypeID.h"

namespace Libero
{
	template<class Type>
	const ComponentTypeID Component<Type>::m_Stat_Component_TypeID = FamilyTypeID<IComponent>::Get<Type>();

	template<class Type>
	inline const ComponentTypeID Component<Type>::GetStaticTypeID() const
	{
		return m_Stat_Component_TypeID;
	}

	template<class Type>
	inline const ComponentTypeID Component<Type>::StaticGetStaticTypeID()
	{
		return m_Stat_Component_TypeID;
	}
}


