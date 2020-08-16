#include "solid_shape_app.hpp"

#include "../../math/vertex.hpp"

void SolidShapeApp::update( SFWR::System::Utils::FloatSeconds delta)
{

}

void SolidShapeApp::render()
{
	SFWR::Math::Vertex a{0.f, -0.5f};
	SFWR::Math::Vertex b{0.5f, 0.0f};
	SFWR::Math::Vertex c{-0.5f, 0.5f};

	m_rc.fillTriangle(a, b, c);
	m_viewPort->present( m_rc.getBuffer() );
}