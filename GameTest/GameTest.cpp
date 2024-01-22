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
#include "src/resources/menu.h"
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

void debug_info_entities(EntityListMut entities, ResourcesMut resources)
{
	if (!std::get<ui::Menu>(resources).show_debug_info)
	{
		return;
	}

	int offset_y = 0;

	for (auto& entity : entities)
	{
		Debug::font = GLUT_BITMAP_9_BY_15;
		Debug::DrawInfo(entity.position, IVec2(40, 400 + offset_y), Color::MAGENTA);
		offset_y += 20;
	}
}

void update_player(EntityListMut entities, ResourcesMut resources)
{
	if (entities.empty())
	{
		return;
	}

	Entity& player = entities.front();

	const auto controller = App::GetController();

	if (controller.GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
	}
	if (controller.GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
	}
	if (controller.GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
	}
	if (controller.GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
	}

	auto movement = Vec2(controller.GetLeftThumbStickX(), controller.GetLeftThumbStickY());
	movement.Normalize();

	player.position += movement * std::get<Time>(resources).DeltaTime() * 100;


	if (controller.CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		auto& physics_manager = std::get<PhysicsManager>(resources);
		const Collider collider(Circle{ 10 });
		const auto rb = physics_manager.CreateRigidbody(collider);

		auto shoot_dir = Vec2(controller.GetRightThumbStickX(), controller.GetRightThumbStickY());
		shoot_dir.Normalize();

		if (shoot_dir == Vec2::Zero)
		{
			shoot_dir = Vec2::UnitX;
		}

		rb->velocity = shoot_dir * 160;

		entities.emplace_back();
		entities.back().SetRigidbody(rb).SetTag(Entity::Tag::PROJECTILE).SetPosition(player.position);
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

void draw_sprites(EntityList entities, Resources resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}

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
	if (!std::get<ui::Menu>(resources).show_debug_colliders)
	{
		return;
	}

	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}

	for (auto& entity : entities)
	{
		if (entity.collider && entity.collider->type == ColliderType::AABB) {
			const auto& dimensions = IVec2(entity.collider->aabb.dimensions);
			Debug::DrawRect(IVec2(entity.position) - dimensions / 2, dimensions, Color::GREEN);
		}
		else
		{
			const float radius = entity.collider->circle.radius;
			Debug::DrawCircle(IVec2(entity.position), radius, Color::MAGENTA, 6);
		}
	}
}

void update_rigidbodies(EntityListMut entities, ResourcesMut resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}

	const float dt = std::get<Time>(resources).DeltaTime();
	auto& rigidbodies = std::get<PhysicsManager>(resources).rigidbodies;
	for (auto& rb : rigidbodies)
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

void spawn_enemy(EntityListMut entities, ResourcesMut resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}
	const Collider collider(Circle{ 50 });
	const auto rb = std::get<PhysicsManager>(resources).CreateRigidbody(collider);
	rb->SetGravity(false).SetMass(100);
	entities.emplace_back();
	auto& enemy = entities.back();
	enemy.SetRigidbody(rb).SetTag(Entity::Tag::ENEMY).SetPosition(Vec2(FRAND_RANGE(-100, APP_VIRTUAL_WIDTH + 100), FRAND_RANGE(-100, APP_VIRTUAL_HEIGHT + 100)));
}

void create_menu(EntityList entities, ResourcesMut resources)
{
	auto& menu = std::get<ui::Menu>(resources);

	menu.options.push_back(ui::MenuOption{ "RESUME" });
	menu.options.push_back(ui::MenuOption{ "MUSIC: ", true, menu.play_music });
	menu.options.push_back(ui::MenuOption{ "LARGE TEXT: ", true, false });
	menu.options.push_back(ui::MenuOption{ "DEBUG INFO: ", true, menu.show_debug_info });
	menu.options.push_back(ui::MenuOption{ "DRAW COLLIDERS: ", true, menu.show_debug_colliders });
	menu.options.push_back(ui::MenuOption{ "SHOW CONTROLS: ", true, menu.show_controls });

	menu.recalculate_offsets();
}

void update_menu(EntityList entities, ResourcesMut resources)
{
	const auto& controller = App::GetController();
	auto& menu = std::get<ui::Menu>(resources);

	if (!menu.is_visible)
	{
		return;
	}

	if (controller.CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
	{
		menu.selection++;
	}

	if (controller.CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
	{
		menu.selection--;
	}

	menu.selection = (menu.options.size() + menu.selection) % menu.options.size();

	if (controller.CheckButton(XINPUT_GAMEPAD_A))
	{
		switch (menu.selection)
		{
		case 0:
			menu.ToggleVisibility();
			std::get<Time>(resources).time_scale = menu.is_visible ? 0 : 1;
			break;
		case 1:
			menu.options[1].is_enabled = !menu.options[1].is_enabled;
			menu.recalculate_offsets();
			menu.play_music = menu.options[1].is_enabled;
			break;
		case 2:
			menu.options[2].is_enabled = !menu.options[2].is_enabled;
			menu.font = menu.options[2].is_enabled ? GLUT_BITMAP_9_BY_15 : GLUT_BITMAP_8_BY_13;
			menu.recalculate_offsets();
			break;
		case 3:
			menu.options[3].is_enabled = !menu.options[3].is_enabled;
			menu.show_debug_info = menu.options[3].is_enabled;
			menu.recalculate_offsets();
			break;
		case 4:
			menu.options[4].is_enabled = !menu.options[4].is_enabled;
			menu.show_debug_colliders = menu.options[4].is_enabled;
			menu.recalculate_offsets();
			break;
		case 5:
			menu.options[5].is_enabled = !menu.options[5].is_enabled;
			menu.show_controls = menu.options[5].is_enabled;
			menu.recalculate_offsets();
			break;
		default:
			break;
		}
	}
}

void update_enemies(EntityListMut entities, Resources resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}
	const auto& player = entities.front();

	for (auto& entity : entities)
	{
		if (entity.tag != Entity::Tag::ENEMY)
		{
			continue;
		}

		Vec2 dir = player.position - entity.position;
		const float square_magnitude = dir.MagnitudeSquared();

		dir.Normalize();

		if (square_magnitude < 1000 * 1000)
		{
			entity.rigidbody->velocity = dir * 90.0f;
			entity.rigidbody->force = -dir;
		}

		if (square_magnitude < 50000)
		{
			entity.rigidbody->velocity = Vec2::Zero;
		}
	}
}

void toggle_menu(EntityList entities, ResourcesMut resources)
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		auto& menu = std::get<ui::Menu>(resources);
		menu.ToggleVisibility();
		std::get<Time>(resources).time_scale = menu.is_visible ? 0 : 1;
	}
}

void draw_menu(EntityList entities, Resources resources)
{
	const auto& menu = std::get<ui::Menu>(resources);

	if (menu.is_visible)
	{
		auto center_menu = Debug::ScreenDimensions / 2;
		center_menu.y += menu.option_positions.back().y / 2;
		for (size_t i = 0; i < menu.options.size(); i++)
		{
			auto offset = center_menu - menu.option_positions[i];
			auto text = menu.options[i].text;

			if (menu.options[i].is_toggle)
			{
				text += menu.options[i].is_enabled ? "ON" : "OFF";
			}

			App::Print(offset.x, offset.y, text.c_str(), 1, 1, 1, menu.font);

			if (menu.selection == i)
			{
				auto text_dimensions = FontUtils::GetTextDimensions(menu.font, text);
				Debug::DrawPaddedRect(offset, text_dimensions, IVec2(5));
			}
		}
	}
}

// Spawn test rigidbodies :)
void test_spawn_rbs(EntityListMut entities, ResourcesMut resources)
{
	const auto collider = Collider(AABB{ Vec2(20) });
	auto& physics_manager = std::get<PhysicsManager>(resources);

	for (int i = 0; i < 5; i++)
	{
		const auto rb = physics_manager.CreateRigidbody(collider);
		rb->SetGravity(i % 2 == 0);
		rb->velocity.x = 8.0f;
		rb->velocity.y = 80.0f;
		rb->mass = i * 20 + 1;
		entities.emplace_back();
		entities.back().SetRigidbody(rb);
	}
}

// Kill any Entity that goes out of bounds.
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
			// App::PlaySound(".\\TestData\\Test.wav");
		}
		else
		{
			i++;
		}
	}

	entities.resize(entity_count);
#endif
}

void draw_projectiles(EntityList entities, Resources resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}

	for (auto& entity : entities)
	{
		if (entity.tag == Entity::Tag::PROJECTILE && entity.collider && entity.collider->type == ColliderType::Circle)
		{

			Debug::DrawCircle(IVec2(entity.position), entity.collider->circle.radius, Color::BLUE, 4);
		}
	}
}

void draw_enemies(EntityList entities, Resources resources)
{
	if (std::get<ui::Menu>(resources).is_visible)
	{
		return;
	}

	for (auto& entity : entities)
	{
		if (entity.tag == Entity::Tag::ENEMY && entity.collider && entity.collider->type == ColliderType::Circle)
		{

			Debug::DrawCircle(IVec2(entity.position), entity.collider->circle.radius, Color::WHITE, 12);
		}
	}
}

void kill_unused_rigidbodies(EntityList entities, ResourcesMut resources)
{
	auto& rigidbodies = std::get<PhysicsManager>(resources).rigidbodies;

	rigidbodies.remove_if([](const Rigidbody& rb) {return rb.entity == nullptr;});
}

void show_controls(EntityList entities, Resources resources)
{
	if (!std::get<ui::Menu>(resources).show_controls)
	{
		return;
	}

	static std::string controls = "RB: Shoot, A: Select, Start: Menu, Right stick: Aim, Left stick: Move";

	App::Print(20, APP_VIRTUAL_HEIGHT - 35, controls.c_str(), 1, 1, 1, GLUT_BITMAP_9_BY_15);
	Debug::DrawPaddedRect(IVec2(20, APP_VIRTUAL_HEIGHT - 35), FontUtils::GetTextDimensions(GLUT_BITMAP_9_BY_15, controls), IVec2(5));
}

//------------------------------------------------------------------------
// Called before first update.
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
		.AddSystem(System(create_menu, SystemSchedule::RunOnce))
		.AddSystem(System(spawn_enemy, SystemSchedule::ConstantTick).SetTicksBetween(100))
		.AddRenderSystem(debug_info_entities)
		.AddSystem(update_player)
		.AddSystem(update_rigidbodies)
		.AddSystem(update_sprites)
		.AddSystem(update_menu)
		.AddSystem(update_enemies)
		.AddSystem(toggle_menu)
		.AddRenderSystem(show_controls)
		.AddRenderSystem(draw_sprites)
		.AddRenderSystem(draw_colliders)
		.AddRenderSystem(draw_enemies)
		.AddRenderSystem(draw_projectiles)
		.AddRenderSystem(draw_menu)
		.AddSystem(kill_floor)
		.AddSystem(kill_unused_rigidbodies);


	// Add Player to our world
	const auto collider = Collider(AABB{ Vec2(testSprite->GetWidth(), testSprite->GetHeight()) });
	const auto rb = world.GetResourceMut<PhysicsManager>().CreateRigidbody(collider);
	rb->SetGravity(false);
	world.SpawnEntity()->SetSprite(testSprite).SetRigidbody(rb).SetPosition(Vec2(Debug::ScreenDimensions / 2)).SetTag(Entity::Tag::PLAYER);
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