#pragma once

#ifndef ENGINE_MATH_QUATERNION_H
#define ENGINE_MATH_QUATERNION_H

namespace math {
    struct Vec3;
    struct Vec4;

    struct Quaternion {
        float w;
        float x;
        float y;
        float z;

        explicit Quaternion();
        explicit Quaternion(float, float, float, float);
        explicit Quaternion(float, const Vec3&);
        explicit Quaternion(const Vec4&);

        Quaternion operator*(const Quaternion& rhs) const;
        Quaternion& operator*=(const Quaternion& rhs);

        float Magnitude() const;
        void Normalize();

        Vec3 Rotate(const Vec3& in) const;

        Quaternion Conjugate() const;
        static Quaternion AxisAngle(const Vec3&, float);

        static Quaternion Lerp(const Quaternion& lhs, const Quaternion& rhs, float t);

        const static Quaternion Identity;
    };

}

#endif