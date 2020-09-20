#pragma once
#include <cstdint>

#include "../math/colour.hpp"

namespace SFWR::Renderer
{
	struct TextureInfo
	{
		std::uint32_t width;
		std::uint32_t height;
		std::uint16_t bitsPerPixel;
	};

	class ITextureData
	{
	public:
		virtual SFWR::Renderer::TextureInfo getInfo() = 0;
		virtual SFWR::Math::Colour getColor(float u, float v) = 0;
		virtual SFWR::Math::Colour getColor(std::uint32_t x, std::uint32_t y) = 0;

		virtual ~ITextureData() {};
	};
}
