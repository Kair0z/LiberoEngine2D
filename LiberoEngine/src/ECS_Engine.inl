#pragma once
#include "ECS_Engine.h"
#include "ECS_Includes.h"
#include "Event.h"

namespace Libero
{
	inline ECS_Engine::ECS_Engine()
		: m_pComponentMaster{nullptr}
		, m_pSystemMaster{nullptr}
		, m_pEntityMaster{nullptr}
		, m_IsInitialized{false}
	{

	}

	inline ECS_Engine::~ECS_Engine()
	{
		if (!m_IsInitialized) return;

		delete m_pSystemMaster;
		m_pSystemMaster = nullptr;

		delete m_pComponentMaster;
		m_pComponentMaster = nullptr;

		delete m_pEntityMaster;
		m_pEntityMaster = nullptr;
	}

	inline void ECS_Engine::Initialize()
	{
		m_pComponentMaster = new ECS_ComponentMaster{};
		m_pSystemMaster = new ECS_SystemMaster{};
		m_pEntityMaster = new ECS_EntityMaster{ m_pComponentMaster };

		m_pComponentMaster->Initialize(m_pEntityMaster);

		m_IsInitialized = true;
	}

	inline bool ECS_Engine::IsInitialized() const
	{
		return m_IsInitialized;
	}

	inline void ECS_Engine::Start()
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->Start();
	}

	inline void ECS_Engine::Update(float dt)
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->Update(dt);
	}

	inline void ECS_Engine::OnEvent(IEvent* pE)
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->OnEvent(pE);
	}

	inline void ECS_Engine::Draw() const
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->Draw();
	}

#pragma region EntityMasterFunctionality
	template<class Type, typename ...creationArgs>
	inline IEntity* ECS_Engine::NewEntity(creationArgs&&... constructionParams)
	{
		if (!m_IsInitialized) return nullptr;

		EntityID id = m_pEntityMaster->CreateEntity<Type, creationArgs...>(constructionParams...);

		if (id == id.INVALID) return nullptr;
		else return m_pEntityMaster->GetEntity(id);
	}

	template<class Type, typename ...creationArgs>
	inline Type* ECS_Engine::NewEntityAs(creationArgs&&... constructionParams)
	{
		if (!m_IsInitialized) return nullptr;

		return static_cast<Type*>(NewEntity<Type, creationArgs...>(constructionParams...));
	}

	inline void ECS_Engine::DestroyEntity(const EntityID id)
	{
		if (!m_IsInitialized) return; 

		// Destroy the entity & remove all it's components
		m_pEntityMaster->DestroyEntity(id, true);
		m_pComponentMaster->RemoveAllComponents(id);
	}

#pragma endregion

#pragma region SystemMasterFunctionality
	template<class SysType, typename ...creationArgs>
	inline void ECS_Engine::CreateSystem(creationArgs&& ...sysParams)
	{
		if (!m_IsInitialized) return;
		m_pSystemMaster->AddSystem<SysType, creationArgs...>(m_pComponentMaster, sysParams...);
	}

	template<class CompType>
	inline std::vector<CompType*> ECS_Engine::GetAllComponents()
	{ 
		if (!m_IsInitialized) return std::vector<CompType*>();
		return m_pComponentMaster->GetComponents<CompType>();
	}

#pragma endregion

}

