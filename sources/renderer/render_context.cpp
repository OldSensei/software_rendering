#include <algorithm>
#include <cmath>
#include <cassert>

#include "../math/vector2.hpp"
#include "../math/matrix4.hpp"

#include "render_context.hpp"

namespace  SFWR::Renderer
{
	RenderContext::Edge::Edge(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b) :
		step{ 0.0f },
		curX{ 0.0f },
		yStart{ static_cast<std::uint32_t>(ceilf(a.m_pos.m_y)) },
		yEnd{ static_cast<std::uint32_t>(ceilf(b.m_pos.m_y)) },
		isValide{ false }
	{
		float distY = b.m_pos.m_y - a.m_pos.m_y;
		float distX = b.m_pos.m_x - a.m_pos.m_x;

		if (distY > 0)
		{
			isValide = true;

			step = distX / distY;

			float yPrestep = ceilf(a.m_pos.m_y) - a.m_pos.m_y;
			curX = a.m_pos.m_x + yPrestep * step;
		}
	}

	RenderContext::RenderContext(std::uint32_t width, std::uint32_t height, std::uint32_t bitsPerPixel) :
		FrameBuffer{ width, height, bitsPerPixel }
	{}

	void RenderContext::fillTriangle(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const SFWR::Math::Vertex& c)
	{
		using std::swap;

		static SFWR::Math::Matrix4 m = SFWR::Math::initToScreenSpaceTransform(getWidth(), getHeight());

		SFWR::Math::Vertex minY = a;
		SFWR::Math::Vertex midY = b;
		SFWR::Math::Vertex maxY = c;

		minY.transform( 1.0f / minY.m_pos.m_w ).transform(m);
		midY.transform( 1.0f / midY.m_pos.m_w ).transform(m);
		maxY.transform( 1.0f / maxY.m_pos.m_w ).transform(m);

		if (maxY.m_pos.m_y < minY.m_pos.m_y)
		{
			SFWR::Math::swap(maxY, minY);
		}

		if (midY.m_pos.m_y < minY.m_pos.m_y)
		{
			SFWR::Math::swap(midY, minY);
		}

		if (maxY.m_pos.m_y < midY.m_pos.m_y)
		{
			SFWR::Math::swap(maxY, midY);
		}

		float signedArea = SFWR::Math::crossProduct( { minY, maxY }, { minY, midY } );
		Handedness handedness = signedArea < 0 ? SFWR::Renderer::RenderContext::Handedness::CounterClockwise : SFWR::Renderer::RenderContext::Handedness::Clockwise;

		scanTriangle(minY, midY, maxY, handedness);
	}

	void RenderContext::scanTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness)
	{
		Edge bottomToTop{ minY, maxY };
		Edge bottomToMid{ minY, midY };
		Edge midToTop{ midY, maxY };

		assert( bottomToTop.isValide );

		if ( bottomToMid.isValide)
		{
			scanTrianglePart(bottomToTop, bottomToMid, handedness);
		}
		
		if (midToTop.isValide)
		{
			scanTrianglePart(bottomToTop, midToTop, handedness);
		}
	}

	void RenderContext::scanTrianglePart( Edge& bottomToTop, Edge& mid, Handedness handedness)
	{
		Edge& left = handedness == Handedness::CounterClockwise ? bottomToTop : mid;;
		Edge& right = handedness == Handedness::CounterClockwise ? mid : bottomToTop;

		for (auto y = mid.yStart; y < mid.yEnd; ++y)
		{
			drawScanLine(left, right, y);
			left.curX += left.step;
			right.curX += right.step;
		}
	}

	void RenderContext::drawScanLine(const Edge& left, const Edge& right, std::uint32_t y)
	{
		auto xStart = static_cast<std::uint32_t>(ceilf(left.curX));
		auto xEnd = static_cast<std::uint32_t>(ceilf(right.curX));

		for (auto& x = xStart; x < xEnd; ++x)
		{
			putPixel(x, y, 0xff, 0xff, 0xff);
		}
	}
}