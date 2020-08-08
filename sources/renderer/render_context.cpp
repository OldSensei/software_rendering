#include <algorithm>

#include "../math/vector2.hpp"

#include "render_context.hpp"

namespace  SFWR::Renderer
{
	RenderContext::RenderContext(std::uint32_t width, std::uint32_t height, std::uint32_t bitsPerPixel) :
		FrameBuffer{ width, height, bitsPerPixel },
		m_scanBuffer( height )
	{}

	void RenderContext::fillTriangle(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const SFWR::Math::Vertex& c)
	{
		using std::swap;

		SFWR::Math::Vertex minY = a;
		SFWR::Math::Vertex midY = b;
		SFWR::Math::Vertex maxY = c;

		if (maxY.y < minY.y)
		{
			SFWR::Math::swap(maxY, minY);
		}

		if (midY.y < minY.y)
		{
			SFWR::Math::swap(midY, minY);
		}

		if (maxY.y < midY.y)
		{
			SFWR::Math::swap(maxY, midY);
		}

		float signedArea = SFWR::Math::crossProduct( { minY, maxY }, { minY, midY } );
		Handedness handedness = signedArea < 0 ? SFWR::Renderer::RenderContext::Handedness::CounterClockwise : SFWR::Renderer::RenderContext::Handedness::Clockwise;

		scanConvertTriangle(minY, midY, maxY, handedness);
		fillSolidShape( static_cast<std::uint32_t>(minY.y), static_cast<std::uint32_t>(maxY.y));
	}

	void RenderContext::fillScanBuffer(std::uint32_t y, std::uint32_t xMin, std::uint32_t xMax)
	{
		auto& line = m_scanBuffer[y];
		line.first = xMin;
		line.second = xMax;
	}

	void RenderContext::fillSolidShape(std::uint32_t yMin, std::uint32_t yMax)
	{
		for (auto y = yMin; y < yMax; ++y)
		{
			auto& line = m_scanBuffer[y];
			for (auto& x = line.first; x < line.second; ++x)
			{
				putPixel(x, y, 0xff, 0xff, 0xff);
			}
		}
	}

	void RenderContext::scanConvertTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness)
	{
		Handedness opposite = handedness == Handedness::Clockwise ? Handedness::CounterClockwise : Handedness::Clockwise;

		scanConvertLine(minY, maxY, handedness);
		scanConvertLine(minY, midY, opposite);
		scanConvertLine(midY, maxY, opposite);
	}

	void RenderContext::scanConvertLine(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, Handedness handedness)
	{
		float distY = b.y - a.y;
		float distX = b.x - a.x;

		if (distY <= 0)
		{
			//TODO: need to log
			return;
		}

		float step = distX / distY;
		float curX = a.x;

		for (std::uint32_t y = static_cast<std::uint32_t>(a.y); y < static_cast<std::uint32_t>(b.y); ++y)
		{
			if (handedness == Handedness::Clockwise)
			{
				m_scanBuffer[y].second = static_cast<std::uint32_t>(curX);
			}
			else if (handedness == Handedness::CounterClockwise)
			{
				m_scanBuffer[y].first = static_cast<std::uint32_t>(curX);
			}
			curX += step;
		}
	}
}