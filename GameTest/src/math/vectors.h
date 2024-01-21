#pragma once

#ifndef ENGINE_MATH_VECTOR_H
#define ENGINE_MATH_VECTOR_H

#include <cfloat>
#define GAME_FLT_EPSILON FLT_EPSILON

namespace math {
    struct Quaternion;
    struct IVec2;
	union Mat4;

    struct Vec2 {
        float x;
        float y;

        explicit Vec2();
        explicit Vec2(float);
        explicit Vec2(float, float);
        explicit Vec2(const IVec2&);

        Vec2 operator-() const;
        Vec2& operator+=(const Vec2& rhs);
        Vec2& operator-=(const Vec2& rhs);

        bool operator==(const Vec2& rhs) const;
        bool operator!=(const Vec2& rhs) const;

        // Cursed shader-programmer zone starts
        Vec2& operator*=(const Vec2& rhs);
        Vec2& operator/=(const Vec2& rhs);
        // Cursed shader-programmer zone ends

        Vec2& operator*=(float f);
        Vec2& operator/=(float f);

        Vec2 operator+(const Vec2& rhs) const;
        Vec2 operator-(const Vec2& rhs) const;

        // Cursed shader-programmer zone starts
        Vec2 operator*(const Vec2& rhs) const;
        Vec2 operator/(const Vec2& rhs) const;
        // Cursed shader-programmer zone ends

        Vec2 operator*(float f) const;
        Vec2 operator/(float f) const;

        Vec2 Abs() const;

        float Magnitude() const;
        float MagnitudeSquared() const;
        void Normalize();

        float Dot(const Vec2& rhs) const;
        static float Dot(const Vec2& lhs, const Vec2& rhs);

        // Not really, but nice to have :P
        float Cross(const Vec2& rhs) const;
        static float Cross(const Vec2& lhs, const Vec2& rhs);

        float Distance(const Vec2& rhs) const;
        static float Distance(const Vec2& lhs, const Vec2& rhs);

        static Vec2 Lerp(const Vec2& lhs, const Vec2& rhs, float t);

        static const Vec2 Zero;
        static const Vec2 UnitX;
        static const Vec2 UnitY;
    };

    struct Vec3 {
        float x;
        float y;
        float z;

        explicit Vec3();
        explicit Vec3(float);
        explicit Vec3(float, float, float);
        explicit Vec3(const Vec2&, float);

        Vec3 operator-() const;
        Vec3& operator+=(const Vec3& rhs);
        Vec3& operator-=(const Vec3& rhs);

        bool operator==(const Vec3& rhs) const;
        bool operator!=(const Vec3& rhs) const;

        // Cursed shader-programmer zone starts
        Vec3& operator*=(const Vec3& rhs);
        Vec3& operator/=(const Vec3& rhs);
        // Cursed shader-programmer zone ends

        Vec3& operator*=(float f);
        Vec3& operator/=(float f);

        Vec3 operator+(const Vec3& rhs) const;
        Vec3 operator-(const Vec3& rhs) const;

        // Cursed shader-programmer zone starts
        Vec3 operator*(const Vec3& rhs) const;
        Vec3 operator/(const Vec3& rhs) const;
        // Cursed shader-programmer zone ends

        Vec3 operator*(float f) const;
        Vec3 operator/(float f) const;

        Vec3 Abs() const;

        float Magnitude() const;
        float MagnitudeSquared() const;
        void Normalize();

        float Dot(const Vec3& rhs) const;
        static float Dot(const Vec3& lhs, const Vec3& rhs);

        Vec3 Cross(const Vec3& rhs) const;
        static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);

        float Distance(const Vec3& rhs) const;
        static float Distance(const Vec3& lhs, const Vec3& rhs);

        static Vec3 Lerp(const Vec3& lhs, const Vec3& rhs, float t);

        static const Vec3 Zero;
        static const Vec3 Forward;
        static const Vec3 Up;
        static const Vec3 Right;
    };

    struct Vec4 {
        float x;
        float y;
        float z;
        float w;

        explicit Vec4();
        explicit Vec4(float);
        explicit Vec4(float, float, float, float);
        explicit Vec4(const Vec3&, float w=1);
        explicit Vec4(const Quaternion&);

        Vec4 operator-() const;
        Vec4& operator+=(const Vec4& rhs);
        Vec4& operator-=(const Vec4& rhs);

        bool operator==(const Vec4& rhs) const;
        bool operator!=(const Vec4& rhs) const;

        // Cursed shader-programmer zone starts
        Vec4& operator*=(const Vec4& rhs);
        Vec4& operator/=(const Vec4& rhs);
        // Cursed shader-programmer zone ends

        Vec4& operator*=(float f);
        Vec4& operator/=(float f);

        Vec4 operator+(const Vec4& rhs) const;
        Vec4 operator-(const Vec4& rhs) const;

        // Cursed shader-programmer zone starts
        Vec4 operator*(const Vec4& rhs) const;
        Vec4 operator/(const Vec4& rhs) const;
        // Cursed shader-programmer zone ends

        Vec4 operator*(float f) const;
        Vec4 operator/(float f) const;

        // TODO: implement
        Vec4 operator*=(const Mat4& matrix);
        Vec4 operator*(const Mat4& matrix) const;

        Vec4 Abs() const;

        float Magnitude() const;
        float MagnitudeSquared() const;
        void Normalize();

        static const Vec4 Zero;
    };

    struct IVec2 {
        int x;
        int y;

        explicit IVec2();
        explicit IVec2(int);
        explicit IVec2(int, int);
        explicit IVec2(const Vec2&);

        IVec2 operator-() const;
        IVec2& operator+=(const IVec2& rhs);
        IVec2& operator-=(const IVec2& rhs);

        bool operator==(const IVec2& rhs) const;
        bool operator!=(const IVec2& rhs) const;

        // Cursed shader-programmer zone starts
        IVec2& operator*=(const IVec2& rhs);
        IVec2& operator/=(const IVec2& rhs);
        // Cursed shader-programmer zone ends

        IVec2& operator*=(int f);
        IVec2& operator/=(int f);

        IVec2 operator+(const IVec2& rhs) const;
        IVec2 operator-(const IVec2& rhs) const;

        // Cursed shader-programmer zone starts
        IVec2 operator*(const IVec2& rhs) const;
        IVec2 operator/(const IVec2& rhs) const;
        // Cursed shader-programmer zone ends

        IVec2 operator*(int f) const;
        IVec2 operator/(int f) const;

        IVec2 Abs() const;

        static const IVec2 Zero;
        static const IVec2 UnitX;
        static const IVec2 UnitY;
    };
}

#endif