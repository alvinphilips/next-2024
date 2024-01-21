#pragma once

#ifndef ENGINE_CORE_ENTITY_H
#define ENGINE_CORE_ENTITY_H

#include "../App/SimpleSprite.h"
#include "../math/vectors.h"

namespace physics
{
    struct Rigidbody;
    struct Collider;
}

struct Entity
{
    unsigned long long id;
    math::Vec2 position;
    physics::Rigidbody* rigidbody = nullptr;
    physics::Collider* collider = nullptr;
    CSimpleSprite* sprite = nullptr;

    explicit Entity();
    
    Entity(const Entity& other) noexcept;
    Entity(Entity&& other) noexcept;
    Entity& operator=(const Entity&) noexcept;

    Entity& SetPosition(const math::Vec2& pos);
    Entity& SetRigidbody(physics::Rigidbody* rigidbody);
    Entity& SetCollider(physics::Collider* collider);
    Entity& SetSprite(CSimpleSprite* sprite);
private:
    static unsigned long long current_id;
};

#endif