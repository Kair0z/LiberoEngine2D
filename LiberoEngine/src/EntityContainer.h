#pragma once
#include "ECS_Defines.h"
#include "LibMemoryChunkAllocator.h"

namespace Libero
{
	class IEntity;
	class IEntityContainer
	{
	public:
		virtual ~IEntityContainer() = default;
		virtual void DestroyEntity(IEntity* pObj) = 0;
	};

	template <class Type>
	class EntityContainer : 
		public LibMemoryChunkAllocator<Type, ENTITY_T_CHUNK_SIZE>, 
		public IEntityContainer
	{
	public:
		EntityContainer() = default;
		virtual ~EntityContainer() = default;

		virtual void DestroyEntity(IEntity* pObj) override;

	public:
		EntityContainer(const EntityContainer&) = delete;
		EntityContainer(EntityContainer&&) = delete;
		EntityContainer& operator=(const EntityContainer&) = delete;
		EntityContainer& operator=(EntityContainer&&) = delete;
	};
}

#include "EntityContainer.inl"