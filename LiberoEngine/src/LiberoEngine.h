#pragma once
#include "LiberoMacros.h"
#include "LiberoCore.h"
#include "LiberoGame.h"

namespace Libero
{
	class IEvent;
	class NextSceneEvent;
	class LiberoEngine final
	{
		ROFDEL(LiberoEngine);

	public:
		LiberoEngine();
		~LiberoEngine();

		void Run();

		template<class Game>
		void LoadGame();

	private:
		Core m_Core;
		bool m_IsInitialized;
		bool m_GameIsRunning;
		bool m_IsExit;

		LiberoGame* m_pGame;

	private:
		void Initialize();
		void Cleanup();

		void ProcessInput();
		void ProcessEvents();
		void Update();
		void Render() const;

		void StartGame();
		void StopGame();
		void ChangeScene(NextSceneEvent* pEvent);

		void OnEvent(IEvent* pEvent);

		void SetupSystems();
	};

	template <class Game>
	void LiberoEngine::LoadGame()
	{
		if (!m_IsInitialized) return;

		m_pGame = new Game();
		m_pGame->Initialize();
	}
}

