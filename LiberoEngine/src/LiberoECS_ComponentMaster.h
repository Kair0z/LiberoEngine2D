#pragma once
#include "ECS_Defines.h"
#include "ComponentContainer.h"

// STL:
#include <vector>
#include <unordered_map>

namespace Libero
{
	class IComponent;

	class ECS_ComponentMaster final
	{
	public:
		ECS_ComponentMaster();
		~ECS_ComponentMaster();

		template <class Type, class ...Args>
		Type* AddComponent(const EntityID eID, Args&&... args);

		template <class Type>
		Type* GetComponent(const EntityID eID);
		std::vector<IComponent*> GetComponents(const EntityID eID);

		template <class Type>
		std::vector<Type*> GetComponents();

		template <class Type>
		void RemoveComponent(const EntityID eID);
		void RemoveAllComponents(const EntityID eID);

		void Initialize(ECS_EntityMaster* pEntityMasterReft);

	private:
//***************************
#pragma region PrivateDefines
		using ComponentMap = std::unordered_map<ComponentTypeID, IComponentContainer*>;
#pragma endregion
//***************************

		ComponentMap m_ComponentMap;
		std::vector<IComponent*> m_ComponentLookUp;
		std::vector<std::vector<ComponentID>> m_EntityComponentsMap;
		ECS_EntityMaster* m_pEntityMasterRef;

	private:
		template <class Type>
		ComponentContainer<Type>* GetComponentContainer();

		ComponentID GenerateComponentID(IComponent* pComponent);
		void ReleaseComponentID(ComponentID ID);

		void MapComponentToEntity(const EntityID eID, const ComponentID cID, const ComponentTypeID cTypeID);
		void UnmapComponentFromEntity(const EntityID eID, const ComponentID cID, const ComponentTypeID cTypeID);



	public:
		template <class CompType>
		using ComponentIterator = typename ComponentContainer<CompType>::ChunkIterator;

		// Iterators that point towards the collection of all components of Type T
		template <class CompType>
		ComponentIterator<CompType> Begin();
		template <class CompType>
		ComponentIterator<CompType> End();

	public: // ROF:
		ECS_ComponentMaster(const ECS_ComponentMaster&) = delete;
		ECS_ComponentMaster(ECS_ComponentMaster&&) = delete;
		ECS_ComponentMaster& operator=(const ECS_ComponentMaster&) = delete;
		ECS_ComponentMaster& operator=(ECS_ComponentMaster&&) = delete;
	};
}

#include "LiberoECS_ComponentMaster.inl"

