#pragma once

#pragma region Includes
#include "ImmediateUI.h"
#include "InputMaster.h"
#include "SceneManager.h"
#include "MemoryMaster.h"
#include "LiberoRenderer_SDL.h"
#include "LiberoWindowBase.h"
#include "CoreSettings.h"
#include "ECS_Engine.h"
#include "Logger.h"
#include "RendererOpenGL.h"
#include "GameTime.h"
#include "EventMaster.h"
#include "FileMaster.h"
#include "PhysicsMaster.h"
#include "ILiberoLocator.h"
#include "SubjectMaster.h"
#include "ContentMaster.h"
#pragma endregion

namespace Libero
{
	struct Core final
	{
		ECS_Engine* m_pECSMaster			= nullptr;
		InputMaster* m_pInputMaster			= nullptr;
		GameTime* m_pTimeMaster				= nullptr;
		LiberoWindow_SDL* m_pWindow			= nullptr;
		LiberoRenderer_SDL* m_pRenderer		= nullptr;
		LiberoSceneMaster* m_pSceneMaster	= nullptr;
		EventMaster* m_pEventMaster			= nullptr;
		PhysicsMaster* m_pPhysicsMaster		= nullptr;
		ImmediateUI* m_pUIMaster			= nullptr;
		Logger* m_pLogger					= nullptr;
		FileMaster* m_pFileMaster			= nullptr;
		SubjectMaster* m_pSubjectMaster		= nullptr;
		ContentMaster* m_pContentMaster		= nullptr;
	};
}




