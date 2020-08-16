#pragma once
#include "vertex.hpp"

namespace SFWR::Math
{
	struct Vector2
	{
		Vector2(const Vertex& v0, const Vertex& v1) :
			x{ v1.m_pos.m_x - v0.m_pos.m_x },
			y{ v1.m_pos.m_y - v0.m_pos.m_y }
		{}

		float x;
		float y;
	};

	float crossProduct(const Vector2& a, const Vector2& b);

} // namespace SFWR::Math
