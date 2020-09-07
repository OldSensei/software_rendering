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
		struct Gradient
		{
			Gradient(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const SFWR::Math::Vertex& c);

			SFWR::Math::Vector4 stepX;
			SFWR::Math::Vector4 stepY;
		};

		struct Edge
		{
			Edge(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const Gradient& g);

			float step;
			float curX;
			std::uint32_t yStart;
			std::uint32_t yEnd;
			SFWR::Math::Vector4 curColour;
			SFWR::Math::Vector4 colourStep;
		};

		constexpr auto getLeftRightEdges(SFWR::Renderer::RenderContext::Edge& bottomToTop, SFWR::Renderer::RenderContext::Edge& mid, SFWR::Renderer::RenderContext::Handedness handedness) noexcept
		{
			if (handedness == SFWR::Renderer::RenderContext::Handedness::Clockwise)
			{
				return std::tie(bottomToTop, mid);
			}
			else
			{
				return std::tie(mid, bottomToTop);
			}
		}

	private:
		void scanTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness);
		void scanTrianglePart(Edge& bottomToTop, Edge& mid, Handedness handedness);
		void drawScanLine(const Edge& left, const Edge& right, std::uint32_t y);
	};
}  // namespace SFWR::Renderer
