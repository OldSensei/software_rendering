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

		Vector4& operator=(const Vector4& rht)
		{
			m_x = rht.m_x;
			m_y = rht.m_y;
			m_z = rht.m_z;
			m_w = rht.m_w;

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

} // namespace SFWR::Math
