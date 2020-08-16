#pragma once
#include <algorithm>
#include "vector4.hpp"

namespace SFWR::Math
{
	// Row - major 4x4 matrix
	struct Matrix4
	{
		Matrix4() = default;
		~Matrix4() = default;

		Matrix4( const Matrix4& src);

		Matrix4& setTranslation(const SFWR::Math::Vector4& translation);

		Matrix4& transpose();

		float m[4][4] = { 0 };
	};

	inline Matrix4::Matrix4(const Matrix4& src)
	{
		std::copy(&src.m[0][0], &src.m[0][0] + 16, &m[0][0]);
	}

	inline Matrix4& Matrix4::setTranslation(const SFWR::Math::Vector4& translation)
	{
		m[3][0] = translation.m_x; m[3][1] = translation.m_y; m[3][2] = translation.m_z; m[3][3] = translation.m_w;
	}

	inline Matrix4& Matrix4::transpose()
	{
		std::swap(m[0][1], m[1][0]);
		std::swap(m[0][2], m[2][0]);
		std::swap(m[0][3], m[3][0]);

		std::swap(m[1][2], m[2][1]);
		std::swap(m[1][3], m[3][1]);

		std::swap(m[2][3], m[3][2]);

		return *this;
	}

	inline Matrix4 initIdentityMatrix()
	{
		Matrix4 identity;
		identity.m[0][0] = 1.0f; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
		identity.m[1][0] = 0.0f; identity.m[1][1] = 1.0f; identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
		identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = 1.0f; identity.m[2][3] = 0.0f;
		identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;

		return identity;
	}

	inline Vector4 operator*( const Vector4& v, const Matrix4& matrix)
	{
		return
		{
				v.m_x * matrix.m[0][0] + v.m_y * matrix.m[1][0] + v.m_z * matrix.m[2][0] + v.m_w * matrix.m[3][0],
				v.m_x * matrix.m[0][1] + v.m_y * matrix.m[1][1] + v.m_z * matrix.m[2][1] + v.m_w * matrix.m[3][1],
				v.m_x * matrix.m[0][2] + v.m_y * matrix.m[1][2] + v.m_z * matrix.m[2][2] + v.m_w * matrix.m[3][2],
				v.m_x * matrix.m[0][3] + v.m_y * matrix.m[1][3] + v.m_z * matrix.m[2][3] + v.m_w * matrix.m[3][3]
		};
	}

	inline Matrix4 operator*(const Matrix4& matrixL, const Matrix4& matrixR)
	{
		Matrix4 r;

		r.m[0][0] = matrixL.m[0][0] * matrixR.m[0][0] + matrixL.m[0][1] * matrixR.m[1][0] + matrixL.m[0][2] * matrixR.m[2][0] + matrixL.m[0][3] * matrixR.m[3][0];
		r.m[0][1] = matrixL.m[0][0] * matrixR.m[0][1] + matrixL.m[0][1] * matrixR.m[1][1] + matrixL.m[0][2] * matrixR.m[2][1] + matrixL.m[0][3] * matrixR.m[3][1];
		r.m[0][2] = matrixL.m[0][0] * matrixR.m[0][2] + matrixL.m[0][1] * matrixR.m[1][2] + matrixL.m[0][2] * matrixR.m[2][2] + matrixL.m[0][3] * matrixR.m[3][2];
		r.m[0][3] = matrixL.m[0][0] * matrixR.m[0][3] + matrixL.m[0][1] * matrixR.m[1][3] + matrixL.m[0][2] * matrixR.m[2][3] + matrixL.m[0][3] * matrixR.m[3][3];

		r.m[1][0] = matrixL.m[1][0] * matrixR.m[0][0] + matrixL.m[1][1] * matrixR.m[1][0] + matrixL.m[1][2] * matrixR.m[2][0] + matrixL.m[1][3] * matrixR.m[3][0];
		r.m[1][1] = matrixL.m[1][0] * matrixR.m[0][1] + matrixL.m[1][1] * matrixR.m[1][1] + matrixL.m[1][2] * matrixR.m[2][1] + matrixL.m[1][3] * matrixR.m[3][1];
		r.m[1][2] = matrixL.m[1][0] * matrixR.m[0][2] + matrixL.m[1][1] * matrixR.m[1][2] + matrixL.m[1][2] * matrixR.m[2][2] + matrixL.m[1][3] * matrixR.m[3][2];
		r.m[1][3] = matrixL.m[1][0] * matrixR.m[0][3] + matrixL.m[1][1] * matrixR.m[1][3] + matrixL.m[1][2] * matrixR.m[2][3] + matrixL.m[1][3] * matrixR.m[3][3];

		r.m[2][0] = matrixL.m[2][0] * matrixR.m[0][0] + matrixL.m[2][1] * matrixR.m[1][0] + matrixL.m[2][2] * matrixR.m[2][0] + matrixL.m[2][3] * matrixR.m[3][0];
		r.m[2][1] = matrixL.m[2][0] * matrixR.m[0][1] + matrixL.m[2][1] * matrixR.m[1][1] + matrixL.m[2][2] * matrixR.m[2][1] + matrixL.m[2][3] * matrixR.m[3][1];
		r.m[2][2] = matrixL.m[2][0] * matrixR.m[0][2] + matrixL.m[2][1] * matrixR.m[1][2] + matrixL.m[2][2] * matrixR.m[2][2] + matrixL.m[2][3] * matrixR.m[3][2];
		r.m[2][3] = matrixL.m[2][0] * matrixR.m[0][3] + matrixL.m[2][1] * matrixR.m[1][3] + matrixL.m[2][2] * matrixR.m[2][3] + matrixL.m[2][3] * matrixR.m[3][3];

		r.m[3][0] = matrixL.m[3][0] * matrixR.m[0][0] + matrixL.m[3][1] * matrixR.m[1][0] + matrixL.m[3][2] * matrixR.m[2][0] + matrixL.m[3][3] * matrixR.m[3][0];
		r.m[3][1] = matrixL.m[3][0] * matrixR.m[0][1] + matrixL.m[3][1] * matrixR.m[1][1] + matrixL.m[3][2] * matrixR.m[2][1] + matrixL.m[3][3] * matrixR.m[3][1];
		r.m[3][2] = matrixL.m[3][0] * matrixR.m[0][2] + matrixL.m[3][1] * matrixR.m[1][2] + matrixL.m[3][2] * matrixR.m[2][2] + matrixL.m[3][3] * matrixR.m[3][2];
		r.m[3][3] = matrixL.m[3][0] * matrixR.m[0][3] + matrixL.m[3][1] * matrixR.m[1][3] + matrixL.m[3][2] * matrixR.m[2][3] + matrixL.m[3][3] * matrixR.m[3][3];

		return r;
	}

	inline Matrix4 initToScreenSpaceTransform( std::uint32_t width, std::uint32_t height)
	{
		Matrix4 r;

		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;

		r.m[0][0] = halfWidth;		r.m[0][1] = 0.0f;			r.m[0][2] = 0.0f;	r.m[0][3] = 0.0f;
		r.m[1][0] = 0.0f;			r.m[1][1] = halfHeight;		r.m[1][2] = 0.0f;	r.m[1][3] = 0.0f;
		r.m[2][0] = 0.0f;			r.m[2][1] = 1.0f;			r.m[2][2] = 1.0f;	r.m[2][3] = 0.0f;
		r.m[3][0] = halfWidth;		r.m[3][1] = halfHeight;		r.m[3][2] = 0.0f;	r.m[3][3] = 1.0f;

		return r;
	}
}
