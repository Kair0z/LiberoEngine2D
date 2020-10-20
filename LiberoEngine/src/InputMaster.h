#pragma once
#include "LiberoMacros.h"

#include <vector>

class IEvent;

namespace Libero
{
	class InputMaster
	{
	public:
		void PollInput();

		ROFDEL(InputMaster)
	};
}


