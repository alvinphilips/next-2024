#include "stdafx.h"
#include "entity.h"

#include "../physics/rigidbody.h"

Entity::Entity()
{
    id = ++current_id;
}

Entity::Entity(const Entity& other) noexcept
{
    *this = other;
}

Entity::Entity(Entity&& other) noexcept
{
    id = other.id;

    if (rigidbody) {
        rigidbody->entity = nullptr;
    }

    if (collider) {
        collider->entity = nullptr;
    }

    position = other.position;
    sprite = other.sprite;

    rigidbody = other.rigidbody;
    collider = other.collider;

    if (rigidbody)
    {
        rigidbody->entity = this;
    }

    if (collider)
    {
        collider->entity = this;
    }
}

Entity& Entity::operator=(const Entity& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    
    id = other.id;
    position = other.position;
    sprite = other.sprite;

    if (rigidbody) {
        rigidbody->entity = nullptr;
    }

    if (collider) {
        collider->entity = nullptr;
    }

    rigidbody = other.rigidbody;
    collider = other.collider;

    if (rigidbody)
    {
        rigidbody->entity = this;
    }

    if (collider)
    {
        collider->entity = this;
    }

    return *this;
}

Entity& Entity::SetPosition(const math::Vec2& pos)
{
    position = pos;

    return *this;
}

Entity& Entity::SetRigidbody(physics::Rigidbody* rigidbody)
{
    this->rigidbody = rigidbody;
    this->collider = &this->rigidbody->collider;

    this->rigidbody->entity = this;
    collider->entity = this;

    return *this;
}

Entity& Entity::SetCollider(physics::Collider* collider)
{
    this->collider = collider;
    
    this->collider->entity = this;

    return *this;
}

Entity& Entity::SetSprite(CSimpleSprite* sprite)
{
    this->sprite = sprite;

    return *this;
}

unsigned long long Entity::current_id = 0;