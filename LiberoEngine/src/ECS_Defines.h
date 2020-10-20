#pragma once
#include "Handle.h"
#include <limits>

// General TypeID
typedef unsigned int TypeID;
static const TypeID g_TypeID_Invalid = std::numeric_limits<TypeID>::max();

// EntityID
#if _WIN32 || _WIN64
#if _WIN64
typedef Handle64 EntityID;
static const EntityID g_EntityID_Invalid = Handle64::INVALID;
#else
typedef Handle32 EntityID;
static const EntityID g_EntityID_Invalid = Handle32::INVALID;
#endif
#endif

typedef TypeID EntityTypeID;

// ComponentID
typedef TypeID ComponentID;
typedef TypeID ComponentTypeID;
static const ComponentID g_ComponentID_Invald = g_TypeID_Invalid;

// SystemID:
typedef TypeID SysID;
typedef TypeID SysTypeID;

// EventID:
typedef TypeID EventID;
typedef TypeID EventTypeID;

// 8MB
#define ECS_SYSTEM_MEMORY_SIZE 8388608
#define EVENTMASTER_MEMORY_SIZE 8388608

#define ENTITY_T_CHUNK_SIZE 1024
#define COMPONENT_T_CHUNK_SIZE 1024
#define EVENT_T_CHUNK_SIZE 1024

#define ENTITY_LUT_GROW 1024
#define COMPONENT_LUT_GROW 1024