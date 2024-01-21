#include "stdafx.h"
#include "vectors.h"

#include <cmath>

#include "quaternion.h"

namespace math {
    Vec4::Vec4() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vec4::Vec4(const float value) {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    Vec4::Vec4(const float x, const float y, const float z, const float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vec4::Vec4(const Vec3& vec3, const float w) {
        this->x = vec3.x;
        this->y = vec3.y;
        this->z = vec3.z;
        this->w = w;
    }

    Vec4::Vec4(const Quaternion& quat)
    {
        this->x = quat.x;
        this->y = quat.y;
        this->z = quat.z;
        this->w = quat.w;
    }

    Vec4 Vec4::operator-() const {
        return Vec4(-x, -y, -z, -w);
    }

    Vec4& Vec4::operator+=(const Vec4& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;

        return *this;
    }

    Vec4& Vec4::operator-=(const Vec4& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        this->w -= rhs.w;

        return *this;
    }

    bool Vec4::operator==(const Vec4& rhs) const
    {
        return std::abs(this->x - rhs.x) <= GAME_FLT_EPSILON && std::abs(this->y - rhs.y) <= GAME_FLT_EPSILON && std::abs(this->z - rhs.z) <= GAME_FLT_EPSILON && std::abs(this->w - rhs.w) <= GAME_FLT_EPSILON;
    }

    bool Vec4::operator!=(const Vec4& rhs) const
    {
        return !(*this == rhs);
    }

    // Cursed shader-programmer zone starts
    Vec4& Vec4::operator*=(const Vec4& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        this->w *= rhs.w;

        return *this;
    }

    Vec4& Vec4::operator/=(const Vec4& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        this->w /= rhs.w;

        return *this;
    }
    // Cursed shader-programmer zone ends

    Vec4& Vec4::operator*=(const float f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        this->w *= f;

        return *this;
    }

    Vec4& Vec4::operator/=(const float f)
    {
        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        this->x *= inv_f;
        this->y *= inv_f;
        this->z *= inv_f;
        this->w *= inv_f;

        return *this;
    }

    Vec4 Vec4::operator+(const Vec4& rhs) const
    {
        Vec4 res;

        res.x = this->x + rhs.x;
        res.y = this->y + rhs.y;
        res.z = this->z + rhs.z;
        res.w = this->w + rhs.w;

        return res;
    }

    Vec4 Vec4::operator-(const Vec4& rhs) const
    {
        Vec4 res;

        res.x = this->x - rhs.x;
        res.y = this->y - rhs.y;
        res.z = this->z - rhs.z;
        res.w = this->w - rhs.w;

        return res;
    }

    // Cursed shader-programmer zone starts
    Vec4 Vec4::operator*(const Vec4& rhs) const
    {
        Vec4 res;

        res.x = this->x * rhs.x;
        res.y = this->y * rhs.y;
        res.z = this->z * rhs.z;
        res.w = this->w * rhs.w;

        return res;
    }

    Vec4 Vec4::operator/(const Vec4& rhs) const
    {
        Vec4 res;

        res.x = this->x / rhs.x;
        res.y = this->y / rhs.y;
        res.z = this->z / rhs.z;
        res.w = this->w / rhs.w;

        return res;
    }
    // Cursed shader-programmer zone ends

    Vec4 Vec4::operator*(const float f) const
    {
        Vec4 res;

        res.x = this->x * f;
        res.y = this->y * f;
        res.z = this->z * f;
        res.w = this->w * f;

        return res;
    }

    Vec4 Vec4::operator/(const float f) const
    {
        Vec4 res;

        // TODO: figure out if this even helps :P
        const float inv_f = 1.0f / f;

        res.x = this->x * inv_f;
        res.y = this->y * inv_f;
        res.z = this->z * inv_f;
        res.w = this->w * inv_f;

        return res;
    }

    Vec4 Vec4::Abs() const
    {
        Vec4 res;

        res.x = std::abs(this->x);
        res.y = std::abs(this->y);
        res.z = std::abs(this->z);
        res.w = std::abs(this->w);

        return res;
    }

    float Vec4::Magnitude() const
    {
        return std::sqrtf(this->MagnitudeSquared());
    }

    float Vec4::MagnitudeSquared() const
    {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    void Vec4::Normalize()
    {
        const float mag = this->Magnitude();

        if (mag > 0.0f) {
            *this /= mag;
        }
    }

    const Vec4 Vec4::Zero = Vec4();
}
