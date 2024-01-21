#pragma once

#ifndef ENGINE_COLLIDER_H
#define ENGINE_COLLIDER_H

#include "../math/vectors.h"

struct Entity;

namespace physics {
    // Enum of Collider types.
    enum class ColliderType
    {
        Circle,
        AABB,
    };

    // A Circle Collider;
    struct Circle
    {
        float radius;
    };

    // An Axis-Aligned Bounding Box.
    struct AABB
    {
        math::Vec2 dimensions;
    };

    struct Collider;

    // TODO: 
    struct CollisionInfo
    {
        bool is_collision;
    };

    struct Collision
    {
        const Collider* first;
        const Collider* other;
        CollisionInfo info;
    };

    // A Collider is esentially a tagged union with a pointer to an Entity.
    struct Collider
    {
        Entity* entity = nullptr;
        ColliderType type;
        union
        {
            Circle circle;
            AABB aabb;
        };

        Collider(const Collider& other);
        explicit Collider(const Circle& collider);
        explicit Collider(const AABB& collider);

        bool HasCollision(const Collider& other) const;
        math::Vec2 ResolveCollision(const Collider& other);

        Collision Collide(const Collider& other) const;

        static CollisionInfo CalculateCollision(const Collider& first, const Collider& second);
    };
}

#endif