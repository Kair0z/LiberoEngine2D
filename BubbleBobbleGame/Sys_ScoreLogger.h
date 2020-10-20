#pragma once
#include "System.h"
#include "IObserver.h"

class Sys_ScoreLogger : 
	public Libero::System<Sys_ScoreLogger>,
	public Libero::IObserver
{
public:
	Sys_ScoreLogger();

	void OnNotify() override;

private:

};

