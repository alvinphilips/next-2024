#include "stdafx.h"
#include "collider.h"

#include "../core/entity.h"
#include "../math/utils.h"

namespace physics
{
    using namespace math;

    Collider::Collider(const Collider& other)
    {
        type = other.type;
        switch (type)
        {
        case ColliderType::AABB:
            aabb = other.aabb;
            break;
        case ColliderType::Circle:
            circle = other.circle;
            break;
        }
    }

    Collider::Collider(const Circle& collider)
    {
        type = ColliderType::Circle;
        circle = collider;
    }

    Collider::Collider(const AABB& collider)
    {
        type = ColliderType::AABB;
        aabb = collider;
    }

    bool Collider::HasCollision(const Collider& other) const
    {
        return this->Collide(other).info.is_collision;
    }

    Collision Collider::Collide(const Collider& other) const
    {
        Collision collision;
        collision.first = this;
        collision.other = &other;

        collision.info = CalculateCollision(*this, other);

        return collision;
    }

    CollisionInfo Collider::CalculateCollision(const Collider& first, const Collider& second)
    {
        CollisionInfo info;

        // Circle-to-Circle collision
        if (first.type == ColliderType::Circle && second.type == ColliderType::Circle)
        {
            const float square_distance = (second.entity->position - first.entity->position).MagnitudeSquared();
            const float radii_sum = first.circle.radius + second.circle.radius;
            info.is_collision = square_distance <= radii_sum * radii_sum;
            return info;
        }

        // AABB-to-AABB collision
        if (first.type == ColliderType::AABB && second.type == ColliderType::AABB)
        {
            const auto box1 = Rect(first.entity->position, first.aabb.dimensions);
            const auto box2 = Rect(second.entity->position, second.aabb.dimensions);

            info.is_collision = box1.min.x < box2.max.x && box2.min.x < box1.max.x && box1.min.y < box2.max.y && box2.min.y < box1.max.y;
            return info;
        }

        // Circle-to-AABB collision
        const Collider& circle_collider = second.type == ColliderType::Circle ? second: first;
        Rect box;

        if (first.type == ColliderType::AABB)
        {
            box = Rect::OriginAndDimensions(first.entity->position, first.aabb.dimensions);
        } else
        {
            box = Rect::OriginAndDimensions(second.entity->position, second.aabb.dimensions);
        }

        const Vec2 closest_point = box.ClampPoint(circle_collider.entity->position);
        const float square_distance = (closest_point - circle_collider.entity->position).MagnitudeSquared();

        info.is_collision = square_distance < circle_collider.circle.radius * circle_collider.circle.radius;
        return info;
    }
}
