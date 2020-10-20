#pragma once
#include "ECS_Defines.h"
#include "LiberoMacros.h"
#include "LibMemoryChunkAllocator.h"
#include "IComponent.h"

namespace Libero
{
	class IComponentContainer
	{
	public:
		virtual ~IComponentContainer() = default;
		virtual void DestroyComponent(IComponent*& pComponent) = 0;
	};

	template <class T>
	class ComponentContainer :
		public IComponentContainer,
		public Libero::LibMemoryChunkAllocator<T, COMPONENT_T_CHUNK_SIZE>
	{
	public:
		ROFDEL(ComponentContainer)

		ComponentContainer() = default;
		virtual ~ComponentContainer() = default;

		virtual void DestroyComponent(IComponent*& pComp) override
		{
			pComp->~IComponent();
			this->DestroyObject(pComp);
			pComp = nullptr;
		}
	};
}
