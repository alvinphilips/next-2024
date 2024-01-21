#pragma once

#ifndef ENGINE_PHYSICS_RIGIDBODY_H
#define ENGINE_PHYSICS_RIGIDBODY_H

#include "collider.h"
#include "../core/entity.h"

namespace physics
{
    using namespace math;

    struct Rigidbody
    {
        Entity* entity = nullptr;
        Vec2 velocity;
        Vec2 force;
        Collider collider;
        float mass;
        float inverse_mass;
        unsigned int flags;

        explicit Rigidbody();
        explicit Rigidbody(const Collider& collider);

        bool UseGravity() const;
        bool IsKinematic() const;

        Rigidbody& SetMass(float mass);
        Rigidbody& SetCollider(const Collider& collider);
        Rigidbody& SetGravity(bool use_gravity);
        Rigidbody& SetKinematic(bool is_kinematic);

        enum
        {
            USE_GRAVITY = 1,
            IS_KINEMATIC = 2,
        };
    };
}

#endif