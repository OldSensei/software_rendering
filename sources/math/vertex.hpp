#pragma once

#include <algorithm>

#include "vector4.hpp"
#include "matrix4.hpp"

namespace SFWR::Math
{
	struct Vertex
	{
		Vertex(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.0f,
				float r = 0.f, float g = 0.f, float b = 0.f) :
			m_pos{ x, y, z, w },
			m_colour{ r, g, b, 0.f}
		{};

		SFWR::Math::Vertex& transform(const SFWR::Math::Matrix4& t);
		SFWR::Math::Vertex& transform(float scalar);

		Vector4 m_pos;
		Vector4 m_colour;
	};

	inline SFWR::Math::Vertex& Vertex::transform(const SFWR::Math::Matrix4& t)
	{
		m_pos = m_pos * t;
		return *this;
	}

	inline SFWR::Math::Vertex& Vertex::transform(float scalar)
	{
		m_pos.m_x *= scalar;
		m_pos.m_y *= scalar;
		m_pos.m_z *= scalar;
		m_pos.m_w *= scalar;

		return *this;
	}

	inline void swap( SFWR::Math::Vertex& a, SFWR::Math::Vertex& b )
	{
		std::swap(a.m_pos, b.m_pos);
		std::swap(a.m_colour, b.m_colour);
	}
} // namespace SFWR::Renderer
