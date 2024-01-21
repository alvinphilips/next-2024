#pragma once

#ifndef ENGINE_GRAPHICS_FONT_H
#define ENGINE_GRAPHICS_FONT_H

#include "../math/vectors.h"
#include <string>

namespace gfx {
    // How many Fonts we have available, currently hardcoded in.
    constexpr int FONT_COUNT = 8;

    // A Font is an opaque type we do not want the user to care about.
    // This is meant to *only* be used with GLUT's built-in bitmap fonts.
    typedef void* Font;

    // FontType describes the 'type' of font.
    // Possible values are Serif, SansSerif, Monospaced and Other.
    enum class FontType
    {
        Other,
        Serif,
        SansSerif,
        Monospaced,
    };

    // Get info about a Font
    // Returns the dimensions of a single character, the name of the Font, if available and its FontType.
    struct FontInfo
    {
        // Only an approximation for non-monospaced fonts
        math::Vec2 char_size;
        char name[20] = "";
        FontType type = FontType::Other;
    };

    // A set of utilities for working with Fonts.
    struct FontUtils
    {
        // Get info regarding a given Font.
        static const FontInfo& GetInfo(Font font);

        // Get dimensions of a given string of text with a specified Font.
        static math::IVec2 GetTextDimensions(Font font, const std::string& text);

        // Internal table used to store FontInfo data for our Fonts.
        const static FontInfo table[FONT_COUNT];
    };
}

#endif