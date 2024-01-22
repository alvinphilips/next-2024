#include "stdafx.h"
#include "world.h"

Entity* World::SpawnEntity()
{
    entities.push_back(Entity());

    return &entities.back();
}

World& World::AddSystem(const System& system)
{
    systems.push_back(system);

    return *this;
}

World& World::AddSystem(const SystemFunction& func)
{
    systems.push_back(System(func));

    return *this;
}

World& World::AddSystems(const std::vector<SystemFunction>& funcs)
{
    for (auto& func: funcs)
    {
        systems.push_back(System(func));
    }

    return *this;
}

World& World::AddRenderSystem(const System& system)
{
    render_systems.push_back(system);

    return *this;
}

World& World::AddRenderSystem(const SystemFunction& func)
{
    render_systems.push_back(System(func));

    return *this;
}

World& World::AddRenderSystems(const std::vector<SystemFunction>& funcs)
{
    for (auto& func: funcs)
    {
        render_systems.push_back(System(func));
    }

    return *this;
}

void World::RunUpdateSystems()
{
    for (auto& system: systems)
    {
        if (!system.is_enabled)
        {
            continue;
        }

        if (system.schedule == SystemSchedule::ConstantTick &&  update_tick_count % system.ticks_between != 0) {
            continue;
        }

        system.func(this->entities, this->resources);

        if (system.schedule == SystemSchedule::RunOnce)
        {
            system.is_enabled = false;
        }
    }
    update_tick_count++;
}

void World::RunRenderSystems()
{
    for (auto& system: render_systems)
    {
        if (!system.is_enabled)
        {
            continue;
        }

        if (system.schedule == SystemSchedule::ConstantTick && render_tick_count % system.ticks_between != 0) {
            continue;
        }

        system.func(this->entities, this->resources);

        if (system.schedule == SystemSchedule::RunOnce)
        {
            system.is_enabled = false;
        }
    }
    render_tick_count++;
}
