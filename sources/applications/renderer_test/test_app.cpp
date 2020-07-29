#include "test_app.hpp"

#include <vector>
#include <random>

#define _USE_MATH_DEFINES
#include <math.h>

namespace
{
	class StarField
	{
	public:
		StarField(std::uint32_t numStars, float spread, float speed) :
			m_spread{spread},
			m_speed{speed},
			m_starX(numStars),
			m_starY(numStars),
			m_starZ(numStars)
		{

			for (std::uint32_t index = 0; index < numStars; ++index)
			{
				initStar(index);
			}
		}
	
		void initStar(std::uint32_t index)
		{
			static std::default_random_engine generator;
			static std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
			static std::uniform_real_distribution<float> zDistribution(0.001f, 1.0f);

			m_starX[index] = distribution(generator) * m_spread;
			m_starY[index] = distribution(generator) * m_spread;
			m_starZ[index] = zDistribution(generator) * m_spread;
		}

		void update(float time, SFWR::Renderer::FrameBuffer& fb)
		{
			static float tanHalfFOV = tanf( 140 / 2 * M_PI  / 180.0f );

			std::int32_t halfWidth = fb.getWidth() / 2;
			std::int32_t halfHeight = fb.getHeight() / 2;

			for (std::uint32_t index = 0; index < m_starX.size(); ++index)
			{
				m_starZ[index] -= time * m_speed;
				if (m_starZ[index] <= 0)
				{
					initStar(index);
				}

				std::int32_t x = static_cast<std::int32_t>( (m_starX[index] / (m_starZ[index] * tanHalfFOV)) * halfWidth + halfWidth );
				std::int32_t y = static_cast<std::int32_t>( (m_starY[index] / (m_starZ[index] * tanHalfFOV)) * halfHeight + halfHeight );

				if (x < 0 || x >= fb.getWidth() ||
					y < 0 || y >= fb.getHeight())
				{
					initStar(index);
				}
				else
				{
					fb.putPixel(static_cast<std::uint32_t>(x), static_cast<std::uint32_t>(y), 0xff, 0xff, 0xff);
				}
				
			}
		}

	private:
		float m_spread;
		float m_speed;

		std::vector<float> m_starX;
		std::vector<float> m_starY;
		std::vector<float> m_starZ;
	};

}

void TestApp::update(SFWR::Sytem::Utils::FloatSeconds delta)
{
	static StarField starField{ 4096, 64.f, 20.f };
	m_fb.clear(0, 0, 0);

	starField.update(delta.count(), m_fb);
}

void TestApp::render()
{
	m_viewPort->present(m_fb.getBuffer());
}
