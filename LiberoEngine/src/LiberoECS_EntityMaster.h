#pragma once
#include "ECS_Defines.h"
#include "EntityContainer.h"
#include "LiberoMemory.h"

// STL:
#include <vector>
#include <unordered_map>

namespace Libero
{
	class ComponentMaster;
	class ECS_EntityMaster final
	{
	public:
		ECS_EntityMaster(ECS_ComponentMaster* pComponentMaster);
		~ECS_EntityMaster();

		// Functionality:
		template <class Type, typename... creationArgs>
		EntityID CreateEntity(creationArgs&&... constructionParams);
		IEntity* GetEntity(const EntityID ID);
		void DestroyEntity(const EntityID ID, bool immediate = false);

		void FlushDestroyedEntities();
		
	private: 
//****************
#pragma region PrivateDefines
		using EntityMap = std::unordered_map<EntityTypeID, IEntityContainer*>;
		using ObjectLookupTable = std::unordered_map<EntityID, IEntity*>;
#ifdef _WIN64
		using EntityHandleTable = HandleTable<IEntity, Handle64>;
#else
		using EntityHandleTable = HandleTable<IEntity, Handle32>;
#endif
#pragma endregion
//****************

//****************
#pragma region Data

	private: // Data:
		// Maps the type to the correct EntityContainer:
		EntityMap m_EntityMap;
		EntityHandleTable m_EntityHandleTable;

		std::vector<EntityID> m_PendingDestroyedEntities;
		size_t m_NrPendingDestroyedEntities;

		ECS_ComponentMaster* m_pComponentMasterRef;

#pragma endregion
//****************

//****************
#pragma region Private Methods
	private: // Private Methods:
		template <class Type>
		EntityContainer<Type>* GetEntityContainer(); // Get (or create if nonexistent) container of Entities<Type>

		EntityID GenerateEntityID(IEntity* pEntity); // Let the table generate a unique EntityID
		void ReleaseEntityID(EntityID id);			// Let the table release the existing unique EntityID
#pragma endregion
//****************

	public: // ROF
		ECS_EntityMaster(const ECS_EntityMaster&) = delete;
		ECS_EntityMaster(ECS_EntityMaster&&) = delete;
		ECS_EntityMaster& operator=(const ECS_EntityMaster&) = delete;
		ECS_EntityMaster& operator=(ECS_EntityMaster&&) = delete;
	};
}

#include "LiberoECS_EntityMaster.inl"


