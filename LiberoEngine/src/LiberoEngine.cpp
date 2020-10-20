#include "PCH.h"
#include "LiberoEngine.h"
#include "EventDispatcher.h"
#include "MiscEvent.h"
#include "LiberoSystems.h"	

namespace Libero
{
	LiberoEngine::LiberoEngine() : m_Core{}, m_IsInitialized{false}, m_IsExit{false}, m_GameIsRunning{false}
	{ Initialize(); }
	LiberoEngine::~LiberoEngine()
	{ Cleanup(); }


	void LiberoEngine::Run()
	{
		m_Core.m_pSceneMaster->Initialize();

		while (!m_IsExit)
		{
			ProcessInput();
			ProcessEvents();
			Update();
			Render();
		}
	}


	void LiberoEngine::Update()
	{
		if (!m_IsInitialized) return;

		// Increase time:
		m_Core.m_pTimeMaster->Tick();
		float dt = (float)m_Core.m_pTimeMaster->GetElapsedSec();

		if (m_GameIsRunning) m_Core.m_pECSMaster->Update(dt);
	}

	void LiberoEngine::Render() const
	{
		if (!m_IsInitialized) return;

		m_Core.m_pRenderer->Open();

		m_Core.m_pECSMaster->Draw();
		m_Core.m_pUIMaster->Render();

		m_Core.m_pRenderer->Present();
	}

	void LiberoEngine::Initialize()
	{
		if (m_IsInitialized) return;

		// SDL:
		if (SDL_Init(SDL_INIT_VIDEO))
			throw std::runtime_error(std::string{ "SDL_Init Error: " } + SDL_GetError());

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
			throw std::runtime_error(std::string{ "SDL_IMG Error: " } + IMG_GetError());

		// GLFW:
		if (!glfwInit())
			throw std::runtime_error(std::string{ "glfwInit Error!" });

		// TTF:
		int ress = TTF_Init();
		if (ress == -1)
			throw std::runtime_error(std::string(TTF_GetError()));

		// Filemaster:
		m_Core.m_pFileMaster = new FileMaster();
		m_Core.m_pFileMaster->Initialize();
		FileMasterLocator::Provide(m_Core.m_pFileMaster);

		// Time:
		m_Core.m_pTimeMaster = new GameTime();

		// Contentmaster:
		m_Core.m_pContentMaster = new ContentMaster();
		m_Core.m_pContentMaster->Initialize();
		ContentMasterLocator::Provide(m_Core.m_pContentMaster);

		// Events:
		m_Core.m_pEventMaster = new EventMaster();
		m_Core.m_pEventMaster->Initialize();
		EventMasterLocator::Provide(m_Core.m_pEventMaster);

		// Physics:
		m_Core.m_pPhysicsMaster = new PhysicsMaster();
		m_Core.m_pPhysicsMaster->Initialize();
		PhysicsMasterLocator::Provide(m_Core.m_pPhysicsMaster);

		// ECS:
		m_Core.m_pECSMaster = new ECS_Engine();
		m_Core.m_pECSMaster->Initialize();
		ECSLocator::Provide(m_Core.m_pECSMaster);

		// Scenemaster:
		m_Core.m_pSceneMaster = new LiberoSceneMaster();
		SceneMasterLocator::Provide(m_Core.m_pSceneMaster);

		// Logger:
		m_Core.m_pLogger = new Logger();
		LoggerLocator::Provide(m_Core.m_pLogger);
		m_Core.m_pLogger->Log(Libero::Logger::LogType::Info, "Welcome to the Libero Engine! (v 1.0)");

		// Window:
		m_Core.m_pWindow = new LiberoWindow_SDL();
		m_Core.m_pWindow->Initialize("(x) Libero Engine (x)", CoreSettings::m_ApplicationDimensions);

		// Renderer:
#pragma region subWindow
		SDL_Rect subWindow{};
		subWindow.x = CoreSettings::m_GameWindowTopLeft.x;
		subWindow.y = CoreSettings::m_GameWindowTopLeft.y + 60;
		subWindow.w = CoreSettings::m_GameDimensions.x;
		subWindow.h = CoreSettings::m_GameDimensions.y;
#pragma endregion
		m_Core.m_pRenderer = new LiberoRenderer_SDL();
		m_Core.m_pRenderer->Initialize(m_Core.m_pWindow->GetSDLWindow(), &subWindow);
		m_Core.m_pRenderer->SetClearColor({ 0.f, 0.f, 0.f, 255.f });
		RendererLocator::Provide(m_Core.m_pRenderer);

		// UI:
		m_Core.m_pUIMaster = new ImmediateUI();
		m_Core.m_pUIMaster->Initialize(m_Core.m_pRenderer->GetSDLRenderer(), CoreSettings::m_ApplicationDimensions);
		UILocator::Provide(m_Core.m_pUIMaster);

		// Input:
		m_Core.m_pInputMaster = new InputMaster{};

		// Subjects:
		m_Core.m_pSubjectMaster = new SubjectMaster{};
		m_Core.m_pSubjectMaster->Initialize();

		SetupSystems();

		m_IsInitialized = true;
	}

	void LiberoEngine::Cleanup()
	{
		// Scenemaster:
		SafeDelete(m_Core.m_pSceneMaster);

		// ECS:
		SafeDelete(m_Core.m_pECSMaster);

		// ContentMaster:
		SafeDelete(m_Core.m_pContentMaster);

		// Filemaster:
		SafeDelete(m_Core.m_pFileMaster);

		// Events:
		SafeDelete(m_Core.m_pEventMaster);

		// Physics:
		SafeDelete(m_Core.m_pPhysicsMaster);

		// Logger:
		SafeDelete(m_Core.m_pLogger);

		// Window:
		SafeDelete(m_Core.m_pWindow);

		// Renderer:
		SafeDelete(m_Core.m_pRenderer);

		// UI:
		SafeDelete(m_Core.m_pUIMaster);

		// Time:
		SafeDelete(m_Core.m_pTimeMaster);

		// Inpute:
		SafeDelete(m_Core.m_pInputMaster);

		SafeDelete(m_pGame);

		SafeDelete(m_Core.m_pSubjectMaster);

		glfwTerminate();
	}

	// Setting up core systems:
	void LiberoEngine::SetupSystems()
	{
		if (!m_Core.m_pECSMaster->IsInitialized()) return;

		m_Core.m_pECSMaster->CreateSystem<SysSpriteAnimator>();
		m_Core.m_pECSMaster->CreateSystem<SysRendering>();
		m_Core.m_pECSMaster->CreateSystem<SysDebugRendering>();
		m_Core.m_pECSMaster->CreateSystem<SysInput>();
		m_Core.m_pECSMaster->CreateSystem<SysMovement>();
		m_Core.m_pECSMaster->CreateSystem<SysPhysics>();
		m_Core.m_pECSMaster->CreateSystem<SysBulletMovement>();
	}

	void LiberoEngine::ProcessInput()
	{
		if (!m_IsInitialized) return;

		m_Core.m_pInputMaster->PollInput();
		m_Core.m_pUIMaster->ProcessInput();
	}

	void LiberoEngine::ProcessEvents()
	{
		for (IEvent* pEvent : m_Core.m_pEventMaster->GetQueue())
		{
			if (pEvent->IsHandled()) continue;

			// My On Event
			OnEvent(pEvent);
			
			// Objects On Event:
			m_Core.m_pECSMaster->OnEvent(pEvent);

			// SceneMaster On Event:
		}

		float dt = (float)m_Core.m_pTimeMaster->GetElapsedSec();
		// Flushing events:
		m_Core.m_pEventMaster->Update(dt);
	}

	void LiberoEngine::OnEvent(IEvent* pEvent)
	{
		EventSignalDispatcher dispatcher{ pEvent };
		EventFinalDispatcher dispatcher2{ pEvent };

		dispatcher.Dispatch<ExitEvent>([=]() {m_IsExit = true; }, true);
		dispatcher.Dispatch<GamePlayEvent>([=]() { StartGame(); });
		dispatcher.Dispatch<GameStopEvent>([=]() { StopGame(); });
		dispatcher2.Dispatch<NextSceneEvent>(EVDISP_FINAL_MEMBER_BIND(LiberoEngine::ChangeScene));
	}

	void LiberoEngine::StartGame()
	{
		if (m_GameIsRunning) return;

		m_Core.m_pSceneMaster->Start();
		m_GameIsRunning = true;

		m_Core.m_pECSMaster->Start();
	}

	void LiberoEngine::StopGame()
	{
		if (!m_GameIsRunning) return;

		m_Core.m_pSceneMaster->Stop(); 
		m_GameIsRunning = false;
	}

	void LiberoEngine::ChangeScene(NextSceneEvent*)
	{
		m_Core.m_pSceneMaster->IncrementActiveScene();
		// restart new objects:
		m_Core.m_pECSMaster->Start();
	}
}


