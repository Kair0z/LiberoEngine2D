#pragma once
#include <LiberoGame.h>
#include "BB_LevelParser.h"

class BubbleBobbleGame final : public Libero::LiberoGame
{ 
public:
	void Initialize() override final;

private:
	BB_EnviromentLoader m_EnviromentLoader;
};

