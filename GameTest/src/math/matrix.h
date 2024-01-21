#pragma once

#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "vectors.h"

namespace math
{
	// 4x4 Matrix
	union Mat4 {
		float values[16];
		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
		struct {
			Vec4 r1;
			Vec4 r2;
			Vec4 r3;
			Vec4 r4;
		};

		explicit Mat4();
		explicit Mat4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);
		explicit Mat4(const float values[16]);
		
		Mat4 operator+(const Mat4& rhs) const;
		Mat4 operator-(const Mat4& rhs) const;
		Mat4& operator+=(const Mat4& rhs);
		Mat4& operator-=(const Mat4& rhs);

		// TODO: implement
		Mat4 operator*(const Mat4& rhs) const;
		Mat4 operator*=(const Mat4& rhs) const;

		// Scalar stuff
		Mat4 operator*(float scale) const;
		Mat4 operator/(float scale) const;
		Mat4 operator*=(float scale);
		Mat4 operator/=(float scale);

		static const Mat4 Identity;
	};
}

#endif