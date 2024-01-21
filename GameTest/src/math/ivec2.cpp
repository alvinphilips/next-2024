#include "stdafx.h"
#include "vectors.h"

#include <cmath>

namespace math {
    IVec2::IVec2() {
        x = 0;
        y = 0;
    }

    IVec2::IVec2(const int value) {
        x = value;
        y = value;
    }

    IVec2::IVec2(const int x, const int y) {
        this->x = x;
        this->y = y;
    }

    IVec2::IVec2(const Vec2& vec2)
    {
        this->x = static_cast<int>(vec2.x);
        this->y = static_cast<int>(vec2.y);
    }

    IVec2 IVec2::operator-() const {
        return IVec2(-x, -y);
    }

    IVec2& IVec2::operator+=(const IVec2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }

    IVec2& IVec2::operator-=(const IVec2& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;

        return *this;
    }

    bool IVec2::operator==(const IVec2& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }

    bool IVec2::operator!=(const IVec2& rhs) const
    {
        return !(*this == rhs);
    }

    // Cursed shader-programmer zone starts
    IVec2& IVec2::operator*=(const IVec2& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;

        return *this;
    }

    IVec2& IVec2::operator/=(const IVec2& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;

        return *this;
    }
    // Cursed shader-programmer zone ends

    IVec2& IVec2::operator*=(const int f)
    {
        this->x *= f;
        this->y *= f;

        return *this;
    }

    IVec2& IVec2::operator/=(const int f)
    {
        this->x /= f;
        this->y /= f;

        return *this;
    }

    IVec2 IVec2::operator+(const IVec2& rhs) const
    {
        IVec2 res;

        res.x = this->x + rhs.x;
        res.y = this->y + rhs.y;

        return res;
    }

    IVec2 IVec2::operator-(const IVec2& rhs) const
    {
        IVec2 res;

        res.x = this->x - rhs.x;
        res.y = this->y - rhs.y;

        return res;
    }

    // Element-wise multiplication of two Vectors.
    IVec2 IVec2::operator*(const IVec2& rhs) const
    {
        IVec2 res;

        res.x = this->x * rhs.x;
        res.y = this->y * rhs.y;

        return res;
    }
    
    // Element-wise division of two Vectors.
    IVec2 IVec2::operator/(const IVec2& rhs) const
    {
        IVec2 res;

        res.x = this->x / rhs.x;
        res.y = this->y / rhs.y;

        return res;
    }
    // Cursed shader-programmer zone ends

    IVec2 IVec2::operator*(const int f) const
    {
        IVec2 res;

        res.x = this->x * f;
        res.y = this->y * f;

        return res;
    }

    IVec2 IVec2::operator/(const int f) const
    {
        IVec2 res;

        res.x = this->x / f;
        res.y = this->y / f;

        return res;
    }

    IVec2 IVec2::Abs() const
    {
        IVec2 res;

        res.x = std::abs(this->x);
        res.y = std::abs(this->y);

        return res;
    }

    const IVec2 IVec2::UnitX = IVec2(1, 0);
    const IVec2 IVec2::UnitY = IVec2(0, 1);
    const IVec2 IVec2::Zero = IVec2();
}
