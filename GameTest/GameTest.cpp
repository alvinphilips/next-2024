//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "src/core/world.h"
#define USE_TEMPLATED_DRAW_INFO
#include "src/graphics/debug.h"
#include "src/physics/collider.h"
#include "src/physics/rigidbody.h"
//------------------------------------------------------------------------

using namespace math;
using namespace gfx;
using namespace physics;

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite* testSprite;
World world;

enum
{
    ANIM_FORWARDS,
    ANIM_BACKWARDS,
    ANIM_LEFT,
    ANIM_RIGHT,
};
//------------------------------------------------------------------------

void print_hello(EntityListMut entities, ResourcesMut resources)
{
    int offset_y = 0;

    for (auto& entity : entities)
    {
        Debug::font = GLUT_BITMAP_9_BY_15;
        Debug::DrawInfo(entity.position, IVec2(40, 400 + offset_y), Color::MAGENTA);
        offset_y += 20;
    }
}

void move_player(EntityListMut entities, Resources resources)
{
    if (entities.size() == 0)
    {
        return;
    }

    Entity& player = entities.front();

    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_RIGHT);
        player.position.x += 1;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        testSprite->SetAnimation(ANIM_LEFT);
        player.position.x -= 1;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_FORWARDS);
        player.position.y += 1;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        testSprite->SetAnimation(ANIM_BACKWARDS);
        player.position.y -= 1;
    }

    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
    {
        testSprite->SetScale(testSprite->GetScale() + 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
    {
        testSprite->SetScale(testSprite->GetScale() - 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
    {
        testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
    {
        testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
    {
        testSprite->SetAnimation(-1);
    }
}

void update_sprites(EntityList entities, Resources resources)
{
    const float delta_time = std::get<Time>(resources).DeltaTime() * Time::MS_TO_SECONDS;
    for (const auto& entity : entities)
    {
        if (!entity.sprite)
        {
            continue;
        }
        entity.sprite->Update(delta_time);
        entity.sprite->SetPosition(entity.position.x, entity.position.y);
    }
}

void display_sprites(EntityList entities, Resources resources)
{
    for (auto& entity : entities)
    {
        if (!entity.sprite)
        {
            continue;
        }

        entity.sprite->Draw();
    }
}

void draw_colliders(EntityList entities, Resources resources)
{
    for (auto& entity : entities)
    {
        if (entity.collider && entity.collider->type == ColliderType::AABB) {
            const auto& dimensions = IVec2(entity.collider->aabb.dimensions);
            Debug::DrawRect(IVec2(entity.position) - dimensions / 2, dimensions, Color::GREEN);
        }
    }
}

void update_rigidbodies(EntityListMut entities, ResourcesMut resources)
{
    const float dt = std::get<Time>(resources).DeltaTime();
    auto& rigidbodies = std::get<PhysicsManager>(resources).rigidbodies;
    for (auto& rb: rigidbodies)
    {

        if (rb.IsKinematic())
        {
            continue;
        }

        if (rb.UseGravity()) {

            rb.velocity.y -= 9.8f * rb.inverse_mass * dt;
        }

        rb.velocity += rb.force * rb.inverse_mass * dt;

        if (rb.entity)
        {
            rb.entity->position += rb.velocity * dt;
        }
    }
}

// Spawn 10 rigidbodies :)
void test_spawn_rbs(EntityListMut entities, ResourcesMut resources)
{
    const auto collider = Collider(AABB{ Vec2(20) });
    auto& physics_manager = std::get<PhysicsManager>(resources);

    for (int i = 0; i < 10000; i++)
    {
        const auto rb = physics_manager.CreateRigidbody(collider);
        rb->SetGravity(i % 2 == 0);
        rb->velocity.x = i * 8.0f;
        rb->velocity.y = i * 8.0f;
        rb->mass = i * 2 + 1;
        entities.emplace_back();
        entities.back().SetRigidbody(rb);
    }
}

// Kill any Entity that falls past a certain 'altitude'.
void kill_floor(EntityListMut entities, Resources resources)
{
    auto should_kill = [](Entity& entity) {return OUT_OF_BOUNDS(entity.position);};
#ifdef USE_LIST_ENTITIES
    entities.remove_if(should_kill);
#else
    size_t entity_count = entities.size();
    for (size_t i = 0; i < entity_count;)
    {
        if (should_kill(entities[i]))
        {
            entities[i] = entities[--entity_count];
            App::PlaySound(".\\TestData\\Test.wav");
        } else
        {
            i++;
        }
    }

    entities.resize(entity_count);
#endif
}

void kill_unused_rigidbodies(EntityList entities, ResourcesMut resources)
{
    auto& rigidbodies = std::get<PhysicsManager>(resources).rigidbodies;

    rigidbodies.remove_if([](Rigidbody& rb){return rb.entity == nullptr;});
}

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
    testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
    testSprite->SetPosition(400.0f, 400.0f);
    float speed = 1.0f / 15.0f;
    testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
    testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
    testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
    testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
    testSprite->SetScale(1.0f);

    world.AddSystem(System(test_spawn_rbs, SystemSchedule::RunOnce))
        .AddRenderSystem(print_hello)
        .AddSystem(move_player)
        .AddSystem(update_rigidbodies)
        .AddSystem(update_sprites)
        .AddRenderSystem(display_sprites)
        .AddRenderSystem(draw_colliders)
        .AddSystem(kill_floor)
        .AddSystem(kill_unused_rigidbodies);


    // Add Player to our world
    const auto collider = Collider(AABB{ Vec2(testSprite->GetWidth(), testSprite->GetHeight()) });
    const auto rb = world.GetResourceMut<PhysicsManager>().CreateRigidbody(collider);
    rb->SetGravity(false);
    world.SpawnEntity()->SetSprite(testSprite).SetRigidbody(rb);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
    world.GetResourceMut<Time>().Tick();
    world.RunUpdateSystems();

    //------------------------------------------------------------------------
    // Sample Sound.
    //------------------------------------------------------------------------

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
    world.RunRenderSystems();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
    delete testSprite;
}