#pragma once

#ifndef ENGINE_PHYSICS_MANAGER_H
#define ENGINE_PHYSICS_MANAGER_H

#include <list>

#include "../math/vectors.h"
#include "rigidbody.h"

namespace physics
{
    struct PhysicsManager
    {
        std::list<Rigidbody> rigidbodies;
        Vec2 gravity;

        Rigidbody* CreateRigidbody();
        Rigidbody* CreateRigidbody(const Collider& collider);
    };
}

#endif