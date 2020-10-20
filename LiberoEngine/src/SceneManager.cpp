#include "PCH.h"
#include "SceneManager.h"
#include "LiberoScene.h"
#include "Logger.h"

namespace Libero
{
	LiberoSceneMaster::LiberoSceneMaster()
		: m_ActiveSceneIdx{}
	{
		m_pScenes.reserve(SCENEMANAGER_MAX_AMOUNT_SCENES);
	}

	LiberoSceneMaster::~LiberoSceneMaster()
	{
		for (LiberoScene* pScene : m_pScenes)
		{
			delete pScene;
			pScene = nullptr;
		}

		for (LiberoScene* pScene : m_pOriginalScenes)
		{
			delete pScene;
			pScene = nullptr;
		}

		m_pScenes.clear();
		m_pOriginalScenes.clear();
	}

	void LiberoSceneMaster::Initialize()
	{
		if (m_pScenes.empty()) return;

		m_pScenes[m_ActiveSceneIdx]->Initialize(); // Initialize active scene
		m_StartSceneIdx = m_ActiveSceneIdx;
	}

	void LiberoSceneMaster::Start()
	{
		if (m_pScenes.empty()) return;
		m_pScenes[m_ActiveSceneIdx]->Start(); // Start the active scene
	}

	void LiberoSceneMaster::Stop()
	{
		if (m_pScenes.empty()) return;

		for (size_t i{}; i < m_pScenes.size(); ++i)
		{
			delete m_pScenes[i];
			m_pScenes[i] = nullptr;

			// Set each scene to a copy of the original scenes: 
			// And initialize
			m_pScenes[i] = m_pOriginalScenes[i]->Clone();
		}

		m_ActiveSceneIdx = m_StartSceneIdx;
		m_pScenes[m_ActiveSceneIdx]->Initialize();
	}

	void LiberoSceneMaster::HandleEvent(IEvent* pE)
	{
		if (m_pScenes.empty()) return;

		m_pScenes[m_ActiveSceneIdx]->OnEvent(pE);
	}

	void LiberoSceneMaster::RenderActiveScene() const
	{
		if (!m_pScenes.empty())
		m_pScenes[m_ActiveSceneIdx]->Render();
	}

	void LiberoSceneMaster::SetActiveScene(const size_t idx)
	{
		if (idx == m_ActiveSceneIdx) return;
		if (idx >= m_pScenes.size())
		{
			LoggerLocator::Locate()->Log(Logger::LogType::Warning, "SceneManager::AddScene >> Tried to add over the max amount of Scenes!");
			return;
		}

		// Delete previous scene instance:
		delete m_pScenes[m_ActiveSceneIdx];
		m_pScenes[m_ActiveSceneIdx] = nullptr;
		m_pScenes[m_ActiveSceneIdx] = m_pOriginalScenes[m_ActiveSceneIdx]->Clone();

		// Set new active sceneIdx
		m_ActiveSceneIdx = idx;

		// Initialize the new scene:
		m_pScenes[m_ActiveSceneIdx]->Initialize();
	}

	void LiberoSceneMaster::IncrementActiveScene()
	{
		size_t newIdx = m_ActiveSceneIdx + 1;
		if (newIdx >= m_pScenes.size()) newIdx = 0;

		SetActiveScene(newIdx);
	}

	void LiberoSceneMaster::ToggleActiveScene()
	{
		size_t newIdx = m_ActiveSceneIdx + 1;
		if (newIdx >= m_pScenes.size()) newIdx = 0;
		SetActiveScene(newIdx);
	}

	LiberoScene* LiberoSceneMaster::GetActiveScene() const
	{
		return m_pScenes[m_ActiveSceneIdx];
	}

	size_t LiberoSceneMaster::GetActiveSceneIdx() const
	{
		return m_ActiveSceneIdx;
	}

	bool LiberoSceneMaster::IsEmpty() const
	{
		return m_pScenes.empty();
	}
}

