#include <chrono>

#include "../../math/vertex.hpp"

#include "solid_shape_app.hpp"

namespace
{
	SFWR::Math::Vertex aLocal{ 0.f, -0.5f };
	SFWR::Math::Vertex bLocal{ 0.5f, 0.5f };
	SFWR::Math::Vertex cLocal{ -0.5f, 0.5f };

	std::uint64_t oldTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
		.time_since_epoch()
		.count();

	SFWR::Math::Vertex aWorld;
	SFWR::Math::Vertex bWorld;
	SFWR::Math::Vertex cWorld;
}

void SolidShapeApp::update( SFWR::System::Utils::FloatSeconds delta)
{
	std::uint64_t newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
		.time_since_epoch()
		.count();

	std::uint64_t deltaT = newTime - oldTime;

	auto rotationMatrix = SFWR::Math::initRotationAroundYTransform(deltaT * 360.0f / 2500.0f );

	aWorld = aLocal;
	bWorld = bLocal;
	cWorld = cLocal;

	aWorld.transform(rotationMatrix);
	bWorld.transform(rotationMatrix);
	cWorld.transform(rotationMatrix);
}

void SolidShapeApp::render()
{
	m_rc.clear(0, 0, 0);
	m_rc.fillTriangle(aWorld, bWorld, cWorld);
	m_viewPort->present( m_rc.getBuffer() );
}