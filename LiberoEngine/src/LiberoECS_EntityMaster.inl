#pragma once
#include "PCH.h"
#include "LiberoECS_EntityMaster.h"
#include "IEntity.h"
#include "LiberoECS_ComponentMaster.h"

// TODO: What's going on?

namespace Libero
{
	inline ECS_EntityMaster::ECS_EntityMaster(ECS_ComponentMaster* pComponentMaster)
		: m_PendingDestroyedEntities(1024)
		, m_NrPendingDestroyedEntities{ 0 }
		, m_pComponentMasterRef{ pComponentMaster }
	{
	}

	inline ECS_EntityMaster::~ECS_EntityMaster()
	{
		FlushDestroyedEntities();

		for (auto container : m_EntityMap)
		{
			delete container.second;
			container.second = nullptr;
		}
	}

	template<class Type, typename ...creationArgs>
	inline EntityID ECS_EntityMaster::CreateEntity(creationArgs&& ...constructionParams)
	{
		// 1: Get Objectpool for this type of component. If this one doesn't exist yet, you create it in GetEntityContainer<Type>()
		void* pObjMem = GetEntityContainer<Type>()->CreateObject();

		// 2: Create Unique EntityID for the look-up-table that links it to the pointer to the freshly allocated memory
		EntityID entityID = GenerateEntityID((Type*)pObjMem);

		IEntity* pEntity = new (pObjMem)Type(std::forward<creationArgs>(constructionParams)...);

		// Setup core ID:
		pEntity->m_ID = entityID;
		// Setup ComponentmasterReference & EntityMasterReference:
		pEntity->m_pComponentMasterRef = m_pComponentMasterRef;
		pEntity->m_pEntityMasterRef = this;

		// Initialize the entity:
		pEntity->Initialize();

		return entityID;
	}

	template<class Type>
	inline EntityContainer<Type>* ECS_EntityMaster::GetEntityContainer()
	{
		EntityTypeID typeID = Type::m_Stat_TypeID;
		auto it = m_EntityMap.find(typeID);

		EntityContainer<Type>* container = nullptr;
		if (it == m_EntityMap.end())
		{
			// If the container with this type doesn't exist yet...
			container = new EntityContainer<Type>();
			m_EntityMap[typeID] = container;
		}

		else container = (EntityContainer<Type>*)it->second;

		assert(container); // Else, failed to create container
		return container;
	}

	inline IEntity* ECS_EntityMaster::GetEntity(const EntityID ID)
	{
		return m_EntityHandleTable[ID];
	}

	inline void ECS_EntityMaster::DestroyEntity(const EntityID ID, bool immediate)
	{
		IEntity* pEntity = GetEntity(ID);

		const EntityTypeID typeID = pEntity->GetStaticTypeID();

		if (!immediate)
		{
			// Add the entity-pointer to the DestroyedEntity-waiting line
			if (m_NrPendingDestroyedEntities < m_PendingDestroyedEntities.size()) m_PendingDestroyedEntities[m_NrPendingDestroyedEntities++] = ID;
			else
			{
				m_PendingDestroyedEntities.push_back(ID);
				++m_NrPendingDestroyedEntities;
			}
		}
		else
		{
			auto it = m_EntityMap.find(typeID);
			if (it != m_EntityMap.end())
			{
				it->second->DestroyEntity(pEntity);
			}

			ReleaseEntityID(ID);
		}
	}

	inline void ECS_EntityMaster::FlushDestroyedEntities()
	{
		for (size_t i{}; i < m_NrPendingDestroyedEntities; ++i)
		{
			EntityID entityID = m_PendingDestroyedEntities[i];

			IEntity* pEntity = GetEntity(entityID);
			const EntityTypeID typeID{ pEntity->GetStaticTypeID() };

			auto it = m_EntityMap.find(typeID);
			if (it != m_EntityMap.end()) it->second->DestroyEntity(pEntity);

			ReleaseEntityID(entityID);
		}

		m_NrPendingDestroyedEntities = 0;
	}

	inline EntityID ECS_EntityMaster::GenerateEntityID(IEntity* pEntity)
	{
		return m_EntityHandleTable.AcquireHandle(pEntity);
	}

	inline void ECS_EntityMaster::ReleaseEntityID(EntityID id)
	{
		m_EntityHandleTable.ReleaseHandle(id);
	}
}

