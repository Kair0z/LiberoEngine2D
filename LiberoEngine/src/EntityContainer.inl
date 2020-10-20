#pragma once
#include "PCH.h"
#include "EntityContainer.h"

namespace Libero
{
	template<class Type>
	inline void EntityContainer<Type>::DestroyEntity(IEntity* pObj)
	{
		// Call the destructor
		pObj->~IEntity();

		// Release the memory internally
		LibMemoryChunkAllocator<Type, ENTITY_T_CHUNK_SIZE>::DestroyObject(pObj);
	}
}