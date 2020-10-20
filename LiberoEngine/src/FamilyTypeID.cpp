#pragma once
#include "PCH.h"
#include "FamilyTypeID.h"
#include "ECS_Includes.h"
#include "IEvent.h"

class Libero::IEntity;
class Libero::IComponent;
class Libero::ISystem;
class Libero::IEvent;

unsigned int FamilyTypeID<Libero::IEntity>::m_Stat_Count = 1;
template class FamilyTypeID<Libero::IEntity>;

unsigned int FamilyTypeID<Libero::IComponent>::m_Stat_Count = 1;
template class FamilyTypeID<Libero::IComponent>;

unsigned int FamilyTypeID<Libero::ISystem>::m_Stat_Count = 1;
template class FamilyTypeID<Libero::ISystem>;

unsigned int FamilyTypeID<Libero::IEvent>::m_Stat_Count = 1;
template class FamilyTypeID<Libero::IEvent>;