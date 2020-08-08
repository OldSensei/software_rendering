#pragma once

#include <algorithm>

namespace SFWR::Math
{
	struct Vertex
	{
		float x;
		float y;
	};

	inline void swap( SFWR::Math::Vertex& a, SFWR::Math::Vertex& b )
	{
		std::swap(a.x, b.x);
		std::swap(a.y, b.y);
	}
} // namespace SFWR::Renderer
