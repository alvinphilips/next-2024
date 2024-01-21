#pragma once

#ifndef ENGINE_GRAPHICS_DEBUG_H
#define ENGINE_GRAPHICS_DEBUG_H

#include "color.h"
#include "font.h"
#include "../math/vectors.h"

#ifdef USE_TEMPLATED_DRAW_INFO
#include "../App/app.h"
#endif


constexpr int BOUNDS_PADDING = 1000;
#define OUT_OF_BOUNDS(position) (position).x < (-BOUNDS_PADDING) || (position).x > (APP_VIRTUAL_WIDTH + BOUNDS_PADDING) || (position).y < (-BOUNDS_PADDING) || (position).y > (APP_VIRTUAL_HEIGHT + BOUNDS_PADDING)

namespace gfx
{
    // A set of graphical debugging utilities
    struct Debug
    {
        // Default Color to draw with
        static Color draw_color;

        // Default padding amount
        static math::IVec2 padding;

        // Default Font to use
        static Font font;

        static void DrawRect(const math::IVec2& top_left, const math::IVec2& dimensions, const Color& color = draw_color);
        static void DrawPaddedRect(const math::IVec2& top_left, const math::IVec2& dimensions, const math::IVec2& pad = padding);
        static void DrawPaddedRect(const math::IVec2& top_left, const math::IVec2& dimensions, const Color& color = draw_color, const math::IVec2& pad = padding);

        // data utility functions

#ifdef USE_TEMPLATED_DRAW_INFO
        template <typename T>
        static void DrawInfo(T data, math::IVec2 position = math::IVec2::Zero, Color color = draw_color);
#endif
        static void DrawInfo(const math::IVec2& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);
        static void DrawInfo(const math::Vec2& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);
        static void DrawInfo(const math::Vec3& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);
        static void DrawInfo(const math::Vec4& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);
        static void DrawInfo(const math::Quaternion& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);
        static void DrawInfo(const Font& data, const math::IVec2& position = math::IVec2::Zero, const Color& color = draw_color);

        static const math::IVec2 ScreenDimensions;
    };
    
#ifdef USE_TEMPLATED_DRAW_INFO
    template <typename T>
    void Debug::DrawInfo(T data, const math::IVec2 position, const Color color)
    {
        const auto pos = math::Vec2(position);
        App::Print(pos.x, pos.y, std::to_string(data).c_str(), color.r, color.g, color.b, font);
    }
#endif

}


#endif