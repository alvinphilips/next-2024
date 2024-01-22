#pragma once

#ifndef ENGINE_MATH_UTILS_H
#define ENGINE_MATH_UTILS_H

#include "vectors.h"
#include "../../App/AppSettings.h"

namespace math
{
    struct Rect
    {
        Vec2 min;
        Vec2 max;
        
        explicit Rect();
        explicit Rect(const Vec2& min, const Vec2& max);

        bool Contains(const Vec2& point) const;
        Vec2 ClampPoint(const Vec2& point) const;

        static Rect OriginAndDimensions(const Vec2& origin, const Vec2& dimensions);
    };

    template <typename T>
    T clamp(const T& val, const T& low, const T& high)
    {
        return val < low ? low : val > high ? high : val;
    }

    constexpr float TAU = PI * 2;
}

#endif