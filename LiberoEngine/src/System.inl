#pragma once
#include "System.h"
#include "FamilyTypeID.h"

namespace Libero
{
	template<class SysType>
	const SysTypeID System<SysType>::m_Stat_System_TypeID = FamilyTypeID<ISystem>::Get<SysType>();

	template <class SysType>
	const SysTypeID System<SysType>::StaticGetStaticSystemTypeID()
	{
		return m_Stat_System_TypeID;
	}
}
