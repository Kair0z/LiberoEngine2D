#include "LibMemoryChunkAllocator.h"
#include "LibPoolAllocator.h"
#include "MemoryMaster.h"
#include "Logger.h"

#define ChunkAllocatorTemplate template<class ObjType, size_t MaxChunkObj>

namespace Libero
{
	ChunkAllocatorTemplate
	inline LibMemoryChunkAllocator<ObjType, MaxChunkObj>::LibMemoryChunkAllocator()
	{
		MemoryMaster& ECSMemory = MemoryMaster::Get();

		// Create First chunk:
		LibPoolAllocator* pAllocator = new LibPoolAllocator(m_ChunkAllocationSize, ECSMemory.Allocate(m_ChunkAllocationSize), sizeof(ObjType));
		MemoryChunk* pNewChunk = new MemoryChunk(pAllocator);
		m_ChunkList.push_back(pNewChunk);
	}

	ChunkAllocatorTemplate
	inline LibMemoryChunkAllocator<ObjType, MaxChunkObj>::~LibMemoryChunkAllocator()
	{
		// For every chunk:
		for (auto pChunk : m_ChunkList)
		{
			// Destroy all objects:
			for (ObjType* pObj : pChunk->m_pObjects) pObj->~ObjType();
			
			// Clear the chunk:
			pChunk->m_pObjects.clear();

			// Let the memorymaster release the memory:
			MemoryMaster& ECSMemory = MemoryMaster::Get();
			ECSMemory.Free((void*)pChunk->m_pAllocator->GetBaseAdress());

			// Delete the chunk obj
			delete pChunk;
			pChunk = nullptr;
		}
	}

	ChunkAllocatorTemplate
	inline void* LibMemoryChunkAllocator<ObjType, MaxChunkObj>::CreateObject()
	{
		MemoryMaster& ECSMemory = MemoryMaster::Get();
		void* pSlot = nullptr;

		for (MemoryChunk* pChunk: m_ChunkList)
		{
			size_t amount = MaxChunkObj;
			amount;

			// If the amount of objects in the chunk > 
			if (pChunk->m_pObjects.size() >= MaxChunkObj)
			{
				continue;
			}

			pSlot = pChunk->m_pAllocator->Allocate(sizeof(ObjType));
			if (pSlot)
			{
				pChunk->m_pObjects.push_back((ObjType*)pSlot);
				break;
			}
		}

		if (pSlot == nullptr)
		{
			// No free slot has been found, all chunks are full... allocate new one
			LibPoolAllocator* pNewPool = new LibPoolAllocator(m_ChunkAllocationSize, ECSMemory.Allocate(m_ChunkAllocationSize), sizeof(ObjType));
			MemoryChunk* pNewChunk = new MemoryChunk(pNewPool);

			m_ChunkList.push_back(pNewChunk);
			pSlot = pNewChunk->m_pAllocator->Allocate(sizeof(ObjType));

			assert(pSlot);

			pNewChunk->m_pObjects.clear();
			pNewChunk->m_pObjects.push_back((ObjType*)pSlot);
		}

		return pSlot;
	}

	ChunkAllocatorTemplate
	inline void LibMemoryChunkAllocator<ObjType, MaxChunkObj>::DestroyObject(void* pObj)
	{
		char* asCharPtr = (char*)pObj;

		for (MemoryChunk* pChunk : m_ChunkList)
		{
			if (pChunk->m_pStart <= asCharPtr && asCharPtr < pChunk->m_pEnd)
			{
				// No need to call destructor --> already called by delete
				pChunk->m_pObjects.remove((ObjType*)pObj);
				pChunk->m_pAllocator->Free(pObj);
				pObj = nullptr;
				return;
			}
		}

		// This is bad!
		assert(false);
	}
}
