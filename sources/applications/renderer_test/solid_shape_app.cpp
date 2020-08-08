#include "solid_shape_app.hpp"

#include "../../math/vertex.hpp"

void SolidShapeApp::update( SFWR::System::Utils::FloatSeconds delta)
{

}

void SolidShapeApp::render()
{
	//for (std::uint32_t y = 300; y < 400; ++y)
	//{
	//	m_rc.fillScanBuffer(y, 100, 200);
	//}
	//
	//m_rc.fillSolidShape(300, 400);

	SFWR::Math::Vertex a{100, 100};
	SFWR::Math::Vertex b{150, 200};
	SFWR::Math::Vertex c{80, 300};
	//m_rc.scanConvertTriangle(a, b, c, SFWR::Renderer::RenderContext::Handedness::CounterClockwise);
	//m_rc.fillSolidShape(100, 300);
	m_rc.fillTriangle(a, b, c);
	m_viewPort->present( m_rc.getBuffer() );
}