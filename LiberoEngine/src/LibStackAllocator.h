#pragma once
#include "ILibAllocator.h"

namespace Libero
{
	class LibStackAllocator : public ILibAllocator
	{
	public:
		LibStackAllocator(const size_t size, const void* pBase);
		virtual ~LibStackAllocator();

		virtual void* Allocate(const size_t size) override;
		virtual void Free(void*) override;
		virtual void Clear() override;
	};
}


