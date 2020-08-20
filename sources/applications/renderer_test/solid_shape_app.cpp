#include <chrono>

#include "../../math/vertex.hpp"

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

	auto transformation = SFWR::Math::initRotationAroundYTransform(0);//deltaT * 360.0f / 2500.0f );
	transformation.setTranslation({0.0f, 0.0f, 3.f});
	transformation = transformation * perspectiveProjection;

	aWorld = aLocal;
	bWorld = bLocal;
	cWorld = cLocal;

	aWorld.transform(transformation);
	bWorld.transform(transformation);
	cWorld.transform(transformation);
}

void SolidShapeApp::render()
{
	static char message[255] = { 0 };
	m_rc.clear(0, 0, 0);

	snprintf(message, 255, "A(x:%.4f y:%.4f z:%.4f ) Color(R:%.4f G:%.4f B:%.4f)\n", aWorld.m_pos.m_x, aWorld.m_pos.m_y, aWorld.m_pos.m_z, aWorld.m_colour.m_x, aWorld.m_colour.m_y, aWorld.m_colour.m_z);
	OutputDebugStringA(message);
	snprintf(message, 255, "B(x:%.4f y:%.4f z:%.4f ) Color(R:%.4f G:%.4f B:%.4f)\n", bWorld.m_pos.m_x, bWorld.m_pos.m_y, bWorld.m_pos.m_z, bWorld.m_colour.m_x, bWorld.m_colour.m_y, bWorld.m_colour.m_z);
	OutputDebugStringA(message);
	snprintf(message, 255, "C(x:%.4f y:%.4f z:%.4f ) Color(R:%.4f G:%.4f B:%.4f)\n", cWorld.m_pos.m_x, cWorld.m_pos.m_y, cWorld.m_pos.m_z, cWorld.m_colour.m_x, cWorld.m_colour.m_y, cWorld.m_colour.m_z);
	OutputDebugStringA(message);

	m_rc.fillTriangle(aWorld, bWorld, cWorld);
	m_viewPort->present( m_rc.getBuffer() );
}