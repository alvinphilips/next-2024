#include "stdafx.h"
#include "quaternion.h"
#include "vectors.h"

#include <cmath>

namespace math {
    Quaternion::Quaternion()
    {
        w = 1;
        x = 0;
        y = 0;
        z = 0;
    }

    Quaternion::Quaternion(const float w, const float x, const float y, const float z)
    {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Quaternion::Quaternion(const float w, const Vec3& vec3)
    {
        this->w = w;
        this->x = vec3.x;
        this->y = vec3.y;
        this->z = vec3.z;
    }

    Quaternion::Quaternion(const Vec4& vec4)
    {
        this->w = vec4.w;
        this->x = vec4.x;
        this->y = vec4.y;
        this->z = vec4.z;
    }

    Quaternion Quaternion::operator*(const Quaternion& rhs) const
    {
        Quaternion res;
        res.w = this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z;
        res.x = this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y;
        res.y = this->w * rhs.y + this->y * rhs.w + this->z * rhs.x - this->x * rhs.z;
        res.z = this->w * rhs.z + this->z * rhs.w + this->x * rhs.y - this->y * rhs.x;

        return res;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& rhs)
    {
        *this = *this * rhs;
        // A sky full of asterisks
        return *this;
    }

    float Quaternion::Magnitude() const
    {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    void Quaternion::Normalize()
    {
        const float mag = this->Magnitude();

        if (mag > 0.0f)
        {
            const float inv_mag = 1.0f / mag;

            w *= inv_mag;
            x *= inv_mag;
            y *= inv_mag;
            z *= inv_mag;
        }
    }

    Vec3 Quaternion::Rotate(const Vec3& in) const
    {
        const Quaternion quat_in(0, in);
        const Quaternion res = *this * quat_in * Conjugate();

        return Vec3(res.x, res.y, res.z);
    }

    Quaternion Quaternion::Conjugate() const
    {
        return Quaternion(w, -x, -y, -z);
    }

    Quaternion Quaternion::AxisAngle(const Vec3& axis, const float rad)
    {
        const float half_angle = rad * 0.5f;

        return Quaternion(std::cos(half_angle), axis * std::sin(half_angle));
    }

    Quaternion Quaternion::Lerp(const Quaternion& lhs, const Quaternion& rhs, const float t)
    {
        const float one_minus_t = 1.0f - t;

        return Quaternion(
            one_minus_t * lhs.w + t * rhs.w,
            one_minus_t * lhs.x + t * rhs.x,
            one_minus_t * lhs.y + t * rhs.y,
            one_minus_t * lhs.z + t * rhs.z
        );
    }

    const Quaternion Quaternion::Identity = Quaternion();

}