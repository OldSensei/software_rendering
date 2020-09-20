#include <chrono>

#include "../../math/vertex.hpp"
#include "../../renderer/bmp_loader.hpp"

#include "solid_shape_app.hpp"

namespace
{
	SFWR::Math::Vertex aLocal{ -0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 0.f };
	SFWR::Math::Vertex bLocal{	0.f,  0.5f, 0.f, 1.f, 0.f, 1.f, 0.f };
	SFWR::Math::Vertex cLocal{	0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f };

	std::uint64_t oldTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
		.time_since_epoch()
		.count();

	SFWR::Math::Vertex aWorld;
	SFWR::Math::Vertex bWorld;
	SFWR::Math::Vertex cWorld;
}

void SolidShapeApp::update( SFWR::System::Utils::FloatSeconds delta)
{
	static SFWR::Math::Matrix4 perspectiveProjection = SFWR::Math::initPerspectiveProjectionMatrix(70.f,
																			static_cast<float>(m_rc.getWidth()) / static_cast<float>(m_rc.getHeight()),
																			0.1f, 1000.f);

	std::uint64_t newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
		.time_since_epoch()
		.count();

	std::uint64_t deltaT = newTime - oldTime;

	auto transformation =	SFWR::Math::initRotationAroundYTransform(deltaT * 360.0f / 2500.0f ) * 
							SFWR::Math::initTranslationMatrix(0.0f, 0.0f, 3.f) *
							perspectiveProjection;

	aWorld = aLocal;
	bWorld = bLocal;
	cWorld = cLocal;

	aWorld.transform(transformation);
	bWorld.transform(transformation);
	cWorld.transform(transformation);
}

void SolidShapeApp::render()
{
	m_rc.clear(0, 0, 0);
	m_rc.fillTriangle(aWorld, bWorld, cWorld);
	m_viewPort->present( m_rc.getBuffer() );
}