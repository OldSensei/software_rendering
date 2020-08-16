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
		struct Edge
		{
			Edge(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b);

			float step;
			float curX;
			std::uint32_t yStart;
			std::uint32_t yEnd;
			bool isValide;
		};

	private:
		void scanTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness);
		void scanTrianglePart(Edge& bottomToTop, Edge& mid, Handedness handedness);
		void drawScanLine(const Edge& left, const Edge& right, std::uint32_t y);
	};
}  // namespace SFWR::Renderer
