#pragma once
#include "IComponent.h"

namespace Libero
{
	template <class Type>
	class Component : public IComponent
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual const ComponentTypeID GetStaticTypeID() const override;
		static const ComponentTypeID StaticGetStaticTypeID();
		static const ComponentTypeID m_Stat_Component_TypeID;

	private:
		// Deletion & Construction should happen in the ComponentMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};
}

#include "Component.inl"

