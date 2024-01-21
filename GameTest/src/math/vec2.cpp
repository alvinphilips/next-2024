#include "stdafx.h"
#include "vectors.h"

#include <cmath>

namespace math {
    Vec2::Vec2() {
        x = 0;
        y = 0;
    }

    Vec2::Vec2(const float value) {
        x = value;
        y = value;
    }

    Vec2::Vec2(const float x, const float y) {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(const IVec2& ivec2)
    {
        this->x = static_cast<float>(ivec2.x);
        this->y = static_cast<float>(ivec2.y);
    }

    Vec2 Vec2::operator-() const {
        return Vec2(-x, -y);
    }

    Vec2& Vec2::operator+=(const Vec2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }

    Vec2& Vec2::operator-=(const Vec2& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;

        return *this;
    }

    bool Vec2::operator==(const Vec2& rhs) const
    {
        return std::abs(this->x - rhs.x) <= GAME_FLT_EPSILON && std::abs(this->y - rhs.y) <= GAME_FLT_EPSILON;
    }

    bool Vec2::operator!=(const Vec2& rhs) const
    {
        return !(*this == rhs);
    }

    // Cursed shader-programmer zone starts
    Vec2& Vec2::operator*=(const Vec2& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;

        return *this;
    }

    Vec2& Vec2::operator/=(const Vec2& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;

        return *this;
    }
    // Cursed shader-programmer zone ends

    Vec2& Vec2::operator*=(const float f)
    {
        this->x *= f;
        this->y *= f;

        return *this;
    }

    Vec2& Vec2::operator/=(const float f)
    {
        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        this->x *= inv_f;
        this->y *= inv_f;

        return *this;
    }

    Vec2 Vec2::operator+(const Vec2& rhs) const
    {
        Vec2 res;

        res.x = this->x + rhs.x;
        res.y = this->y + rhs.y;

        return res;
    }

    Vec2 Vec2::operator-(const Vec2& rhs) const
    {
        Vec2 res;

        res.x = this->x - rhs.x;
        res.y = this->y - rhs.y;

        return res;
    }

    // Element-wise multiplication of two Vectors.
    Vec2 Vec2::operator*(const Vec2& rhs) const
    {
        Vec2 res;

        res.x = this->x * rhs.x;
        res.y = this->y * rhs.y;

        return res;
    }
    
    // Element-wise multiplication of two Vectors.
    Vec2 Vec2::operator/(const Vec2& rhs) const
    {
        Vec2 res;

        res.x = this->x / rhs.x;
        res.y = this->y / rhs.y;

        return res;
    }
    // Cursed shader-programmer zone ends

    Vec2 Vec2::operator*(const float f) const
    {
        Vec2 res;

        res.x = this->x * f;
        res.y = this->y * f;

        return res;
    }

    Vec2 Vec2::operator/(const float f) const
    {
        Vec2 res;

        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        res.x = this->x * inv_f;
        res.y = this->y * inv_f;

        return res;
    }

    Vec2 Vec2::Abs() const
    {
        Vec2 res;

        res.x = std::abs(this->x);
        res.y = std::abs(this->y);

        return res;
    }

    float Vec2::Magnitude() const
    {
        return std::sqrtf(this->MagnitudeSquared());
    }

    float Vec2::MagnitudeSquared() const
    {
        return this->x * this->x + this->y * this->y;
    }

    void Vec2::Normalize()
    {
        const float mag = this->Magnitude();

        if (mag > 0.0f)
        {
            *this /= mag;
        }
    }

    float Vec2::Dot(const Vec2& rhs) const
    {
        return this->x * rhs.x + this->y * rhs.y;
    }

    float Vec2::Dot(const Vec2& lhs, const Vec2& rhs)
    {

        return lhs.Dot(rhs);
    }

    // Not really, but nice to have :P
    float Vec2::Cross(const Vec2& rhs) const
    {
        return this->x * rhs.y + this->y * rhs.x;
    }

    float Vec2::Cross(const Vec2& lhs, const Vec2& rhs)
    {

        return lhs.Cross(rhs);
    }

    float Vec2::Distance(const Vec2& rhs) const {
        return (*this - rhs).Magnitude();
    }

    float Vec2::Distance(const Vec2& lhs, const Vec2& rhs) {
        return (lhs - rhs).Magnitude();
    }

    Vec2 Vec2::Lerp(const Vec2& lhs, const Vec2& rhs, const float t)
    {
        return lhs + (rhs - lhs) * t;
    }

    const Vec2 Vec2::UnitX = Vec2(1, 0);
    const Vec2 Vec2::UnitY = Vec2(0, 1);
    const Vec2 Vec2::Zero = Vec2();
}
