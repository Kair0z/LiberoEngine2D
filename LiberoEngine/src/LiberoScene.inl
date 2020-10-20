#include "PCH.h"
#include "LiberoScene.h"
#include "ECS_Engine.h"
#include "GameObject.h"
#include "Logger.h"

namespace Libero
{
	inline LiberoScene::LiberoScene(const std::string& name)
		: m_Name{ name }
	{
	}

	inline LiberoScene::~LiberoScene()
	{
		for (GameObject* pObject : m_pObjects)
		{
			DestroyGameObject(pObject);
		}

		m_pObjects.clear();
	}

	inline LiberoScene::LiberoScene(const LiberoScene& other)
	{
		m_Name = other.m_Name;
	}

	inline LiberoScene& LiberoScene::operator=(const LiberoScene& other)
	{
		m_Name = other.m_Name;
	}

	inline GameObject* LiberoScene::AddGameObject()
	{
		ECS_Engine* pEngine = ECSLocator::Locate();
		GameObject* pObj = pEngine->NewEntityAs<GameObject>();

		m_pObjects.push_back(pObj);

		return pObj;
	}

	template<class SysType, typename ...creationArgs>
	inline void LiberoScene::CreateSystem(creationArgs&& ...sysParams)
	{
		ECS_Engine* pEngine = ECSLocator::Locate();
		pEngine->CreateSystem<SysType, creationArgs...>(sysParams...);
	}

	inline void LiberoScene::DestroyGameObject(GameObject* pObject)
	{
		if (!pObject) return;

		ECS_Engine* pEngine = ECSLocator::Locate();

		auto it = std::find(m_pObjects.cbegin(), m_pObjects.cend(), pObject);
		if (it == m_pObjects.cend())
		{
			LoggerLocator::Locate()->LogWarning("LiberoScene::DestroyGameObject() >> Tried destroying an invalid GameObject!");
			return;
		}

		pEngine->DestroyEntity(pObject->GetID());
	}

	inline const std::vector<GameObject*>& LiberoScene::GetObjects() const
	{
		return m_pObjects;
	}

	inline const std::string& LiberoScene::GetName() const
	{
		return m_Name;
	}
}