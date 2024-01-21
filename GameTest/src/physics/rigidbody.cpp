#include "stdafx.h"
#include "rigidbody.h"

#include "../core/entity.h"

#define CHECK_FLAG(FIELD, FLAG) ((FIELD) & (FLAG)) != 0

namespace physics
{
    Rigidbody::Rigidbody(): collider(Collider(AABB { Vec2(1)}))
    {
        mass = 1;
        flags = USE_GRAVITY;
        inverse_mass = 1;
    }

    Rigidbody::Rigidbody(const Collider& collider): collider(collider)
    {
        mass = 1;
        flags = USE_GRAVITY;
        inverse_mass = 1;
    }

    bool Rigidbody::UseGravity() const
    {
        return CHECK_FLAG(flags, USE_GRAVITY);
    }

    bool Rigidbody::IsKinematic() const
    {
        return CHECK_FLAG(flags, IS_KINEMATIC);
    }

    Rigidbody& Rigidbody::SetMass(const float mass)
    {
        this->mass = mass;
        this->inverse_mass = 1.0f / mass;

        return *this;
    }

    Rigidbody& Rigidbody::SetCollider(const Collider& collider)
    {
        this->collider = collider;

        return *this;
    }

    Rigidbody& Rigidbody::SetGravity(const bool use_gravity)
    {
        flags &= ~USE_GRAVITY;

        if (use_gravity)
        {
            flags |= USE_GRAVITY;
        }

        return *this;
    }

    Rigidbody& Rigidbody::SetKinematic(const bool is_kinematic)
    {
        flags &= ~IS_KINEMATIC;

        if (is_kinematic)
        {
            flags |= IS_KINEMATIC;
        }

        return *this;
    }
}
