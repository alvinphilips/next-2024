#include "stdafx.h"
#include "matrix.h"

namespace math
{
	Mat4::Mat4()
	{
		*this = Identity;
	}

	Mat4::Mat4(const float values[16])
	{
		for (int i = 0; i < 16; i++)
		{
			this->values[i] = values[i];
		}
	}

	Mat4 Mat4::operator+(const Mat4& rhs) const
	{
		Mat4 res;

		for (int i = 0; i < 16; i++)
		{
			res.values[i] = this->values[i] + rhs.values[i];
		}

		return res;
	}

	Mat4 Mat4::operator-(const Mat4& rhs) const
	{
		Mat4 res;

		for (int i = 0; i < 16; i++)
		{
			res.values[i] = this->values[i] - rhs.values[i];
		}

		return res;
	}

	Mat4& Mat4::operator+=(const Mat4& rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			this->values[i] += rhs.values[i];
		}

		return *this;
	}

	Mat4& Mat4::operator-=(const Mat4& rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			this->values[i] -= rhs.values[i];
		}

		return *this;
	}

	Mat4 Mat4::operator*(const float scale) const
	{
		Mat4 res;

		for (int i = 0; i < 16; i++)
		{
			res.values[i] = this->values[i] * scale;
		}

		return res;
	}

	Mat4 Mat4::operator/(const float scale) const
	{
		return *this * (1.0f / scale);
	}

	Mat4 Mat4::operator*=(const float scale)
	{
		for (float& value : this->values)
		{
			value *= scale;
		}

		return *this;
	}

	Mat4 Mat4::operator/=(const float scale)
	{
		*this *= (1.0f / scale);

		return *this;
	}

	Mat4::Mat4(
		const float m11, const float m12, const float m13, const float m14,
		const float m21, const float m22, const float m23, const float m24,
		const float m31, const float m32, const float m33, const float m34,
		const float m41, const float m42, const float m43, const float m44)
	{
		this->m11 = m11;
		this->m12 = m12;
		this->m13 = m13;
		this->m14 = m14;

		this->m21 = m21;
		this->m22 = m22;
		this->m23 = m23;
		this->m24 = m24;

		this->m31 = m31;
		this->m32 = m32;
		this->m33 = m33;
		this->m34 = m34;

		this->m41 = m41;
		this->m42 = m42;
		this->m43 = m43;
		this->m44 = m44;
	}


	const Mat4 Mat4::Identity = Mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
