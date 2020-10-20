#include "Sys_ScoreLogger.h"
#include "SubjectMaster.h"

using namespace Libero;

Sys_ScoreLogger::Sys_ScoreLogger()
{
	SubjectMasterLocator::Locate()->SubToSubject(SubjectMaster::Category::Score, this);
}

void Sys_ScoreLogger::OnNotify()
{
	LoggerLocator::Locate()->LogInfo("Score up!");
}
