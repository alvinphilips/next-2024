#pragma once

#ifndef ENGINE_CORE_WORLD_H
#define ENGINE_CORE_WORLD_H

#include "entity.h"
#include "system.h"
#include "resource.h"

class World
{
    EntityContainer entities;
    std::vector<System> systems;
    std::vector<System> render_systems;

    unsigned long long update_tick_count = 0;
    unsigned long long render_tick_count = 0;
    _resources resources;

public:
    Entity* SpawnEntity();
    World& AddSystem(const System& system);
    World& AddSystem(const SystemFunction& func);
    World& AddSystems(const std::vector<SystemFunction>& funcs);
    World& AddRenderSystem(const System& system);
    World& AddRenderSystem(const SystemFunction& func);
    World& AddRenderSystems(const std::vector<SystemFunction>& funcs);

    template <typename T>
    const T& GetResource()
    {
        return std::get<T>(resources);
    }

    template <typename T>
    T& GetResourceMut()
    {
        return std::get<T>(resources);
    }

    void RunUpdateSystems();
    void RunRenderSystems();
};

#endif