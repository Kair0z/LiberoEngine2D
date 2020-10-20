#pragma once
#include "LiberoMacros.h"
#include "LiberoUnix.h"
#include <list>

#define ECS_MEMORY_CAPACITY 134217728 * 2;

namespace Libero
{
	class LibStackAllocator;
	class MemoryMaster : public LiberoUnix<MemoryMaster>
	{
	private:
		DECLUNIX(MemoryMaster)

	public:
		bool InitializeMemory();

		void* Allocate(const size_t size);
		void Free(void* pMem);

		static constexpr size_t MEMORY_CAPACITY = ECS_MEMORY_CAPACITY;

	private:
		void* m_pECSMemoryBase;

		LibStackAllocator* m_pMainAllocator;
		bool m_IsInitialized;

	public:
		ROFDEL(MemoryMaster)
	};
}


