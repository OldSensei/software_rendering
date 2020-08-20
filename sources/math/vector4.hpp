#pragma once

namespace SFWR::Math
{
	// TODO 16 byte aligned
	struct Vector4
	{
		Vector4(float x, float y, float z = 0.f, float w = 1.f) :
			m_x{ x },
			m_y{ y },
			m_z{ z },
			m_w{ w }
		{};

		Vector4& operator=(const Vector4& rhv)
		{
			m_x = rhv.m_x;
			m_y = rhv.m_y;
			m_z = rhv.m_z;
			m_w = rhv.m_w;

			return *this;
		}

		Vector4& operator*(float scalar)
		{
			m_x *= scalar;
			m_y *= scalar;
			m_z *= scalar;
			m_w *= scalar;

			return *this;
		}

		Vector4& operator+(const Vector4& rhv)
		{
			m_x += rhv.m_x;
			m_y += rhv.m_y;
			m_z += rhv.m_z;
			m_w += rhv.m_w;

			return *this;
		}

		Vector4& operator+=(const Vector4& rhv)
		{
			return this->operator+(rhv);
		}

		Vector4& operator-(const Vector4& rhv)
		{
			m_x -= rhv.m_x;
			m_y -= rhv.m_y;
			m_z -= rhv.m_z;
			m_w -= rhv.m_w;

			return *this;
		}

		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};

	inline void swap(Vector4& a, Vector4& b)
	{
		Vector4 temp = a;
		a = b;
		b = temp;
	}

	inline Vector4 operator*(const Vector4& a, float scalar)
	{
		return Vector4{ a.m_x * scalar, a.m_y * scalar, a.m_z * scalar, a.m_w * scalar };
	}

	inline Vector4 operator*(float scalar, const Vector4& a)
	{
		return Vector4{ a.m_x * scalar, a.m_y * scalar, a.m_z * scalar, a.m_w * scalar };
	}

	inline Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4{a.m_x + b.m_x, a.m_y + b.m_y, a.m_z + b.m_z, a.m_w + b.m_w};
	}

	inline Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4{ a.m_x - b.m_x, a.m_y - b.m_y, a.m_z - b.m_z, a.m_w - b.m_w };
	}

} // namespace SFWR::Math
