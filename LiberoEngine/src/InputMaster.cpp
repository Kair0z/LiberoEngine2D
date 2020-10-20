#include "PCH.h"
#include "InputMaster.h"

#include "EventMaster.h"
#include "MouseEvent.h"
#include "MiscEvent.h"
#include "KeyEvent.h"

namespace Libero
{
	void InputMaster::PollInput()
	{
		SDL_Event e;
		int x{}, y{};
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					EventMasterLocator::Locate()->AddToQueue<ExitEvent>();
					break;

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					EventMasterLocator::Locate()->AddToQueue<MouseMoveEvent>(MouseMoveEvent({ (float)x, (float)y }));
					break;

				case SDL_MOUSEBUTTONUP:
					SDL_GetMouseState(&x, &y);
					EventMasterLocator::Locate()->AddToQueue<MouseUpEvent>(MouseUpEvent({ (float)x, (float)y }));
					break;

				
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x, &y);
					EventMasterLocator::Locate()->AddToQueue<MouseDownEvent>(MouseDownEvent({ (float)x, (float)y }));
					break;

				case SDL_KEYDOWN:
					EventMasterLocator::Locate()->AddToQueue<KeyDownEvent>(KeyDownEvent({ e.key.keysym.sym }));
					break;

				case SDL_KEYUP:
					EventMasterLocator::Locate()->AddToQueue<KeyUpEvent>(KeyUpEvent({ e.key.keysym.sym }));
					break;
			}
			
		}
	}
}

