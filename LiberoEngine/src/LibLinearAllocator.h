#pragma once
#include "ILibAllocator.h"

// Memory can only be freed by clearing all allocations

namespace Libero
{
	class LibLinearAllocator : public ILibAllocator
	{
	public:
		LibLinearAllocator(const size_t size, const void* pBase) : ILibAllocator(size, pBase){}
		virtual ~LibLinearAllocator();

		virtual void* Allocate(const size_t size) override;
		virtual void Free(void*) override;
		virtual void Clear() override;
	};
}


