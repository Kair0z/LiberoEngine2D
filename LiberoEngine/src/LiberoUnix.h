#pragma once
#include "LiberoMacros.h"

// Declare as part of the Unix
#define DECLUNIX(x) friend class Libero::LiberoUnix<x>; \
					x();\
					~x();

namespace Libero
{
	template <typename UnixMember>
	class LiberoUnix
	{
	public:
		static UnixMember& Get()
		{
			static UnixMember instance;
			return instance;
		}

	protected:
		LiberoUnix() = default;
		~LiberoUnix() = default;

	public:
		ROFDEL(LiberoUnix)
	};
}


