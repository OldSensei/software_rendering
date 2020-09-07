#include <algorithm>
#include <cmath>
#include <cassert>

#include "../math/colour.hpp"
#include "../math/vector2.hpp"
#include "../math/matrix4.hpp"

#include "render_context.hpp"

namespace  SFWR::Renderer
{
	RenderContext::Gradient::Gradient(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const SFWR::Math::Vertex& c) :
		stepX{ 0.f, 0.f, 0.f, 0.f },
		stepY{ 0.f, 0.f, 0.f, 0.f }
	{
		using SFWR::Math::Vector4;

		float	dx	= (b.m_pos.m_x - c.m_pos.m_x) * (a.m_pos.m_y - c.m_pos.m_y) + (c.m_pos.m_x - a.m_pos.m_x) * (b.m_pos.m_y - c.m_pos.m_y);
		Vector4	dcx = (b.m_colour - c.m_colour) * (a.m_pos.m_y - c.m_pos.m_y) + (c.m_colour - a.m_colour) * (b.m_pos.m_y - c.m_pos.m_y);
		stepX = dcx * (1.f / dx);

		float	dy = -dx;
		Vector4	dcy = (b.m_colour - c.m_colour) * (a.m_pos.m_x - c.m_pos.m_x) + (c.m_colour - a.m_colour) * (b.m_pos.m_x - c.m_pos.m_x);
		stepY = dcy * (1.f / dy);
	}

	RenderContext::Edge::Edge(const SFWR::Math::Vertex& a, const SFWR::Math::Vertex& b, const RenderContext::Gradient& g) :
		step{ 0.0f },
		curX{ 0.0f },
		yStart{ static_cast<std::uint32_t>(ceilf(a.m_pos.m_y)) },
		yEnd{ static_cast<std::uint32_t>(ceilf(b.m_pos.m_y)) },
		curColour{a.m_colour},
		colourStep{0.0f, 0.0f, 0.0f, 0.0f}
	{
		float distY = b.m_pos.m_y - a.m_pos.m_y;
		float distX = b.m_pos.m_x - a.m_pos.m_x;

		step = distY != 0 ? distX / distY : distX;

		float yPrestep = ceilf(a.m_pos.m_y) - a.m_pos.m_y;
		curX = a.m_pos.m_x + yPrestep * step;

		float xPrestep = curX - a.m_pos.m_x;

		curColour = a.m_colour + g.stepY * yPrestep + g.stepX * xPrestep;
		colourStep = g.stepY + g.stepX * step;
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

		minY.transform(m).transform(1.0f / minY.m_pos.m_w);
		midY.transform(m).transform(1.0f / midY.m_pos.m_w);
		maxY.transform(m).transform(1.0f / maxY.m_pos.m_w);

		if (maxY.m_pos.m_y < midY.m_pos.m_y)
		{
			SFWR::Math::swap(maxY, midY);
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
		Handedness handedness = signedArea < 0 ? SFWR::Renderer::RenderContext::Handedness::Clockwise : SFWR::Renderer::RenderContext::Handedness::CounterClockwise;

		scanTriangle(minY, midY, maxY, handedness);
	}

	void RenderContext::scanTriangle(const SFWR::Math::Vertex& minY, const SFWR::Math::Vertex& midY, const SFWR::Math::Vertex& maxY, Handedness handedness)
	{
		Gradient g{ minY, midY, maxY };

		Edge bottomToTop{ minY, maxY, g };
		Edge bottomToMid{ minY, midY, g };
		Edge midToTop{ midY, maxY, g };

		scanTrianglePart(bottomToTop, bottomToMid, handedness);
		scanTrianglePart(bottomToTop, midToTop, handedness);
	}

	void RenderContext::scanTrianglePart( Edge& bottomToTop, Edge& mid, Handedness handedness)
	{
		auto [left, right] = getLeftRightEdges(bottomToTop, mid, handedness);

		for (auto y = mid.yStart; y < mid.yEnd; ++y)
		{
			drawScanLine(left, right, y);
			left.curX += left.step;
			left.curColour += left.colourStep;

			right.curX += right.step;
			right.curColour += right.colourStep;
		}
	}

	void RenderContext::drawScanLine(const Edge& left, const Edge& right, std::uint32_t y)
	{
		auto xStart = static_cast<std::uint32_t>(ceilf(left.curX));
		auto xEnd = static_cast<std::uint32_t>(ceilf(right.curX));

		auto colourStart = left.curColour;
		auto colourEnd = right.curColour;

		float step = 1.f / (xEnd - xStart);
		float weight = 0.0f;

		for (auto& x = xStart; x < xEnd; ++x)
		{
			auto result = SFWR::Math::lepr(SFWR::Math::Colour(colourStart), SFWR::Math::Colour(colourEnd), weight);
			auto&& [r, g, b, a] = SFWR::Math::normalizedToUint32(result);

			putPixel(x, y, r, g, b);

			weight += step;
		}
	}
}