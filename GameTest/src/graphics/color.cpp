#include "stdafx.h"
#include "color.h"

#define BYTE_TO_FLOAT(byte) float(byte) / 255.0f
namespace gfx
{
    Color::Color()
    {
        *this = WHITE;
    }

    Color::Color(const uint32_t rgb, const uint8_t a)
    {
        // rgb field layout
        // | 00 - 07 | 08 - 15 | 16 - 23 | 24 - 31 | bits
        // |  blue   |  green  |   red   | unused  | component
        this->r = BYTE_TO_FLOAT(rgb >> 16 & 0xff);
        this->g = BYTE_TO_FLOAT(rgb >> 8 & 0xff);
        this->b = BYTE_TO_FLOAT(rgb & 0xff);
        this->a = BYTE_TO_FLOAT(a);
    }

    Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    {
        this->r = BYTE_TO_FLOAT(r);
        this->g = BYTE_TO_FLOAT(g);
        this->b = BYTE_TO_FLOAT(b);
        this->a = BYTE_TO_FLOAT(a);
    }

    const Color Color::WHITE = Color(255, 255, 255);
    const Color Color::BLACK = Color(0, 0, 0);
    const Color Color::RED = Color(255, 0, 0);
    const Color Color::GREEN = Color(0, 255, 0);
    const Color Color::BLUE = Color(0, 0, 255);
    const Color Color::MAGENTA = Color(255, 0, 255);
}