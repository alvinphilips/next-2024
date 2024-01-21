#include "stdafx.h"
#include "manager.h"

#include "rigidbody.h"

namespace physics
{
    Rigidbody* PhysicsManager::CreateRigidbody()
    {
        rigidbodies.emplace_back(Rigidbody());

        return &rigidbodies.back();
    }

    Rigidbody* PhysicsManager::CreateRigidbody(const Collider& collider)
    {
        rigidbodies.emplace_back(Rigidbody(collider));

        return &rigidbodies.back();
    }

}
