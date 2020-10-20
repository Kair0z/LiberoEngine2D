#pragma once
#include "LiberoECS_SystemMaster.h"

#include "ISystem.h"
#include "LibLinearAllocator.h"
#include "LiberoECS_ComponentMaster.h"
#include "Event.h"

namespace Libero
{
	inline ECS_SystemMaster::ECS_SystemMaster()
		: m_pSystemAlloc{ nullptr }
		, m_pSystemsToWork()
		, m_Systems()
	{
		size_t size = ECS_SYSTEM_MEMORY_SIZE;
		MemoryMaster& memMaster = LiberoUnix<MemoryMaster>::Get();

		m_pSystemAlloc = new Libero::LibLinearAllocator(size, memMaster.Allocate(size));
	}

	inline ECS_SystemMaster::~ECS_SystemMaster()
	{
		for (std::vector<ISystem*>::reverse_iterator it = m_pSystemsToWork.rbegin(); it != m_pSystemsToWork.rend(); ++it)
		{
			(*it)->~ISystem();
			*it = nullptr;
		}

		m_pSystemsToWork.clear();
		m_Systems.clear();

		MemoryMaster& memMaster = LiberoUnix<MemoryMaster>::Get();

		// Allocator:
		memMaster.Free((void*)m_pSystemAlloc->GetBaseAdress());
		delete m_pSystemAlloc;
		m_pSystemAlloc = nullptr;
	}

	inline void ECS_SystemMaster::Start()
	{
		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->Start();
		}
	}

	inline void ECS_SystemMaster::Update(float dt)
	{
		// PREUPDATE:
		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->PreUpdate(dt);
		}

		// UPDATE:
		for (ISystem* pSys : m_pSystemsToWork)
		{
			// Increase time since laste update:
			pSys->m_TimeSinceLastUpdate += dt;

			// if the update interval is exceeded, the system needs an update (as well if the interval is negative:)
			bool isIntervalExceeded = (pSys->m_UpdateInterval > 0.0f) && (pSys->m_TimeSinceLastUpdate > pSys->m_UpdateInterval);
			pSys->m_DoesNeedUpdate = (pSys->m_UpdateInterval < 0.0f) || isIntervalExceeded;

			if (pSys->m_DoesNeedUpdate && pSys->m_IsEnabled)
			{
				pSys->Update(dt);
				pSys->m_TimeSinceLastUpdate = 0.0f;
			}
		}

		// POSTUPDATE:
		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->PostUpdate(dt);
		}
	}

	inline void ECS_SystemMaster::Draw() const
	{
		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->Draw();
		}

		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->PostDraw();
		}
	}

	inline void ECS_SystemMaster::OnEvent(IEvent* pE)
	{
		for (ISystem* pSys : m_pSystemsToWork)
		{
			if (pSys->m_IsEnabled) pSys->OnEvent(pE);
		}
	}

	template<class SysType, class ...Args>
	inline SysType* ECS_SystemMaster::AddSystem(ECS_ComponentMaster* pCompMaster, Args&& ...sysArgs)
	{
		const SysTypeID typeID = SysType::m_Stat_System_TypeID;

		auto it = m_Systems.find(typeID);

		// If the system exists in m_Systems already, then just return that system --> no duplicates
		if (it != m_Systems.end() && it->second != nullptr) return (SysType*)it->second;

		SysType* pSystem{ nullptr };
		alignof(SysType);
		void* pSysMem = m_pSystemAlloc->Allocate(sizeof(SysType));
		if (pSysMem != nullptr)
		{
			// Create the System:
			pSystem = new (pSysMem)SysType(std::forward<Args>(sysArgs)...);
			pSystem->m_pSystemMasterRef = this;
			pSystem->m_pComponentMasterRef = pCompMaster;

			// Register in the Systemmap:
			m_Systems[typeID] = pSystem;
		}
		else assert(false); // TODO: catch not being able to allocate memory for the system

		// Add to workorder:
		m_pSystemsToWork.emplace_back(pSystem);

		return pSystem;
	}

}

