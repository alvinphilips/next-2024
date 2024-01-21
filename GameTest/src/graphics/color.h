#pragma once

#ifndef ENGINE_GRAPHICS_COLOR_H
#define ENGINE_GRAPHICS_COLOR_H

#include <cstdint>

namespace gfx {
    struct Color
    {
        float r;
        float g;
        float b;
        float a; // unused

        explicit Color();
        explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        // Use a 32-bit integer to assign the RGB value, with an optional 8-bit alpha value.
        explicit Color(uint32_t rgb, uint8_t a = 255);

        static const Color WHITE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color MAGENTA;
    };
}

#endif