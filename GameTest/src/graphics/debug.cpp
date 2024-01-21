#include "stdafx.h"
#include "debug.h"

#include <string>

#include "../math/quaternion.h"
#include "../App/app.h"

namespace gfx {
    using namespace math;

    void Debug::DrawRect(const IVec2& top_left, const IVec2& dimensions, const Color& color) {
        if (OUT_OF_BOUNDS(top_left)) { return; }
        const auto tl = Vec2(top_left);
        const auto br = Vec2(top_left + dimensions);

        const float& top = tl.y;
        const float& bottom = br.y;
        const float& left = tl.x;
        const float& right = br.x;


        App::DrawLine(left, top, right, top, color.r, color.g, color.b);
        App::DrawLine(left, bottom, right, bottom, color.r, color.g, color.b);
        App::DrawLine(left, top, left, bottom, color.r, color.g, color.b);
        App::DrawLine(right, top, right, bottom, color.r, color.g, color.b);
    }

    void Debug::DrawPaddedRect(const IVec2& top_left, const IVec2& dimensions, const IVec2& pad)
    {
        DrawPaddedRect(top_left, dimensions, draw_color, pad);
    }

    void Debug::DrawPaddedRect(const IVec2& top_left, const IVec2& dimensions, const Color& color, const IVec2& pad)
    {
        const auto padded_top_left = top_left - pad;
        const auto padded_dimensions = dimensions + pad * 2;

        DrawRect(padded_top_left, padded_dimensions, color);
    }

    void Debug::DrawInfo(const IVec2& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        const auto text = std::to_string(data.x) + ", " + std::to_string(data.y);
        App::Print(pos.x, pos.y, text.c_str(), color.r, color.g, color.b, font);
    }

    void Debug::DrawInfo(const Vec2& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        const auto text = std::to_string(data.x) + ", " + std::to_string(data.y);
        App::Print(pos.x, pos.y, text.c_str(), color.r, color.g, color.b, font);
    }

    void Debug::DrawInfo(const Vec3& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        const auto text = std::to_string(data.x) + ", " + std::to_string(data.y) + ", " + std::to_string(data.z);
        App::Print(pos.x, pos.y, text.c_str(), color.r, color.g, color.b, font);
    }

    void Debug::DrawInfo(const Vec4& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        const auto text = std::to_string(data.x) + ", " + std::to_string(data.y) + ", " + std::to_string(data.z) + ", " + std::to_string(data.w);
        App::Print(pos.x, pos.y, text.c_str(), color.r, color.g, color.b, font);
    }

    void Debug::DrawInfo(const Quaternion& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        const auto text = "w: " + std::to_string(data.w) + " | xyz: " + std::to_string(data.x) + ", " + std::to_string(data.y) + ", " + std::to_string(data.z);
        App::Print(pos.x, pos.y, text.c_str(), color.r, color.g, color.b, font);
    }

    void Debug::DrawInfo(const Font& data, const IVec2& position, const Color& color)
    {
        if (OUT_OF_BOUNDS(position)) { return; }
        const auto pos = Vec2(position);
        App::Print(pos.x, pos.y, FontUtils::GetInfo(data).name, color.r, color.g, color.b, data);
    }

    Color Debug::draw_color = Color(255, 255, 255);
    IVec2 Debug::padding = IVec2(5);
    Font Debug::font = GLUT_BITMAP_8_BY_13;
}