#pragma once
#include <vector>

#include "../math/vertex.hpp"

#include "frame_buffer.hpp"


namespace SFWR::Renderer
{
	class RenderContext : public FrameBuffer
	{
	public:
		enum class Handedness : std::uint8_t
		{
			Clockwise = 0,
			CounterClockwise
		};

	public:
		RenderContext(std::uint32_t width, std::uint32_t height, std::uint32_t bitsPerPixel);
		void fillTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY);

	private:
		void fillScanBuffer(std::uint32_t y, std::uint32_t xMin, std::uint32_t xMax);
		void fillSolidShape(std::uint32_t yMin, std::uint32_t yMax);
		void scanConvertTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness);

		void scanConvertLine( const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, Handedness handedness);

	private:
		std::vector< std::pair< std::uint32_t, std::uint32_t > > m_scanBuffer;
	};
}  // namespace SFWR::Renderer
