#include "LiberoECS_ComponentMaster.h"
#include "FamilyTypeID.h"
#include "LiberoECS_EntityMaster.h"

namespace Libero
{
	inline ECS_ComponentMaster::ECS_ComponentMaster()
		: m_pEntityMasterRef{nullptr}
	{
		const size_t nrComponents = FamilyTypeID<IComponent>::Get();
		m_EntityComponentsMap.resize(ENTITY_LUT_GROW);

		// Fill the componentmap with invalid IDs
		for (auto i = 0; i < ENTITY_LUT_GROW; ++i)
			m_EntityComponentsMap[i].resize(nrComponents, g_ComponentID_Invald);
	}

	inline ECS_ComponentMaster::~ECS_ComponentMaster()
	{
		// Delete all component containers:
		for (auto container : m_ComponentMap)
		{
			delete container.second;
			container.second = nullptr;
		}
	}

	template<class Type, class ...Args>
	inline Type* ECS_ComponentMaster::AddComponent(const EntityID eID, Args&& ...args)
	{
		const ComponentTypeID cTypeID = Type::m_Stat_Component_TypeID;

		// Get memory for object:
		void* pObjMem = GetComponentContainer<Type>()->CreateObject();

		ComponentID componentID = GenerateComponentID((Type*)pObjMem);
		((Type*)pObjMem)->m_ID = componentID;

		// Create the object to the memory & forward the construction arguments:
		IComponent* pComponent = new (pObjMem)Type(std::forward<Args>(args)...);

		pComponent->m_Owner = eID;
		pComponent->m_pEntityMasterRef = m_pEntityMasterRef;

		// Map the componentID to the EntityOwner ID
		MapComponentToEntity(eID, componentID, cTypeID);

		return (Type*)pComponent;
	}

	template<class Type>
	inline Type* ECS_ComponentMaster::GetComponent(const EntityID eID)
	{
		const ComponentTypeID cTypeID = Type::m_Stat_Component_TypeID;

		const ComponentID cID = m_EntityComponentsMap[eID.m_Idx][cTypeID];

		// Entity doesn't have such component
		if (cID == g_ComponentID_Invald) return nullptr;

		return (Type*)m_ComponentLookUp[cID];
	}

	template<class Type>
	inline std::vector<Type*> ECS_ComponentMaster::GetComponents()
	{
		const ComponentTypeID cTypeID = Type::m_Stat_Component_TypeID;

		std::vector<Type*> res;
		res.reserve(1024);

		for (auto it = Begin<Type>(); it != End<Type>(); ++it)
		{
			res.push_back(*it);
		}

		return res;
	}

	

	template<class Type>
	inline ComponentContainer<Type>* ECS_ComponentMaster::GetComponentContainer()
	{
		ComponentTypeID typeID = Type::m_Stat_Component_TypeID;

		auto it = m_ComponentMap.find(typeID);
		ComponentContainer<Type>* container = nullptr;

		// if there is no Container of this type yet, create one
		if (it == m_ComponentMap.end())
		{
			container = new ComponentContainer<Type>();
			m_ComponentMap[typeID] = container;
		}
		else container = (ComponentContainer<Type>*)it->second;

		return container;
	}

	template<class CompType>
	inline ECS_ComponentMaster::ComponentIterator<CompType> ECS_ComponentMaster::Begin()
	{
		return GetComponentContainer<CompType>()->Begin();
	}

	template<class CompType>
	inline ECS_ComponentMaster::ComponentIterator<CompType> ECS_ComponentMaster::End()
	{
		return GetComponentContainer<CompType>()->End();
	}

	inline std::vector<IComponent*> ECS_ComponentMaster::GetComponents(const EntityID eID)
	{
		static const size_t nrComponents = m_EntityComponentsMap[0].size();
		std::vector<IComponent*> res;
		res.reserve(nrComponents);

		for (ComponentTypeID cTypeID{}; cTypeID < nrComponents; ++cTypeID)
		{
			const ComponentID cID = m_EntityComponentsMap[eID.m_Idx][cTypeID];
			if (cID == g_ComponentID_Invald) continue;

			IComponent* pComponent = m_ComponentLookUp[cID];
			if (pComponent) res.push_back(pComponent);
		}

		return res;
	}

	template<class Type>
	inline void ECS_ComponentMaster::RemoveComponent(const EntityID eID)
	{
		const ComponentTypeID cTypeID = Type::m_Stat_Component_TypeID;

		// Get the ID of the component that belongs to eID
		const ComponentID componentID = m_EntityComponentsMap[eID.m_Idx][cTypeID];

		IComponent* pComponent = m_ComponentLookUp[componentID];

		assert(pComponent); // TODO: This is bad if fails: the component is not being used by this entity

		// Release the component memory:
		//GetComponentContainer<Type>()->DestroyObject(pComponent);
		GetComponentContainer<Type>()->DestroyComponent(pComponent);

		// Unmap the componentID from the EntityOwner ID:
		UnmapComponentFromEntity(eID, componentID, cTypeID);
	}

	inline void ECS_ComponentMaster::RemoveAllComponents(const EntityID eID)
	{
		static const size_t nrComponents = m_EntityComponentsMap[0].size();

		for (ComponentTypeID cTypeID{}; cTypeID < nrComponents; ++cTypeID)
		{
			const ComponentID cID = m_EntityComponentsMap[eID.m_Idx][cTypeID];
			if (cID == g_ComponentID_Invald) continue;

			IComponent* pComponent = m_ComponentLookUp[cID];
			if (pComponent)
			{
				// Get the component container:
				auto it = m_ComponentMap.find(cTypeID);
				if (it != m_ComponentMap.end()) it->second->DestroyComponent(pComponent);
				else assert(false); // TODO: This is bad!: Trying to release a component that wasn't created by componentManager

				UnmapComponentFromEntity(eID, cID, cTypeID);
			}
		}
	}

	inline void ECS_ComponentMaster::Initialize(ECS_EntityMaster* pEntityMasterRef)
	{
		m_pEntityMasterRef = pEntityMasterRef;
	}

#pragma region IDHandling
	inline ComponentID ECS_ComponentMaster::GenerateComponentID(IComponent* pComponent)
	{
		size_t i{};

		// Find the first element in the lookup table that's nullptr, and put the component in there
		for (; i < m_ComponentLookUp.size(); ++i)
		{
			if (m_ComponentLookUp[i] == nullptr)
			{
				m_ComponentLookUp[i] = pComponent;
				return ComponentID(i);
			}
		}

		// Increase Component Lookup size and fill it with nullptr's
		m_ComponentLookUp.resize(m_ComponentLookUp.size() + COMPONENT_LUT_GROW, nullptr);
		m_ComponentLookUp[i] = pComponent;

		return ComponentID(i);
	}

	inline void ECS_ComponentMaster::ReleaseComponentID(ComponentID ID)
	{
		assert((ID != g_ComponentID_Invald && ID < m_ComponentLookUp.size())); // TODO: catch this invalid componentID
		m_ComponentLookUp[ID] = nullptr;
	}

	inline void ECS_ComponentMaster::MapComponentToEntity(const EntityID eID, const ComponentID cID, const ComponentTypeID cTypeID)
	{
		static const size_t nrComponents = FamilyTypeID<IComponent>::Get();

		if (eID.m_Idx >= m_EntityComponentsMap.size())
		{
			// If entity with this ID isn't in the Entity-componentsmap yet:
			// Grow the Entity-Componentsmap
			size_t oldSize = m_EntityComponentsMap.size();
			size_t newSize = oldSize + ENTITY_LUT_GROW;

			m_EntityComponentsMap.resize(newSize);

			// And fill the new Entity ID's with invalidcomponentID's
			for (auto i{ oldSize }; i < newSize; ++i)
			{
				m_EntityComponentsMap[i].resize(nrComponents, g_ComponentID_Invald);
			}
		}

		// Map this componentID to the component of this type to this Entity with the eID
		m_EntityComponentsMap[eID.m_Idx][cTypeID] = cID;
	}

	inline void ECS_ComponentMaster::UnmapComponentFromEntity(const EntityID eID, const ComponentID cID, const ComponentTypeID cTypeID)
	{
		assert(m_EntityComponentsMap[eID.m_Idx][cTypeID] == cID); // TODO: Catch if this goes wrong, (map corruption)

		// Map an invalid componentID to the component of this type to this Entity with the eID
		m_EntityComponentsMap[eID.m_Idx][cTypeID] = g_ComponentID_Invald;

		// Free the component ID:
		ReleaseComponentID(cID);
	}
#pragma endregion
}




