#pragma once

#include "vector4.hpp"

namespace SFWR::Math
{
	struct Colour
	{
		Colour() :
			r{0.f},
			g{0.f},
			b{0.f},
			a{0.f}
		{}

		explicit Colour(const SFWR::Math::Vector4& source) :
			r{ source.m_x },
			g{ source.m_y },
			b{ source.m_z },
			a{ source.m_w }
		{};

		Colour(float rValue, float gValue, float bValue, float aValue) :
			r{ rValue },
			g{ gValue },
			b{ bValue },
			a{ aValue }
		{}

		float r;
		float g;
		float b;
		float a;
	};

	inline Colour lepr(const Colour& min, const Colour& max, float weight)
	{
		Colour result;
		//result.r = (1.0f - weight) * min.r + weight * max.r;
		//result.g = (1.0f - weight) * min.g + weight * max.g;
		//result.b = (1.0f - weight) * min.b + weight * max.b;
		//result.a = (1.0f - weight) * min.a + weight * max.a;
		result.r = min.r + weight * (max.r - min.r);
		result.g = min.g + weight * (max.g - min.g);
		result.b = min.b + weight * (max.b - min.b);
		result.a = min.a + weight * (max.a - min.a);

		return result;
	}
} // namespace SFWR::Math
