
#include <LiberoEngine.h>
#include "BubbleBobbleGame.h"

#ifdef main
#undef main
#endif

int main()
{
	Libero::LiberoEngine engine{};

	engine.LoadGame<BubbleBobbleGame>();

	engine.Run();
}