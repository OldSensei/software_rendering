#pragma once

#include "../../renderer/render_context.hpp"
#include "../../system/platform/win_app.hpp"
#include "../../system/time_utils.hpp"

class SolidShapeApp : public SFWR::System::WinBaseApp
{
public:
	SolidShapeApp(HINSTANCE instance, std::string_view utf8CmdLine, std::uint32_t width, std::uint32_t height) : 
		WinBaseApp(instance, utf8CmdLine, width, height),
		m_rc{ width, height, 32 }
	{}

	void update( SFWR::System::Utils::FloatSeconds delta ) override;
	virtual void render() override;
private:
	SFWR::Renderer::RenderContext m_rc;
};
