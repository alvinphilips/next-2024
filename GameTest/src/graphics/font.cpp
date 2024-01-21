#include "stdafx.h"
#include "font.h"

namespace gfx
{
    // This is a silly table that could possibly break on a different version of GLUT, or if we're not using the right compiler
    // Since we're *definitely* going to use MSVC, this should be fine. I hope.
    const FontInfo FontUtils::table[FONT_COUNT] = {
        FontInfo {math::Vec2(), "Unknown", FontType::Other}, // Unknown Font
        FontInfo {math::Vec2(9, 15), "Debug Mono big", FontType::Monospaced}, // GLUT_BITMAP_9_BY_15
        FontInfo {math::Vec2(8, 13), "Debug Mono smol", FontType::Monospaced}, // GLUT_BITMAP_8_BY_13
        FontInfo {math::Vec2(5, 10), "Times New Roman", FontType::Serif}, // GLUT_BITMAP_TIMES_ROMAN_10
        FontInfo {math::Vec2(11, 24), "Times New Roman", FontType::Serif}, // GLUT_BITMAP_TIMES_ROMAN_24
        FontInfo {math::Vec2(5.5f, 10), "Helvetica", FontType::SansSerif}, // GLUT_BITMAP_HELVETICA_10
        FontInfo {math::Vec2(6.5f, 12), "Helvetica", FontType::SansSerif}, // GLUT_BITMAP_HELVETICA_12
        FontInfo {math::Vec2(9.2f, 18), "Helvetica", FontType::SansSerif}, // GLUT_BITMAP_HELVETICA_18
    };

    const FontInfo& FontUtils::GetInfo(const Font font)
    {
        // font could be 0 here, mean user :(
        size_t index = (size_t)font - 1;

        if (index >= FONT_COUNT)
        {
            index = 0;
        }

        return table[index];
    }

    math::IVec2 FontUtils::GetTextDimensions(const Font font, const std::string& text)
    {
        auto dimensions = GetInfo(font).char_size;
        dimensions.x *= text.size();

        return math::IVec2(dimensions);
    }
}