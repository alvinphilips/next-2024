#include "stdafx.h"
#include "utils.h"

namespace math
{
    Rect::Rect()
    {
        min = Vec2();
        max = Vec2();
    }

    Rect::Rect(const Vec2& min, const Vec2& max)
    {
        this->min = min;
        this->max = max;
    }

    bool Rect::Contains(const Vec2& point) const
    {
        return min.x < point.x && point.x < max.x && min.y < point.y && point.y < max.y;
    }

    Vec2 Rect::ClampPoint(const Vec2& point) const
    {
        return Vec2(clamp(point.x, min.x, max.x), clamp(point.y, min.y, max.y));
    }

    Rect Rect::OriginAndDimensions(const Vec2& origin, const Vec2& dimensions)
    {
        const Vec2 half_dim = dimensions * 0.5f;
        return Rect(origin - half_dim, origin + half_dim);
    }

}
