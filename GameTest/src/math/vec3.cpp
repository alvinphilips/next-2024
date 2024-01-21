#include "stdafx.h"
#include "vectors.h"

#include <cmath>

namespace math {
    Vec3::Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec3::Vec3(const float value) {
        x = value;
        y = value;
        z = value;
    }

    Vec3::Vec3(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3::Vec3(const Vec2& vec2, const float z) {
        this->x = vec2.x;
        this->y = vec2.y;
        this->z = z;
    }

    Vec3 Vec3::operator-() const {
        return Vec3(-x, -y, -z);
    }

    Vec3& Vec3::operator+=(const Vec3& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;

        return *this;
    }

    Vec3& Vec3::operator-=(const Vec3& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;

        return *this;
    }

    bool Vec3::operator==(const Vec3& rhs) const
    {
        return std::abs(this->x - rhs.x) <= GAME_FLT_EPSILON && std::abs(this->y - rhs.y) <= GAME_FLT_EPSILON && std::abs(this->z - rhs.z) <= GAME_FLT_EPSILON;
    }

    bool Vec3::operator!=(const Vec3& rhs) const
    {
        return !(*this == rhs);
    }

    // Cursed shader-programmer zone starts
    Vec3& Vec3::operator*=(const Vec3& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;

        return *this;
    }

    Vec3& Vec3::operator/=(const Vec3& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;

        return *this;
    }
    // Cursed shader-programmer zone ends

    Vec3& Vec3::operator*=(const float f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;

        return *this;
    }

    Vec3& Vec3::operator/=(const float f)
    {
        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        this->x *= inv_f;
        this->y *= inv_f;
        this->z *= inv_f;

        return *this;
    }

    Vec3 Vec3::operator+(const Vec3& rhs) const
    {
        Vec3 res;

        res.x = this->x + rhs.x;
        res.y = this->y + rhs.y;
        res.z = this->z + rhs.z;

        return res;
    }

    Vec3 Vec3::operator-(const Vec3& rhs) const
    {
        Vec3 res;

        res.x = this->x - rhs.x;
        res.y = this->y - rhs.y;
        res.z = this->z - rhs.z;

        return res;
    }

    // Cursed shader-programmer zone starts
    Vec3 Vec3::operator*(const Vec3& rhs) const
    {
        Vec3 res;

        res.x = this->x * rhs.x;
        res.y = this->y * rhs.y;
        res.z = this->z * rhs.z;

        return res;
    }

    Vec3 Vec3::operator/(const Vec3& rhs) const
    {
        Vec3 res;

        res.x = this->x / rhs.x;
        res.y = this->y / rhs.y;
        res.z = this->z / rhs.z;

        return res;
    }
    // Cursed shader-programmer zone ends

    Vec3 Vec3::operator*(const float f) const
    {
        Vec3 res;

        res.x = this->x * f;
        res.y = this->y * f;
        res.z = this->z * f;

        return res;
    }

    Vec3 Vec3::operator/(const float f) const
    {
        Vec3 res;

        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        res.x = this->x * inv_f;
        res.y = this->y * inv_f;
        res.z = this->z * inv_f;

        return res;
    }

    Vec3 Vec3::Abs() const
    {
        Vec3 res;

        res.x = std::abs(this->x);
        res.y = std::abs(this->y);
        res.z = std::abs(this->z);

        return res;
    }

    float Vec3::Magnitude() const
    {
        return std::sqrtf(this->MagnitudeSquared());
    }

    float Vec3::MagnitudeSquared() const
    {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    void Vec3::Normalize()
    {
        const float mag = this->Magnitude();

        if (mag > 0.0f) {
            *this /= mag;
        }
    }

    float Vec3::Dot(const Vec3& rhs) const
    {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }

    float Vec3::Dot(const Vec3& lhs, const Vec3& rhs)
    {

        return lhs.Dot(rhs);
    }

    Vec3 Vec3::Cross(const Vec3& rhs) const
    {
        Vec3 res;

        res.x = this->y * rhs.z - this->z * rhs.y;
        res.y = this->z * rhs.x - this->x * rhs.z;
        res.z = this->x * rhs.y - this->y * rhs.x;

        return res;
    }

    Vec3 Vec3::Cross(const Vec3& lhs, const Vec3& rhs)
    {
        return lhs.Cross(rhs);
    }

    float Vec3::Distance(const Vec3& rhs) const {
        return (*this - rhs).Magnitude();
    }

    float Vec3::Distance(const Vec3& lhs, const Vec3& rhs) {
        return (lhs - rhs).Magnitude();
    }

    Vec3 Vec3::Lerp(const Vec3& lhs, const Vec3& rhs, const float t)
    {
        return lhs + (rhs - lhs) * t;
    }

    const Vec3 Vec3::Right = Vec3(1, 0, 0);
    const Vec3 Vec3::Up = Vec3(0, 1, 0);
    const Vec3 Vec3::Forward = Vec3(0, 0, 1);
    const Vec3 Vec3::Zero = Vec3();
}
