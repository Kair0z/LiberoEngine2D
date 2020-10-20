#include "PCH.h"
#include "MemoryMaster.h"
#include "LibStackAllocator.h"

namespace Libero
{
	MemoryMaster::MemoryMaster()
		: m_pECSMemoryBase{}
		, m_pMainAllocator{nullptr}
		, m_IsInitialized{false}
	{
		if (!m_IsInitialized) InitializeMemory();
	}

	MemoryMaster::~MemoryMaster()
	{
		m_pMainAllocator->Clear();

		delete m_pMainAllocator;
		m_pMainAllocator = nullptr;

		free(m_pECSMemoryBase);
		m_pECSMemoryBase = nullptr;
	}

	bool MemoryMaster::InitializeMemory()
	{
		if (m_IsInitialized) return true;

		// Allocate all the memory for the ECS (big chungus)
		m_pECSMemoryBase = malloc(MemoryMaster::MEMORY_CAPACITY);
		if (!m_pECSMemoryBase) return false; // TODO: do something (better) when m_pECSMemoryBase isn't nullptr --> Not able to get the memory we need...

			m_pMainAllocator = new LibStackAllocator(MemoryMaster::MEMORY_CAPACITY, m_pECSMemoryBase);
		if (!m_pMainAllocator) return false; // TODO: Do something (better) when the LibStackAllocator cannot be created

		m_IsInitialized = true;
		return true;
	}

	void* MemoryMaster::Allocate(const size_t size)
	{
		if (!m_IsInitialized) return nullptr;

		void* pMem = m_pMainAllocator->Allocate(size);
		return pMem;
	}

	void MemoryMaster::Free(void* pMem)
	{
		if (!m_IsInitialized) return;

		m_pMainAllocator->Free(pMem);
	}
}

