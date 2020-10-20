#include "BubbleBobbleGame.h"
#include "BBLevel.h"

void BubbleBobbleGame::Initialize()
{
	m_EnviromentLoader.ParseBlocks();

	for (size_t i{}; i < 3; ++i)
	{
		AddScene<BBLevel>(i, m_EnviromentLoader);
	}

}
