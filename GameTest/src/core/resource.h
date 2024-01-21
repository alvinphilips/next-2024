#pragma once

#ifndef ENGINE_CORE_RESOURCE_H
#define ENGINE_CORE_RESOURCE_H

#include <chrono>
#include <tuple>

#include "../resources/gametime.h"
#include "../physics/manager.h"

// I would very much like to have this be more flexible, allowing for any type to be as Resource (as long as only one of each type exists).
typedef std::tuple<Time, physics::PhysicsManager> _resources;
typedef const _resources& Resources;
typedef _resources& ResourcesMut;

#endif