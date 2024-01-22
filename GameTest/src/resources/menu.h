#pragma once

#ifndef ENGINE_RESOURCE_MENU
#define ENGINE_RESOURCE_MENU

#include <vector>

#include "../graphics/font.h"

namespace ui
{
	struct MenuOption
	{
		std::string text;
		bool is_toggle = false;
		bool is_enabled = false; // Only used for toggles
	};

	struct Menu
	{
		bool is_visible;
		std::vector<MenuOption> options;
		std::vector<math::IVec2> option_positions;
		int selection;
		int padding;
		gfx::Font font;

		// Hardcoded for now :(
		bool play_music = true;
		bool show_debug_info = true;
		bool show_debug_colliders = false;
		bool show_controls = true;

		explicit Menu();

		void ToggleVisibility();
		void recalculate_offsets();
	};
}

#endif