#pragma once

#ifndef ENGINE_CORE_SYSTEM_H
#define ENGINE_CORE_SYSTEM_H

#include <functional>

#define NUSE_LIST_ENTITIES

#ifdef USE_LIST_ENTITIES
#include <list>
#else
#include <vector>
#endif

struct Entity;


#ifdef USE_LIST_ENTITIES
typedef std::list<Entity> EntityContainer;
#else
typedef std::vector<Entity> EntityContainer;
#endif


#include "resource.h"


enum class SystemSchedule
{
    RunOnce,
    EachFrame,
};

typedef EntityContainer& EntityListMut;
typedef const EntityContainer& EntityList;
typedef std::function<void(EntityListMut entities, ResourcesMut resources)> SystemFunction;

struct System
{
    SystemFunction func;
    SystemSchedule schedule;
    bool is_enabled;

    // Create a System.
    explicit System(const SystemFunction& system);
    // Create a System with a specified SystemSchedule.
    explicit System(const SystemFunction& system, SystemSchedule schedule);

    // Enable a System, and return whether the System was already enabled.
    bool Restart();
};

#endif