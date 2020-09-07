#pragma once

#include <tuple>

#include "vector4.hpp"

namespace SFWR::Math
{
	struct Colour
	{
		Colour() noexcept :
			r{0.f},
			g{0.f},
			b{0.f},
			a{0.f}
		{}

		explicit Colour(const SFWR::Math::Vector4& source) noexcept :
			r{ source.m_x },
			g{ source.m_y },
			b{ source.m_z },
			a{ source.m_w }
		{};

		Colour(float rValue, float gValue, float bValue, float aValue) noexcept :
			r{ rValue },
			g{ gValue },
			b{ bValue },
			a{ aValue }
		{}

		~Colour() = default;

		float r;
		float g;
		float b;
		float a;
	};

	inline Colour lepr(const SFWR::Math::Colour& min, const SFWR::Math::Colour& max, float weight) noexcept
	{
		Colour result;

		result.r = min.r + weight * (max.r - min.r);
		result.g = min.g + weight * (max.g - min.g);
		result.b = min.b + weight * (max.b - min.b);
		result.a = min.a + weight * (max.a - min.a);

		return result;
	}

	inline auto normalizedToUint32(const SFWR::Math::Colour& colour) noexcept
	{
		return std::make_tuple(static_cast<std::uint32_t>(colour.r * 255.f),
								static_cast<std::uint32_t>(colour.g * 255.f),
								static_cast<std::uint32_t>(colour.b * 255.f),
								static_cast<std::uint32_t>(colour.a * 255.f));
	}
} // namespace SFWR::Math
