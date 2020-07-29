#include "test_app.hpp"

void TestApp::update(SFWR::Sytem::Utils::FloatSeconds delta)
{
	m_fb.clear(255, 0, 0);
}

void TestApp::render()
{
	m_viewPort->present(m_fb.getBuffer());
}
