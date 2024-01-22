#include "stdafx.h"
#include "menu.h"

#include <include/GL/freeglut_std.h>

namespace ui
{
	Menu::Menu()
	{
		selection = 0;
		is_visible = false;
		padding = 10;
		font = GLUT_BITMAP_8_BY_13;
	}

	void Menu::ToggleVisibility()
	{
		is_visible = !is_visible;
	}

	void Menu::recalculate_offsets()
	{
		math::IVec2 current_offset;
		option_positions.resize(options.size());
		for (size_t i = 0; i < options.size(); i++)
		{
			auto text = options[i].text;

			// Add "on" or "off" if we're a toggle :)
			if (options[i].is_toggle)
			{
				text += options[i].is_enabled ? "ON" : "OFF";
			}

			const auto text_dimensions = gfx::FontUtils::GetTextDimensions(font, text);
			option_positions[i] = text_dimensions / 2 - current_offset;
			current_offset.y -= text_dimensions.y + padding;
		}
	}
}
