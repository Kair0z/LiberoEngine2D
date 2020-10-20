#pragma once
#include "ISystem.h"

namespace Libero
{
	template <class SysType>
	class System : public ISystem
	{
	public:
		static const SysTypeID StaticGetStaticSystemTypeID();
		static const SysTypeID m_Stat_System_TypeID;

	private:

		// Construction & deletion should happen in the SystemMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};
}

#include "System.inl"
